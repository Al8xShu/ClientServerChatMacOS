#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
    ui(new Ui::MainWindow){

    ui->setupUi(this);

    socket = new QTcpSocket(this);

    connect(socket, &QTcpSocket::readyRead, this, &MainWindow::slotReadyToRead);
    connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);

    nextBlockSize = 0;

}

MainWindow::~MainWindow(){ delete ui; }

void MainWindow::on_pushButtonConnect_clicked(){

    socket->connectToHost(QHostAddress::LocalHost, 1212);

}

void MainWindow::on_pushButtonSend_clicked(){

    sendToServer(ui->lineEditMessage->text());

}


void MainWindow::on_lineEditMessage_returnPressed(){

    sendToServer(ui->lineEditMessage->text());

}

void MainWindow::sendToServer(QString str){

    data.clear();

    QDataStream out(&data, QIODevice::WriteOnly);

    out.setVersion(QDataStream::Qt_6_5);
    out << quint16(0) << QTime::currentTime() << str;
    out.device()->seek(0);
    out << quint16(data.size() - sizeof(quint16));

    socket->write(data);

    ui->lineEditMessage->clear();

}

void MainWindow::slotReadyToRead(){

    QDataStream in(socket);

    in.setVersion(QDataStream::Qt_6_5);

    if(in.status() == QDataStream::Ok){
        for(;;){

            if(nextBlockSize == 0){

                if(socket->bytesAvailable() < 2) {
                    break;
                }

                in >> nextBlockSize;

            }
            if(socket->bytesAvailable() < nextBlockSize){
                break;
            }

            QString str;
            QTime time;
            in >> time >> str;
            nextBlockSize = 0;
            ui->textBrowser->append("[" + time.toString() + "] " + str);

            break;
        }
    }else{

        ui->textBrowser->append("Read error!");

    }

}
