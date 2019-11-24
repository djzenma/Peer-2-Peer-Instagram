#include "imageinfo.h"
#include "ui_imageinfo.h"
#include "/Users/ayashaker/Desktop/Distributed_Project2/requests.h"
#include "/Users/ayashaker/Desktop/Distributed_Project2/account.h"
#include "/Users/ayashaker/Desktop/Distributed_Project2/homepage2.h"
#include "/Users/ayashaker/Desktop/Distributed_Project2/picturesicanview.h"
#include "/Users/ayashaker/Desktop/Distributed_Project2/profilesicanview.h"
#include "/Users/ayashaker/Desktop/Distributed_Project2/mainwindow.h"
ImageInfo::ImageInfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ImageInfo)
{
    ui->setupUi(this);
}

ImageInfo::~ImageInfo()
{
    delete ui;
}
void ImageInfo::on_pushButton_clicked()
{
    QString Number;
    Number = ui->lineEdit->text();
    ui->label_17->setText(Number);
}

void ImageInfo::on_pushButton_2_clicked()
{
    QString Number;
    Number = ui->lineEdit_2->text();
    ui->label_18->setText(Number);

}

void ImageInfo::on_pushButton_3_clicked()
{
    QString Number;
    Number = ui->lineEdit_3->text();
    ui->label_19->setText(Number);
}

void ImageInfo::on_pushButton_4_clicked()
{
    QString Number;
    Number = ui->lineEdit_4->text();
    ui->label_20->setText(Number);
}

void ImageInfo::on_pushButton_5_clicked()
{
    QString Number;
    Number = ui->lineEdit_5->text();
    ui->label_21->setText(Number);
}

void ImageInfo::on_pushButton_6_clicked()
{
    QString Number;
    Number = ui->lineEdit_6->text();
    ui->label_22->setText(Number);
}

void ImageInfo::on_pushButton_7_clicked()
{
    QString Number;
    Number = ui->lineEdit_7->text();
    ui->label_23->setText(Number);

}

void ImageInfo::on_pushButton_14_clicked() //Home page
{
    this->hide();
    homepage2 H;
    H.setModal(true);
    H.exec();
}

void ImageInfo::on_pushButton_15_clicked() // My Profile
{
    this->hide();
    Account A;
    A.setModal(true);
    A.exec();
}

void ImageInfo::on_pushButton_16_clicked() // Pictures I can view
{
    this->hide();
    PicturesIcanView P;
    P.setModal(true);
    P.exec();
}

void ImageInfo::on_pushButton_18_clicked() // Profiles I can view
{
    this->hide();
    profilesIcanView I;
    I.setModal(true);
    I.exec();
}

void ImageInfo::on_pushButton_17_clicked() // Requests
{
    this->hide();
    Requests R;
    R.setModal(true);
    R.exec();

}
