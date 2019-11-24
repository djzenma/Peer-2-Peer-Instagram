#include "requests.h"
#include "ui_requests.h"
#include "account.h"
#include "homepage2.h"
#include "picturesicanview.h"
#include "profilesicanview.h"
#include "mainwindow.h"
#include "headers/Client.h"
Requests::Requests(QWidget *parent) :
    QDialog (parent),
    ui(new Ui::Requests)
{
    ui->setupUi(this);
}

Requests::~Requests()
{
    delete ui;
}

void Requests::on_pushButton_14_clicked() // Home Page
{
    this->hide();
    homepage2 H;
    H.setModal(true);
    H.exec();
}

void Requests::on_pushButton_15_clicked() //My Profile
{

    this->hide();
    Account A;
    A.setModal(true);
    A.exec();

}


void Requests::on_pushButton_16_clicked()
{
    this->hide();
    PicturesIcanView P;
    P.setModal(true);
    P.exec();
}

void Requests::on_pushButton_18_clicked() //Profiles I can view
{
    this->hide();
    profilesIcanView I;
    I.setModal(true);
    I.exec();
}

void Requests::on_Signup_clicked()
{
    this->hide();
    MainWindow M;
    M.setWindowModality(Qt::ApplicationModal);
    M.show();
}
