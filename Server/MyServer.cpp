#include "MyServer.h"

MyServer::MyServer(){}
MyServer::~MyServer(){}

void MyServer::startServer()
{
    if(this->listen(QHostAddress::Any, 5555)){

        qDebug()<<"Listening";
    }
    else
    {
        qDebug()<<"Not Listening";
    }
}

void MyServer::incomingConnection(qintptr socketDescriptor){
    socket = new QTcpSocket(this);
    socket ->setSocketDescriptor(socketDescriptor);

    connect(socket,SIGNAL(readyRead()),this,SLOT(sockReady()));
    connect(socket,SIGNAL(disconnected()),this,SLOT(sockDisc()));
    qDebug()<<socketDescriptor<<"Conected";
    socket->write("{\"type\":\"connect\",\"status\":\"yes\"}");
    qDebug()<<"Send message conected status";

}


void MyServer::sockReady()
{
    Data = socket->readAll();
    doc = QJsonDocument::fromJson(Data, &docError);

    if (docError.errorString() == "no error occurred")
    {
        if((doc.object().value("type").toString() == "select") &&(doc.object().value("params").toString() == "users") )
        {
            QFile file;
            file.setFileName("B:\\Last\\Server\\users.json");
            if(file.open(QIODevice::ReadOnly|QFile::Text))
            {
                QByteArray fromFile = file.readAll();
                QByteArray itog = "{\"type\":\"resultSelect\", \"result\":" +fromFile+"}";

                socket->write(itog);
                socket->waitForBytesWritten(500);
            }
            file.close();
        }
        else if((doc.object().value("type").toString() == "message")){
            QFile file;
            QByteArray fromFile;
            file.setFileName("B:\\Last\\Server\\messages.json");
            if(file.open(QIODevice::ReadOnly|QFile::Text))
            {

               fromFile = file.readAll();
            }
            file.close();

                QJsonDocument doc1 = QJsonDocument::fromJson(fromFile, &docError);

                QJsonArray doctowrite = doc1.object().value("messageeback").toArray();

                doctowrite.append(doc.object().value("params"));
                doc1.setArray(doctowrite);
                if(file.open(QIODevice::WriteOnly))
                {
                file.write("{\"messageeback\":" + doc1.toJson()+"}") ;}
            file.close();
                if(file.open(QIODevice::ReadOnly|QFile::Text))
                {
                QByteArray fromFile = file.readAll();
                QByteArray itog = fromFile;

                socket->write(itog);
                socket->waitForBytesWritten(500);
                }
                file.close();
        }
    }
}

void MyServer::sockDisc(){
    qDebug()<<"disconect";
    socket->deleteLater();
}
