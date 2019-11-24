#include "account.h"
#include "ui_account.h"
#include "mainwindow.h"
#include <QDialog>
#include "homepage2.h"
#include "requests.h"
#include "headers/Client.h"
#include "picturesicanview.h"
#include "profilesicanview.h"
#include "src/imageinfo.h"
#include "headers/Thread.h"
Account::Account(QDialog *parent) :
    QDialog(parent),
    ui(new Ui::Account)
{
    ui->setupUi(this);
    int w = ui->label_7->width();
    int h = ui->label_7->height();
    QString filename1 = "/Users/ayashaker/Desktop/pic1.png";
    QString filename2 = "/Users/ayashaker/Desktop/pic2.png";
    QString filename3 = "/Users/ayashaker/Desktop/pic3.png";
    QString filename4 = "/Users/ayashaker/Desktop/pic4.png";
    QString filename5 = "/Users/ayashaker/Desktop/pic5.png";
    QString filename6 = "/Users/ayashaker/Desktop/pic6.png";
    QPixmap pix;
    if(pix.load(filename1))
       {
         ui->label_7->setPixmap(pix.scaled(w,h));
         }
    if(pix.load(filename2))
       {
         ui->label_6->setPixmap(pix.scaled(w,h));
         }
    if(pix.load(filename3))
       {
         ui->label_5->setPixmap(pix.scaled(w,h));
         }
    if(pix.load(filename4))
       {
         ui->label_4->setPixmap(pix.scaled(w,h));
         }
    if(pix.load(filename5))
       {
         ui->label_3->setPixmap(pix.scaled(w,h));
         }
    if(pix.load(filename6))
       {
         ui->label_2->setPixmap(pix.scaled(w,h));
         }
}
Account::~Account()
{
    delete ui;
}


void Account::on_pushButton_7_clicked() //My Profile
{
    //Thread * thrd = new Thread(true , false ,  0 , 4 ,  "aya");
    //Thread * thrd = new Thread(true , false ,  0 , 4 ,  "serverName",5050 , getIp("2") , getPort("2"),0  );
    this->hide();
    homepage2 H;
    H.setModal(true);
    H.exec();
}
void Account::on_pushButton_9_clicked()
{
    this->hide();
    Requests R;
    R.setModal(true);
    R.exec();
}

void Account::on_pushButton_10_clicked()
{
    this->hide();
    PicturesIcanView P;
    P.setModal(true);
    P.exec();
}

void Account::on_pushButton_18_clicked()
{
    this->hide();
    profilesIcanView I;
    I.setModal(true);
    I.exec();
}

void Account::on_Signup_clicked()
{
    this->hide();
    MainWindow M;
    M.setWindowModality(Qt::ApplicationModal);
    M.show();

}

void Account::on_Signup_2_clicked()
{
    this->hide();
    ImageInfo m;
    m.setModal(true);
    m.exec();

}

void Account::on_Signup_3_clicked()
{
    this->hide();
    ImageInfo m;
    m.setModal(true);
    m.exec();

}

void Account::on_Signup_4_clicked()
{
    this->hide();
    ImageInfo m;
    m.setModal(true);
    m.exec();
}

void Account::on_Signup_5_clicked()
{
    this->hide();
    ImageInfo m;
    m.setModal(true);
    m.exec();
}

void Account::on_Signup_6_clicked()
{
    this->hide();
    ImageInfo m;
    m.setModal(true);
    m.exec();
}

void Account::on_Signup_7_clicked()
{
    this->hide();
    ImageInfo m;
    m.setModal(true);
    m.exec();
}
