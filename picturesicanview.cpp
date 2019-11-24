#include "picturesicanview.h"
#include "ui_picturesicanview.h"
#include "requests.h"
#include "account.h"
#include "homepage2.h"
#include "viewpicture.h"
#include "profilesicanview.h"
#include "mainwindow.h"
#include "headers/Client.h"
PicturesIcanView::PicturesIcanView(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PicturesIcanView)
{
    ui->setupUi(this);
    filename1 = "/Users/ayashaker/Desktop/Distributed_Project2/images/requested/0.jpg";
    filename2 = "/Users/ayashaker/Desktop/Distributed_Project2/images/requested/1.jpg";
    filename3 = "/Users/ayashaker/Desktop/Distributed_Project2/images/requested/2.jpg";
    filename4 = "/Users/ayashaker/Desktop/Distributed_Project2/images/requested/3.jpg";
    filename5 = "/Users/ayashaker/Desktop/Distributed_Project2/images/requested/4.jpg";
    filename6 = "/Users/ayashaker/Desktop/Distributed_Project2/images/requested/5.jpg";
    QPixmap pix;
    QPixmap pix2;
    QPixmap pix3;
    QPixmap pix4;
    QPixmap pix5;
    QPixmap pix6;

    int w = ui->label_3->width();
    int h = ui->label_3->height();
    if(pix.load(filename1))
       {

         ui->label->setPixmap(pix.scaled(w,h));
    }
    if(pix2.load(filename2))
    {
         ui->label_2->setPixmap(pix2.scaled(w,h));
    }
    if(pix3.load(filename3))
    {
        ui->label_4->setPixmap(pix3.scaled(w,h));
    }
    if(pix4.load(filename4))
    {
        ui->label_5->setPixmap(pix4.scaled(w,h));
    }
    if(pix5.load(filename5))
    {
        ui->label_6->setPixmap(pix5.scaled(w,h));
    }
    if(pix6.load(filename6))
    {
        ui->label_3->setPixmap(pix6.scaled(w,h));
    }


}

PicturesIcanView::~PicturesIcanView()
{
    delete ui;
}

void PicturesIcanView::on_pushButton_14_clicked() // Home page
{
    this->hide();
    homepage2 H;
    H.setModal(true);
    H.exec();
}

void PicturesIcanView::on_pushButton_15_clicked() // My Profile
{
    this->hide();
    Account A;
    A.setModal(true);
    A.exec();
}

void PicturesIcanView::on_pushButton_17_clicked() // Requests
{
    this->hide();
    Requests R;
    R.setModal(true);
    R.exec();
}

void PicturesIcanView::on_pushButton_clicked()
{
    this->hide();
    ViewPicture V;
    V.setModal(true);
    V.recieveimage(filename4);
    V.exec();
}

void PicturesIcanView::on_pushButton_2_clicked()
{
    this->hide();
    ViewPicture V;
    V.setModal(true);
    V.recieveimage(filename5);
    V.exec();
}

void PicturesIcanView::on_pushButton_6_clicked()
{
    this->hide();
    ViewPicture V;
    V.setModal(true);
    V.recieveimage(filename3);
    V.exec();
}

void PicturesIcanView::on_pushButton_18_clicked()
{
    this->hide();
    profilesIcanView I;
    I.setModal(true);
    I.exec();
}

void PicturesIcanView::on_Signup_clicked()
{
    this->hide();
    MainWindow M;
    M.setWindowModality(Qt::ApplicationModal);
    M.show();
}

void PicturesIcanView::on_pushButton_5_clicked()
{
    this->hide();
    ViewPicture V;
    V.setModal(true);
    V.recieveimage(filename1);
    V.exec();

}

void PicturesIcanView::on_pushButton_4_clicked()
{
    this->hide();
    ViewPicture V;
    V.setModal(true);
    V.recieveimage(filename2);
    V.exec();
}

void PicturesIcanView::on_pushButton_3_clicked()
{
    this->hide();
    ViewPicture V;
    V.setModal(true);
    V.recieveimage(filename6);
    V.exec();
}
