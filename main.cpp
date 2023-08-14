#include <QCoreApplication>
#include "server.h"

int main(int argc, char *argv[]){

    QCoreApplication serverApp(argc, argv);

    Server serverAVS;

    return serverApp.exec();

}
