#include "dataServerR.h"

dataServerR::dataServerR(QObject *parent) :
    QTcpServer(parent)
{
}

void dataServerR::StartServer()
{
    if(!this->listen(QHostAddress::Any,11111))
    {
        qDebug() << "Could not start server";
    }
    else
    {
        qDebug() << "Port 11111 is Listening...";
    }
}

void dataServerR::incomingConnection(long long socketDescriptor)
{
    qDebug() << socketDescriptor << " Port 11111 Connecting...";
    dataThreadR *thread = new dataThreadR(socketDescriptor, /*sizeToClinet, &size,*/ this);
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    thread->start();
}
