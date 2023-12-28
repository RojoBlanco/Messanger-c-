#ifndef MYSERVER_H
#define MYSERVER_H


#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QFile>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QJsonArray>

class MyServer: public QTcpServer
{
    Q_OBJECT
public:
    MyServer();
    ~MyServer();

    QTcpSocket* socket;
    QByteArray Data;

    QJsonDocument doc;
    QJsonParseError docError;

    QSqlDatabase db;
public slots:
    void startServer();
    void incomingConnection(qintptr socketDescriptor);
    void sockReady();
    void sockDisc();

};

#endif // MYSERVER_H
