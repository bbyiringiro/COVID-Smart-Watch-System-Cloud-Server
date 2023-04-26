# COVID System Cloud Server in C++
This repository contains a multi-threaded C++ cloud server program for a COVID system. The program is responsible for receiving data from sensors (ESP8266 or ESP32) connected through WiFi and the Internet. The received data is stored and sent to a web portal for control room usage. At the moment, no bi-directional command channel is implemented.

## Features
Multi-threaded implementation for efficient data handling
Supports ESP8266 and ESP32 sensors connected through WiFi
Stores received data and sends it to a web portal
Uses QTcpServer and QTcpSocket for server and socket handling
Utilizes QSqlDatabase for database operations

## Dependencies
Qt 5.x.x (Core, Network, SQL modules)
A compatible C++ compiler (e.g., GCC, MSVC)
Building and Running the Project
Install the required dependencies.
Clone the repository:
bash
Copy code
```
git clone https://github.com/yourusername/covid-system-cloud-server.git
```
Change the working directory:
bash
Copy code
```
cd covid-system-cloud-server
```
Run qmake to generate the Makefile:
Copy code
```
qmake
```
Compile the project:
go
Copy code
```
make
```
Run the compiled executable:
bash
Copy code
```
./covid-system-cloud-server
```
## Structure

The project contains the following key files:

main.cpp: The entry point of the application, responsible for initializing the server and starting the event loop.
dataServerR.h: Header file for the dataServerR class, which inherits from QTcpServer and handles incoming connections.
dataServerR.cpp: Implementation file for the dataServerR class.
dataThreadR.h: Header file for the dataThreadR class, which inherits from QThread and is responsible for reading data from the client and handling database operations.
dataThreadR.cpp: Implementation file for the dataThreadR class.
Contributing
Please submit issues and pull requests on the GitHub repository. Your contributions are greatly appreciated!
