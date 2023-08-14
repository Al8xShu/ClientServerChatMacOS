#include "server.h"

Server::Server(){

    if(this->listen(QHostAddress::Any, 1212)){
        qDebug() << "Server is start!";
    }else{
        qDebug() << "Error on startup!";
    }

    nextBlockSize = 0;

}

Server::~Server(){ delete socket; }

void Server::sendToClient(QString str){

    data.clear();

    QDataStream out(&data, QIODevice::WriteOnly);

    out.setVersion(QDataStream::Qt_6_5);
    out << quint16(0) << QTime::currentTime() << str;
    out.device()->seek(0);
    out << quint16(data.size() - sizeof(quint16));

    for(int i = 0; i < sockets.size(); i++){
        sockets[i]->write(data);
    }

}

void Server::incomingConnection(qintptr socketDescrtiptor){

    socket = new QTcpSocket;
    socket->setSocketDescriptor(socketDescrtiptor);

    connect(socket, &QTcpSocket::readyRead, this, &Server::slotReadyToRead);
    connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);

    sockets.push_back(socket);

    qDebug() << "Client is connected: " << "User " << socketDescrtiptor;

}

void Server::slotReadyToRead(){

    socket = (QTcpSocket*)sender();

    QDataStream in(socket);

    in.setVersion(QDataStream::Qt_6_5);

    if(in.status() == QDataStream::Ok){
        for(;;){
            if(nextBlockSize == 0){

                qDebug() << "NextBlockSize = 0";

                if(socket->bytesAvailable() < 2) {
                    qDebug() << "Data < 2, break!";
                    break;
                }

                in >> nextBlockSize;
                qDebug() << "NextBlockSize = " << nextBlockSize;

            }

            if(socket->bytesAvailable() < nextBlockSize){
                qDebug() << "Data is not full, break!";
                break;
            }

            QString str;
            QTime time;
            in >> time >> str;
            nextBlockSize = 0;
            qDebug() << str;
            sendToClient(str);
            break;
        }
    }else{
        qDebug() << "Data stream error!";
    }

}
