#include "dataThreadR.h"


dataThreadR::dataThreadR(int ID, /*int sizeToClient, int* size,*/ QObject *parent) :
    QThread(parent)
{
    this->socketDescriptor = ID;
    //allData = share;
}

void dataThreadR::run()
{
    // thread starts here
    qDebug() << socketDescriptor << " Port 11111 Starting thread";
    socket = new QTcpSocket();
    timer = new QTimer();
    if(!socket->setSocketDescriptor(this->socketDescriptor))
    {
        emit error(socket->error());
        return;
    }

    connect(socket, SIGNAL(readyRead()), this, SLOT(Read()),Qt::DirectConnection);
    connect(socket, SIGNAL(disconnected()), this, SLOT(Dis()),Qt::DirectConnection);
    connect(timer, SIGNAL(timeout()), this, SLOT(TODis()));

    qDebug() << socketDescriptor << " Port 11111 Client connected";

    timer->setInterval(15000); //15sec timeout
    timer->start();

    // make this thread a loop
    exec();
}

void dataThreadR::Read()
{
    Data = socket->readAll();
    timer->stop();

    QString dataString = Data;
    QStringList TCPCheck = dataString.split("?");
    QStringList protocolCheck = TCPCheck[0].split("+");

    if (protocolCheck.size() == 1 && protocolCheck[0].size() == 17) { //received mac address, which is also the handshake of the connection
        qDebug() << "MAC: " << protocolCheck[0];
        QString filePath = "/home/billy/IHF/data.csv";
        bool registered = false;
        bool nothing = false;
        int ID;
        QByteArray name;
        QByteArray IDname;
        int count = 0;

        QFile file(filePath);
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        //qDebug() << "ready to read";
        QTextStream stream(&file);
        while(!stream.atEnd()) {
            QString line = stream.readLine();
            QStringList assetDetail = line.split(",");
            if (assetDetail.size() > 1) { // nothing there
                if (protocolCheck[0] == assetDetail[1] && assetDetail[2] == " "){
                    registered = true;
                    ID = assetDetail[0].toInt();
                    name = assetDetail[3].toUtf8();
                    IDname = assetDetail[0].toUtf8();
                    //qDebug() << "read";
                }
            }
            else {
                nothing = true;
            }
            count++;
        }
        file.close();

        if (registered) { //found the detail for the CSV
            qDebug() << ID;
            qDebug() << name;
            socket->write(IDname+"\r");
            socket->waitForBytesWritten(3000);
        }
        else { //not registered, so have to register here
            qDebug() << count;
            int newID;
            if (nothing)
                newID = count;
            else
                newID = count+1;

            QString conname = "connection ";
            conname += QString::number(int(this->socketDescriptor));

            db = QSqlDatabase::addDatabase("QMYSQL", conname);
            db.setHostName("db.ihf-disc.co.uk");
            db.setDatabaseName("disc_portal");
            db.setUserName("disc_portal_user");
            db.setPassword("5uLXUzJTpSPlX8hv8AWzg6icb3ovooAD");


            QString year = (QDateTime::currentDateTime().toString("yyyy"));
            QString month = (QDateTime::currentDateTime().toString("MM"));
            QString date = (QDateTime::currentDateTime().toString("dd"));
            QString time = (QDateTime::currentDateTime().toString("HH"));
            time += ":"; time += (QDateTime::currentDateTime().toString("mm"));
            time += ":"; time += (QDateTime::currentDateTime().toString("ss"));

            QString qryString = "INSERT INTO sensors (id, mac_address, codename,number, sensors.condition, power, created_at) values ('";
            qryString += QString::number(newID);      qryString += "','";
            qryString += protocolCheck[0];      qryString += "','";
            qryString += "Sensor "+QString::number(newID);       qryString += "','"; //codename
            qryString += QString::number(newID);      qryString += "','"; // number
            qryString += QString::number(2);      qryString += "','"; // condition
            qryString += QString::number(0);      qryString += "','"; //power
            qryString += year;      qryString += "-";
            qryString += month;     qryString += "-";
            qryString += date;      qryString += " ";
            qryString += time;      qryString += "')";

            if (!(db.open())) {
                qDebug() << "cannot open";
            }





            QSqlQuery qry(db);
            if (!qry.exec(qryString)){
                qDebug() << "cannot insert new sensor";

//                qDebug() << qry.lastError().databaseText() << " \n" <<qry.lastError().driverText() ;
            }


            else{
                qDebug() << "New sensor Inserted! it's id" << newID;
                if (nothing) {

                    file.open(QIODevice::WriteOnly | QIODevice::Text);
                    stream << newID << "," << protocolCheck[0] << ", ," << "Sensor" << newID << "\n";
                    file.close();
                    QString sendID = QString::number(newID);
                    socket->write(sendID.toUtf8()+"\r");
                    socket->waitForBytesWritten(3000);

                }

                else {
                    file.open(QIODevice::WriteOnly | QIODevice::Append);
                    stream << newID << "," << protocolCheck[0] << ", ," << "Sensor" << newID << "\n";
                    file.close();
                    QString sendID = QString::number(newID);
                    socket->write(sendID.toUtf8()+"\r");
                    socket->waitForBytesWritten(3000);
                }

            }
//            QSqlQuery query2 = QSqlQuery(db);


//            query2.exec("DELETE FROM sensors WHERE id = 18");
//            query2.exec("SELECT * FROM sensors");
//                // The above two sentences are equivalent to the one commented below
//                // QSqlQuery query2("SELECT * FROM db2.table_component_info",database_1);

//            QSqlRecord rec = query2.record();

//            qDebug() << "Number of columns in the table:" << rec;         // How many columns are there in the table
//            qDebug() << "Number of rows in the table:" << query2.size();       // How many rows are there in the table

//            int col1 = rec.indexOf("id");       // Get the subscript of the attribute "component_type" in the table (counting from the 0th column, which column)
//            int col2 = rec.indexOf("created_at");
//            while (query2.next())
//            {
//                qDebug() << query2.value(col1).toString() << " " << query2.value(col2).toString();  // Output all values ​​under the column name "component_type"
//            }

            db.close();

        }


    }

    else if (protocolCheck.size() == 3) { //PPG testing protocol
        if (firstDB) {
            if (i < 4) { //go to test DB
                QString conname = "connection ";
                conname += QString::number(int(this->socketDescriptor));

                db = QSqlDatabase::addDatabase("QMYSQL", conname);
                db.setHostName("db.ihf-disc.co.uk");
                db.setDatabaseName("disc_test");
                db.setUserName("disc_portal_user");
                db.setPassword("5uLXUzJTpSPlX8hv8AWzg6icb3ovooAD");
            }


            else {
                QString conname = "connection ";
                conname += QString::number(int(this->socketDescriptor));

                db = QSqlDatabase::addDatabase("QMYSQL", conname);
                db.setHostName("db.ihf-disc.co.uk");
                db.setDatabaseName("disc_portal");
                db.setUserName("disc_portal_user");
                db.setPassword("5uLXUzJTpSPlX8hv8AWzg6icb3ovooAD");
            }

            firstDB = false;
        }
        for (i=0; i<TCPCheck.size()-1; i++) {
            QStringList x = TCPCheck[i].split("+");
            qDebug() << x;
            QString year = (QDateTime::currentDateTime().toString("yyyy"));
            QString month = (QDateTime::currentDateTime().toString("MM"));
            QString date = (QDateTime::currentDateTime().toString("dd"));
            QString time = (QDateTime::currentDateTime().toString("HH"));
            time += ":"; time += (QDateTime::currentDateTime().toString("mm"));
            time += ":"; time += (QDateTime::currentDateTime().toString("ss"));
            QString qryString = "INSERT INTO sensor_data (ppg, sensor_id, created_at, updated_at) values ('";
            qryString += x[1];      qryString += "','";
            qryString += x[0];      qryString += "','";
            qryString += year;      qryString += "-";
            qryString += month;     qryString += "-";
            qryString += date;      qryString += " ";
            qryString += time;      qryString += "','";
            qryString += year;      qryString += "-";
            qryString += month;     qryString += "-";
            qryString += date;      qryString += " ";
            qryString += time;      qryString += "')";

            QSqlQuery qry(db);

            qry.prepare(qryString);
            if (!qry.exec())

                qDebug() << "cannot insert";

            else
                qDebug() << "PPG Inserted" << protocolCheck[3];

        }
    }

    else if (protocolCheck.size() != 6 && protocolCheck.size() != 3 && protocolCheck[0].size() != 17) { //not following the protocol
        qDebug() << "wrong protocol";
        qDebug() << Data;
        ProDis();
    }

    else{ //correct protocol

        if (protocolCheck[0].toInt() > 0 && protocolCheck[0].toInt() < 102){ //check if the connected assets provide valid ID, never use "0" as an ID
            i = protocolCheck[0].toInt(); //i is the ID of the list, eg. ID 100

            if (firstDB) {
                if (i < 4) { //go to test DB, 1 - 3 will go to test pool
                    QString conname = "connection ";
                    conname += QString::number(int(this->socketDescriptor));

                    db = QSqlDatabase::addDatabase("QMYSQL", conname);
                    db.setHostName("db.ihf-disc.co.uk");
                    db.setDatabaseName("disc_test");
                    db.setUserName("disc_portal_user");
                    db.setPassword("5uLXUzJTpSPlX8hv8AWzg6icb3ovooAD");
                }


                else {
                    QString conname = "connection ";
                    conname += QString::number(int(this->socketDescriptor));

                    db = QSqlDatabase::addDatabase("QMYSQL", conname);
                    db.setHostName("db.ihf-disc.co.uk");
                    db.setDatabaseName("disc_portal");
                    db.setUserName("disc_portal_user");
                    db.setPassword("5uLXUzJTpSPlX8hv8AWzg6icb3ovooAD");
                }

                firstDB = false;
            }

            //(*allData)[i] = TCPCheck[0].toUtf8();
            prevData = TCPCheck[0].toUtf8();

            QString year = (QDateTime::currentDateTime().toString("yyyy"));
            QString month = (QDateTime::currentDateTime().toString("MM"));
            QString date = (QDateTime::currentDateTime().toString("dd"));
            QString hour = (QDateTime::currentDateTime().toString("hh"));
            QString min = (QDateTime::currentDateTime().toString("mm"));
            QString sec = (QDateTime::currentDateTime().toString("ss"));


            //QString qryString = "INSERT INTO Sensors (sensorID, heartRate, SPO2, temperature, timeStamp) values ('";
            //QString qryString = "INSERT INTO sensor_data (heart_rate, sp02, temperature, temperature_environmental, health_status_id, sensor_id, created_at, updated_at) values ('";
            QString qryString = "INSERT INTO sensor_data (heart_rate, sp02, temperature, temperature_environmental, sensor_id, created_at, updated_at) values ('";
            double spo2 = protocolCheck[2].toDouble();

            if (spo2>100)
                protocolCheck[2] = "100";

            qryString += protocolCheck[1]; qryString += "','";
            qryString += protocolCheck[2]; qryString += "','";
            qryString += protocolCheck[3]; qryString += "','";
            qryString += protocolCheck[4]; qryString += "','";

            qryString += protocolCheck[0]; qryString += "','";
            qryString += year;      qryString += "-";
            qryString += month;     qryString += "-";
            qryString += date;      qryString += " ";

            qryString += hour;      qryString += ":";
            qryString += min;      qryString += ":";
            qryString += sec;      qryString += "','";
            qryString += year;      qryString += "-";
            qryString += month;     qryString += "-";
            qryString += date;      qryString += " ";

            qryString += hour;      qryString += ":";
            qryString += min;      qryString += ":";
            qryString += sec;      qryString += "')";

            QSqlQuery qry(db);

            if (firstOnOff) {
                QString onYear = (QDateTime::currentDateTime().toString("yyyy"));
                QString onMonth = (QDateTime::currentDateTime().toString("MM"));
                QString onDate = (QDateTime::currentDateTime().toString("dd"));
                QString hour = (QDateTime::currentDateTime().toString("hh"));
                QString min = (QDateTime::currentDateTime().toString("mm"));
                QString sec = (QDateTime::currentDateTime().toString("ss"));

                OnTime = onYear;    OnTime +="-";
                OnTime +=onMonth;   OnTime +="-";
                OnTime +=onDate;    OnTime +=" ";
                OnTime +=hour;      OnTime +=":";
                OnTime +=min;       OnTime +=":";
                OnTime +=sec;

                onOffqryString = "UPDATE sensors ";
                onOffqryString += "SET power=1, ";
                onOffqryString += "power_updated_at='";
                onOffqryString += OnTime;
                onOffqryString += "' ";

                onOffqryString += "WHERE id=";
                onOffqryString += QString::number(i);
            }



            if (!(db.open())) {
                qDebug() << "cannot open";
            }

            qry.prepare(onOffqryString);
            if (!qry.exec())

                qDebug() << "on off cannot insert";


            firstOnOff = false;

            qry.prepare(qryString);
            if (!qry.exec())

                qDebug() << "cannot insert";


            db.close();

        }

        else { //kick if no valid ID
            ProDis();
        }
    }

    Data.clear();
    timer->setInterval(15000); //reset to 15 second
    timer->start();

}

void dataThreadR::Dis() //normally disconnect
{
    if (!TO && !PRO) {

        QSqlQuery qry(db);
        QString year = (QDateTime::currentDateTime().toString("yyyy"));
        QString month = (QDateTime::currentDateTime().toString("MM"));
        QString date = (QDateTime::currentDateTime().toString("dd"));
        QString hour = (QDateTime::currentDateTime().toString("hh"));
        QString min = (QDateTime::currentDateTime().toString("mm"));
        QString sec = (QDateTime::currentDateTime().toString("ss"));

        onOffqryString = "UPDATE sensors ";
        onOffqryString += "SET power=0, ";
        onOffqryString += "power_updated_at='";
        onOffqryString += year;      onOffqryString += "-";
        onOffqryString += month;     onOffqryString += "-";
        onOffqryString += date;      onOffqryString += " ";
        onOffqryString += hour;      onOffqryString += ":";
        onOffqryString += min;     onOffqryString += ":";
        onOffqryString += sec;      onOffqryString += "' ";



        onOffqryString += "WHERE id=";
        onOffqryString += QString::number(i);


        if (!(db.open())) {
            qDebug() << "cannot open";
        }

        qry.prepare(onOffqryString);
        if (!qry.exec())

            qDebug() << "on off cannot insert";

        db.close();

        qDebug() << socketDescriptor << " noraml Disconnected";
        socket->deleteLater();
        this->exit();
    }
}

void dataThreadR::ProDis() //incorrect protocol!!
{
    PRO = true;

    QSqlQuery qry(db);
    QString year = (QDateTime::currentDateTime().toString("yyyy"));
    QString month = (QDateTime::currentDateTime().toString("MM"));
    QString date = (QDateTime::currentDateTime().toString("dd"));
    QString hour = (QDateTime::currentDateTime().toString("hh"));
    QString min = (QDateTime::currentDateTime().toString("mm"));
    QString sec = (QDateTime::currentDateTime().toString("ss"));

    onOffqryString = "UPDATE sensors ";
    onOffqryString += "SET power=0, ";
    onOffqryString += "power_updated_at='";
    onOffqryString += year;      onOffqryString += "-";
    onOffqryString += month;     onOffqryString += "-";
    onOffqryString += date;      onOffqryString += " ";
    onOffqryString += hour;      onOffqryString += ":";
    onOffqryString += min;     onOffqryString += ":";
    onOffqryString += sec;      onOffqryString += "' ";



    onOffqryString += "WHERE id=";
    onOffqryString += QString::number(i);


    if (!(db.open())) {
        qDebug() << "cannot open";
    }

    qry.prepare(onOffqryString);
    if (!qry.exec())

        qDebug() << "on off cannot insert";

    db.close();

    qDebug() << socketDescriptor << Data << " incorrect PTC Disconnected";
    socket->deleteLater();
    exit(0);
}

void dataThreadR::TODis() //timeout!!
{
    TO = true;

    QSqlQuery qry(db);
    QString year = (QDateTime::currentDateTime().toString("yyyy"));
    QString month = (QDateTime::currentDateTime().toString("MM"));
    QString date = (QDateTime::currentDateTime().toString("dd"));
    QString hour = (QDateTime::currentDateTime().toString("hh"));
    QString min = (QDateTime::currentDateTime().toString("mm"));
    QString sec = (QDateTime::currentDateTime().toString("ss"));

    onOffqryString = "UPDATE sensors ";
    onOffqryString += "SET power=0, ";
    onOffqryString += "power_updated_at='";
    onOffqryString += year;      onOffqryString += "-";
    onOffqryString += month;     onOffqryString += "-";
    onOffqryString += date;      onOffqryString += " ";
    onOffqryString += hour;      onOffqryString += ":";
    onOffqryString += min;     onOffqryString += ":";
    onOffqryString += sec;      onOffqryString += "' ";



    onOffqryString += "WHERE id=";
    onOffqryString += QString::number(i);


    if (!(db.open())) {
        qDebug() << "cannot open";
    }

    qry.prepare(onOffqryString);
    if (!qry.exec())

        qDebug() << "on off cannot insert";


    db.close();

    qDebug() << socketDescriptor << Data << " TO Disconnected";
    socket->deleteLater();
    this->exit();
}
