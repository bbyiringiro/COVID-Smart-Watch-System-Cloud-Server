#ifndef DATASERVERR_H
#define DATASERVERR_H

#include <QTcpServer>
#include <QDebug>
#include "dataThreadR.h"

class dataServerR : public QTcpServer
{
    Q_OBJECT
public:
    explicit dataServerR(QObject *parent = nullptr);
    void StartServer();
    //QByteArrayList *share;
    //int size;
    //int sizeToClinet;
    //QByteArrayList test;
    
signals:
    
public slots:

protected:
    void incomingConnection(long long socketDescriptor);
    
};

#endif // MYSERVER_H
