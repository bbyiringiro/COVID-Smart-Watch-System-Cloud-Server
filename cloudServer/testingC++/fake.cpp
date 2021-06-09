/*
* Version 2.0 (For Testing)
* This is a Master side program of commands trasmitting system over TCP/IP
* This program receives the keyboard or WiiMote actions from the master side
* This testing platform does not involve ROS, and the combined program is developped based on this platform
* User must start the Server program beforehand
* Commands flow: Master --> Server --> Slave
* The server program can identify which side is master or slave, so that there is no order to connect which side in the beginning
* The server program can detect any disconnection
* SAFETY FIRST, if master side or the server is lost, a "stop" command will be published 
* Default port is 11110, if port is not used by the master side, this program tries to connect other port between 11111 and 11119
* Default IP is 127.0.0.1 (LocalHost), so please give an IP address when calling the program
* For LocalHost:                     (./slave)
* For Internet:                      (./slave IP)
* User can specifies port if wanted: (./slave IP PORT)
* by Leo CW Kong H00278458 cwk2@hw.ac.uk
*/

#include <iostream>
#include <string>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>
#include <sys/uio.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <fstream>
#include <ctime>
using namespace std;
//Slave side
int main(int argc, char *argv[])
{
    //int bar [5] = { 10, 20, 30 };
    //cout<< bar[5];
    string IP = "3.10.180.97";
    char serverIp[100];
    strcpy(serverIp, IP.c_str());
    int port = 11111; 

    //create a message buffer 
    char msg[1500]; 

    struct hostent* host; 
    sockaddr_in sendSockAddr;   
    int clientSd;

    //setup a socket and connection tools 
    if(argc == 1){
        while(1){
            hostent* host = gethostbyname(serverIp);   
            bzero((char*)&sendSockAddr, sizeof(sendSockAddr)); 
            sendSockAddr.sin_family = AF_INET; 
            sendSockAddr.sin_addr.s_addr = 
                inet_addr(inet_ntoa(*(struct in_addr*)*host->h_addr_list));
            sendSockAddr.sin_port = htons(port);
            clientSd = socket(AF_INET, SOCK_STREAM, 0);

        //try to connect...
            int status = connect(clientSd,
                                (sockaddr*) &sendSockAddr, sizeof(sendSockAddr));
            if(status < 0 && port<11120)
            {
                cout<<"Server is not running on port " << port<<endl;
                port++; 


                /*timeval curTime;
                gettimeofday(&curTime, NULL);
                int milli = curTime.tv_usec / 1000;

                char buffer [80];
                strftime(buffer, 80, "%H:%M:%S", localtime(&curTime.tv_sec));

                char currentTime[84] = "";
                sprintf(currentTime, "%s:%d", buffer, milli);
                printf("current time: %s \n", currentTime);*/

            }
            if(status < 0 && port>11119){
                //cout<<"Server is not running on port " << port<<endl;
                cout<<"Server is not running"<<endl;
                cout<<"Please check the server program and the firewall setting"<<endl;
                exit(0);
            }
            if (!(status<0)){
                cout<<"ID 1"<<endl;
                break;
            }
        }
    }

    else if (argc == 2){
        IP = argv[1];
        strcpy(serverIp, IP.c_str());    
        while(1){
            hostent* host = gethostbyname(serverIp);   
            bzero((char*)&sendSockAddr, sizeof(sendSockAddr)); 
            sendSockAddr.sin_family = AF_INET; 
            sendSockAddr.sin_addr.s_addr = 
                inet_addr(inet_ntoa(*(struct in_addr*)*host->h_addr_list));
            sendSockAddr.sin_port = htons(port);
            clientSd = socket(AF_INET, SOCK_STREAM, 0);

            //try to connect...
            int status = connect(clientSd,
                                (sockaddr*) &sendSockAddr, sizeof(sendSockAddr));
            if(status < 0 && port<11120)
            {
                cout<<"Server is not running on port " << port<<endl;
                port++; 
            }
            if(port>11119){
                //cout<<"Server is not running on port " << port<<endl;
                cout<<"Server is not running"<<endl;
                cout<<"Please check the server program and the firewall setting"<<endl;
                exit(0);
            }
            if (!(status<0)){
                cout<<port<<endl;
                break;
            }
        }
    }

    else if (argc == 3){
        IP = argv[1];
        strcpy(serverIp, IP.c_str()); 
        port = atoi(argv[2]);   
        hostent* host = gethostbyname(serverIp);   
        bzero((char*)&sendSockAddr, sizeof(sendSockAddr)); 
        sendSockAddr.sin_family = AF_INET; 
        sendSockAddr.sin_addr.s_addr = 
            inet_addr(inet_ntoa(*(struct in_addr*)*host->h_addr_list));
        sendSockAddr.sin_port = htons(port);
        clientSd = socket(AF_INET, SOCK_STREAM, 0);    
        int status = connect(clientSd,
                            (sockaddr*) &sendSockAddr, sizeof(sendSockAddr)); 
        if (!(status<0))
            cout<<port<<endl;
        else{
            cout<<"Server is not running on "<<IP<<" & port " << port <<endl;
            exit(0);
        }
    }

	//string data = "xx";
    //data = "11+DATA+DATA";
    //memset(&msg, 0, sizeof(msg));//clear the buffer
    //strcpy(msg, data.c_str());
    //for (int i=1; i<1000; i++){
	//send(clientSd, (char*)&msg, strlen(msg), 0);
    while(1){
        memset(&msg, 0, sizeof(msg));//clear the buffer
    //strcpy(msg, data.c_str());
        string data;
        data = "99+0+0+0.00+0.00";
        timeval curTime;
        gettimeofday(&curTime, NULL);
        int milli = curTime.tv_usec / 1000;

        char buffer [80];
        strftime(buffer, 80, "%H:%M:%S", localtime(&curTime.tv_sec));

        char currentTime[84] = "";
        sprintf(currentTime, "%s", buffer);
        //printf("%s \n", currentTime);
        data += "+";
        data += currentTime;
        cout<< data << endl;

        //memset(&msg, 0, sizeof(msg));
        strcpy(msg, data.c_str());
        send(clientSd, (char*)&msg, strlen(msg), 0);
        usleep(250000); //4hz
        cout << clientSd << "\n";
        //recv(clientSd, (char*)&msg, sizeof(msg), 0);
        //cout<<msg<<endl;
        //memset(&msg, 0, sizeof(msg));
    }
	//    usleep(250000);
	    //close(clientSd);
	//}
    close(clientSd);
    /*cout << "Connected to the server!" << endl;
    int bytesRead, bytesWritten = 0;
    struct timeval start1, end1;
    gettimeofday(&start1, NULL);
    
    string data;
    data = "s";
    //getline(cin, data);
    memset(&msg, 0, sizeof(msg));//clear the buffer
    strcpy(msg, data.c_str());
    bytesWritten += send(clientSd, (char*)&msg, strlen(msg), 0);
    memset(&msg, 0, sizeof(msg));
    cout<<"waiting master"<<endl;
    recv(clientSd, (char*)&msg, sizeof(msg), 0);
    cout<<msg<<endl;

    if(!strcmp(msg, "ready"))
        while(1)
        {   bytesRead = 0;
            //cout << "Awaiting server response..." << endl;
            memset(&msg, 0, sizeof(msg));//clear the buffer
            bytesRead = recv(clientSd, (char*)&msg, sizeof(msg), 0);
            if(!strcmp(msg, "~"))
            {
                cout << "Server and master have quit the session" << endl;
                break;
            }
            if(bytesRead>0){
                cout << "Master: " << msg << endl;
                //send(clientSd, (char*)&msg, strlen(msg), 0); //tell server you are still connected
            }
            else{
                string data2 = "99";
                memset(&msg, 0, sizeof(msg));
                strcpy(msg, data2.c_str());
                cout << "Master: " << msg << endl;
                cout<<"Server is closed, please ensure server is opened."<<endl;
                memset(&msg, 0, sizeof(msg));
                break;
            }
        }
    else{
        cout<<"Please check master is running properly"<<endl;
        exit(0);
    }
    gettimeofday(&end1, NULL);
    close(clientSd);*/

    return 0;    
}
