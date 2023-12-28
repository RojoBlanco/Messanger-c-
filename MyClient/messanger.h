#ifndef MESSANGER_H
#define MESSANGER_H

#include <QWidget>
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



namespace Ui {
class messanger;
}

class messanger : public QWidget
{
    Q_OBJECT

public:
    explicit messanger(QWidget *parent = nullptr);
    ~messanger();

    QString login;
    QString password;
    QVector<QString> logpass;
public slots:
private slots:
    void on_pushButton_clicked();

private:
    Ui::messanger *ui;

signals:
    void signalForm(QString,QString);

};

#endif // MESSANGER_H
