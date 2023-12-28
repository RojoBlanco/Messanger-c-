#include "messanger.h"
#include "ui_messanger.h"

messanger::messanger(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::messanger)
{
    ui->setupUi(this);
}

messanger::~messanger()
{
    delete ui;
}

void messanger::on_pushButton_clicked()
{
    login = ui->lineEdit->text();
    password = ui->lineEdit_2->text();

    emit signalForm(login,password);
}

