#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QMessageBox>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QStandardItem>
#include <QJsonArray>
#include <QString>
#include <QVector>

#include "messanger.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QByteArray Data;
    QTcpSocket* socket;
    QJsonDocument doc;
    QJsonParseError docError;
    QString login;
    QString password;
    QVector<QString> logpassuser;

    bool authorization;
    bool chat;

public slots:
    void sockReady();
    void sockDisc();
    void slotForm(QString addlog, QString addpass);
private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;

    messanger* mes;
};
#endif // MAINWINDOW_H
