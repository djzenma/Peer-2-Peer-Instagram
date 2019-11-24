#include "viewpicture.h"
#include "ui_viewpicture.h"
#include "requests.h"
#include "account.h"
#include "homepage2.h"
#include "picturesicanview.h"
#include "profilesicanview.h"
#include "mainwindow.h"
#include "headers/Client.h"
ViewPicture::ViewPicture(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ViewPicture)
{
    ui->setupUi(this);
}

ViewPicture::~ViewPicture()
{
    delete ui;
}
void ViewPicture::recieveimage(QString s)
{
    QPixmap pix;
    int w = ui->label->width();
    int h = ui->label->height();
    if(pix.load(s))
       {
     ui->label->setPixmap(pix.scaled(w,h));
     ui->label->setPixmap(pix.scaled(w,h));
        }

}

void ViewPicture::on_pushButton_14_clicked() //HomePage
{
    this->hide();
    homepage2 H;
    H.setModal(true);
    H.exec();
}

void ViewPicture::on_pushButton_15_clicked() // My Profile
{
    this->hide();
    Account A;
    A.setModal(true);
    A.exec();
}


void ViewPicture::on_pushButton_16_clicked() // Pictures I can View
{
    this->hide();
    PicturesIcanView P;
    P.setModal(true);
    P.exec();
}

void ViewPicture::on_pushButton_17_clicked() // Requests
{
    this->hide();
    Requests R;
    R.setModal(true);
    R.exec();
}

void ViewPicture::on_pushButton_18_clicked()
{
    this->hide();
    profilesIcanView I;
    I.setModal(true);
    I.exec();
}

void ViewPicture::on_Signup_clicked() // Signout
{
    this->hide();
    MainWindow M;
    M.setWindowModality(Qt::ApplicationModal);
    M.show();
}
