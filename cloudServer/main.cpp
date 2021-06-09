/*
 * This program is going to be the cloud server program running on a cloud server
 * For COVID system, it directly coonects sensors (ESP8266 or ESP32) through wifi->internet->this server program
 * The received data will be stored and sent to the web portal for the uae of the control room
 * No bi-directional command channel is needed at the moment
*/

#include <QCoreApplication>
#include "dataServerR.h"

int main(int argc, char *argv[])
{

    QCoreApplication a(argc, argv);
    
    dataServerR Server; //server for receiving data
    Server.StartServer();

    return a.exec();
}
