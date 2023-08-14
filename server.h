#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QDataStream>
#include <QList>
#include <QByteArray>
#include <QTime>

class Server:public QTcpServer{

    Q_OBJECT

public:

    Server();
    ~Server();

    QTcpSocket *socket;

private:

    QList<QTcpSocket*> sockets;

    QByteArray data;

    quint16 nextBlockSize;

    void sendToClient(QString str);

public slots:

    void incomingConnection(qintptr socketDescrtiptor);

    void slotReadyToRead();

};

#endif // SERVER_H
