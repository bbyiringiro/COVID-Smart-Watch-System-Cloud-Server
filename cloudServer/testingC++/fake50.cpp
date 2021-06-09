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
#include <pthread.h> 
#include <fstream>
#include <cstdlib>
#include <sstream>
using namespace std;
//Slave side


/*void connectToServer(int id)
{
    int ID = id;
    string IP = "127.0.0.1";
    char serverIp[100];
    strcpy(serverIp, IP.c_str());
    int port = 11111; 

    //create a message buffer 
    char msg[1500]; 

    struct hostent* host; 
    sockaddr_in sendSockAddr;   
    int clientSd;

    //setup a socket and connection tools 
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
                cout<<"ID 1 - 100"<<endl;
                break;
            }
        }
    

    string data;
    data = to_string(ID);
    data += "+DATA+DATA";
    memset(&msg, 0, sizeof(msg));//clear the buffer
    strcpy(msg, data.c_str());

    while(1){
        send(clientSd, (char*)&msg, strlen(msg), 0);
        usleep(250000); //4hz
    }

    close(clientSd);
}*/

void *PrintHello(void *threadid) {
   long tid;
   tid = (long)threadid;
   //cout << "Hello World! Thread ID, " << tid << endl;
   //pthread_exit(NULL);

   int ID = tid;
   string IP = "3.10.180.97";
    //string IP = "137.195.63.69";
    char serverIp[100];
    strcpy(serverIp, IP.c_str());
    int port = 11111; 

    //create a message buffer 
    char msg[1500]; 

    struct hostent* host; 
    sockaddr_in sendSockAddr;   
    int clientSd;

    //setup a socket and connection tools 
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
                cout<<ID<<endl;
                break;
            }
        }
    

    string data;
    stringstream ss;
    if (ID == 3)
        ID = 49;
    ss << (ID+1);

    while(1){

        data = ss.str();
        data += "+0+0+0.00+0.00";

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
        data += "?";
        cout<< data << endl;

        memset(&msg, 0, sizeof(msg));//clear the buffer
        strcpy(msg, data.c_str());

        send(clientSd, (char*)&msg, strlen(msg), 0);
        usleep(1000000); //1hz
    }

    close(clientSd);
}

int main(int argc, char *argv[])
{
    /*thread one (connectToServer, 90);
    thread two (connectToServer, 91);
    thread three (connectToServer, 92);
    thread four (connectToServer, 93);
    one.join();
    
    two.join();
    
    three.join();
    
    four.join();
    return 0;*/
   pthread_t threads[49];
   int rc;
   int i;
   
   for( i = 0; i < 49; i++ ) {
      //cout << "main() : creating thread, " << i << endl;
      rc = pthread_create(&threads[i], NULL, PrintHello, (void *)i);
      usleep(31250);
      
      if (rc) {
         cout << "Error:unable to create thread," << rc << endl;
         exit(-1);
      }
   }
   pthread_exit(NULL);
}
