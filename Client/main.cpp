#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[]){

    QApplication clientApp(argc, argv);

    MainWindow mainWindow;

    mainWindow.show();

    return clientApp.exec();

}
