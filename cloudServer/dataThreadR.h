#ifndef DATATHREADR_H
#define DATATHREADR_H

#include <QThread>
#include <QTcpSocket>
#include <QDebug>
#include <QtMath>
#include <QTime>
#include <QTimer>
#include <QFile>
#include <QTextStream>

#include <QSqlDatabase>
#include <QSql>
#include <QSqlQuery>

class dataThreadR : public QThread
{
    Q_OBJECT
public:
    explicit dataThreadR(int ID, /*int sizeToClient, int* size,*/ QObject *parent = nullptr);
    void run();
    //QByteArrayList* allData;
    QTime first;
    double firstTime;
    bool firstRead = true;
    bool checkHz = true;
    double hz = 0;
    
signals:
    void error(QTcpSocket::SocketError socketerror);
    
public slots:
    void Read();
    void Dis();
    void ProDis();
    void TODis();

public slots:

private:
    QTcpSocket *socket;
    QTimer *timer;
    int socketDescriptor;
    QByteArray Data;
    QByteArray store;
    QTime current;
    QTime previous;
    QByteArray prevData = "";
    bool TO = false;
    bool PRO = false;
    bool firstOnOff = true;
    bool firstDB = true;
    QString OnTime;
    QString onOffqryString;
    int i = 0;

    QSqlDatabase db;
    
};

#endif // MYTHREAD_H
