#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    socket = new QTcpSocket(this);
    chat = false;


    socket->connectToHost("127.0.0.1", 5555);
    connect(socket,SIGNAL(readyRead()),this,SLOT(sockReady()));
    connect(socket,SIGNAL(disconnected()),this,SLOT(sockDisc()));

    mes = new messanger();
    mes->setWindowFlags(Qt::WindowStaysOnTopHint);
    mes->setGeometry(751,638,mes->size().width(),mes->size().height());

    mes->show();
    connect(mes,&messanger::signalForm,this,&MainWindow::slotForm);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    QByteArray log = login.toUtf8();;
    QByteArray to = ui->comboBox->currentText().toUtf8();
    QByteArray mes = ui->lineEdit->text().toUtf8();
    QByteArray message = "{\"from\":\"" + log +"\",\"to\":\"" + to + "\",\"mess\":\" "+mes+"\"} " ;
    chat = true;
    socket->write("{\"type\":\"message\",\"params\":"+message+"}");
    socket->waitForBytesWritten(500);

}

void MainWindow::sockDisc()
{
    socket->deleteLater();
}

void MainWindow::slotForm(QString addlog, QString addpass)
{
    login = addlog;
    password = addpass;
    authorization = false;
    socket->write("{\"type\":\"select\",\"params\":\"users\"}");
    socket->waitForBytesWritten(500);
}


void MainWindow::sockReady()
{
    if(socket->waitForConnected(500))
    {
        socket->waitForReadyRead(500);
        Data = socket->readAll();

        doc = QJsonDocument::fromJson(Data, &docError);
        if (docError.errorString()=="no error occurred")
        {
            if(doc.object().value("type").toString() == "connect" && (doc.object().value("status").toString()=="yes"))
            {
                QMessageBox::information(this,"Информация", "Соединение установлено");
            }
            else if(doc.object().value("type").toString()=="resultSelect")
            {

                QJsonArray docAr = doc.object().value("result").toArray();
                for(int i = 0; i<docAr.count();i++)
                {
                    if((docAr[i].toObject().value("login").toString() == login) && (docAr[i].toObject().value("password").toString() == password) ){
                        this->show();
                        mes->hide();
                        authorization = true;
                        break;
                    }
                }

                if(authorization == false ){
                    QMessageBox::information(this,"Информация", "Неправильный логин или пароль");
                }
                else{
                    for(int i = 0; i<docAr.count();i++)
                    {
                        QString addcombox = (docAr[i].toObject().value("login").toString()) ;
                        if(addcombox != login){
                            ui->comboBox->addItem(addcombox);
                        }
                    }
                }
            }
            else if(chat == true)
            {

                QJsonArray docAr = doc.object().value("messageeback").toArray();
                ui->textEdit->clear();
                for(int i = 0; i<docAr.count();i++)
                {
                    if((docAr[i].toObject().value("from").toString() == login) && (docAr[i].toObject().value("to").toString() == ui->comboBox->currentText()) ||
                        (docAr[i].toObject().value("from").toString() == ui->comboBox->currentText()) && (docAr[i].toObject().value("to").toString() == login) ){
                        ui->textEdit->append(docAr[i].toObject().value("from").toString()+": "+docAr[i].toObject().value("mess").toString());;
                    }
                }

            }

        }
        else
        {
            QMessageBox::information(this,"Информация", "Ошибка с форматом передачи данных"+docError.errorString());
        }

    }
}


