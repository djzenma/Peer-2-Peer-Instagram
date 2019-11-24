#include "homepage2.h"
#include "ui_homepage2.h"
#include <QPushButton>
#include <QVBoxLayout>
#include "account.h"
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QStyleFactory>
#include "requests.h"
#include "profilesicanview.h"
#include "src/utils.cpp"
#include "picturesicanview.h"
#include "mainwindow.h"
#include "headers/Thread.h"
homepage2::homepage2(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::homepage2)
{
    ui->setupUi(this);
    int w = ui->label_3->width();
    int h = ui->label_3->height();
    QString filename = "/Users/ayashaker/Desktop/Distributed_Project2/images/requested/0.jpg";
    QString filename2 = "/Users/ayashaker/Desktop/Distributed_Project2/images/requested/1.jpg";
    QString filename3 = "/Users/ayashaker/Desktop/Distributed_Project2/images/requested/2.jpg";
    QPixmap pix;
    QPixmap pix2;
    QPixmap pix3;

    if(pix.load(filename))
       {

         ui->label_3->setPixmap(pix.scaled(w,h));
         ui->label_7->setPixmap(pix.scaled(w,h));
    }
    if(pix2.load(filename2))
       {

         ui->label_4->setPixmap(pix2.scaled(w,h));
         ui->label_8->setPixmap(pix2.scaled(w,h));
    }
    if(pix3.load(filename3))
       {

         ui->label_5->setPixmap(pix3.scaled(w,h));
         ui->label_9->setPixmap(pix3.scaled(w,h));
    }

     QFrame *b = new QFrame;
     b->setStyle(QStyleFactory::create("Fusion"));
}

homepage2::~homepage2()
{
    delete ui;
}

void homepage2::on_pushButton_2_clicked()
{
    this->hide();
    Account A;
    A.setModal(true);
    A.exec();
}

void homepage2::on_pushButton_clicked()//My Profile Button
{

}

void homepage2::on_pushButton_5_clicked() // Send request to view samples
{
    Thread * thrd = new Thread(true , false , 1, 4  ,  false, stoi(getIp("4")),   getIp("4")  , getPort("4"),4 );
}

void homepage2::on_pushButton_4_clicked() // Send Requests
{
    this->hide();
    Requests R;
    R.setModal(true);
    R.exec();
}

void homepage2::on_pushButton_3_clicked()
{
    this->hide();
    PicturesIcanView P;
    P.setModal(true);
    P.exec();
}

void homepage2::on_pushButton_18_clicked()
{
    this->hide();
    profilesIcanView I;
    I.setModal(true);
    I.exec();
}
void homepage2::on_Signup_clicked()
{
    this->hide();
    MainWindow M;
    //M.setWindowModality(Qt::ApplicationModal);
    M.show();
}
