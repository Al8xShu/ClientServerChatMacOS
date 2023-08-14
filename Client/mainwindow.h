#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QHostAddress>
#include <QByteArray>
#include <QTime>

QT_BEGIN_NAMESPACE

namespace Ui { class MainWindow; }

QT_END_NAMESPACE

class MainWindow : public QMainWindow{

    Q_OBJECT

public:

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_pushButtonConnect_clicked();

    void on_pushButtonSend_clicked();

    void on_lineEditMessage_returnPressed();

private:

    Ui::MainWindow *ui;

    QTcpSocket *socket;

    QByteArray data;

    quint16 nextBlockSize;

    void sendToServer(QString str);

public slots:

    void slotReadyToRead();

};

#endif // MAINWINDOW_H
