#include "profilesicanview.h"
#include "ui_profilesicanview.h"
#include "requests.h"
#include "account.h"
#include "homepage2.h"
#include "viewpicture.h"
#include "picturesicanview.h"
#include "friendaccount.h"
#include "mainwindow.h"
#include "headers/Client.h"
profilesIcanView::profilesIcanView(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::profilesIcanView)
{
    ui->setupUi(this);

}

profilesIcanView::~profilesIcanView()
{
    delete ui;
}

void profilesIcanView::on_pushButton_14_clicked() //Home Page
{
    this->hide();
    homepage2 H;
    H.setModal(true);
    H.exec();
}

void profilesIcanView::on_pushButton_15_clicked() // My Profile
{
    this->hide();
    Account A;
    A.setModal(true);
    A.exec();
}

void profilesIcanView::on_pushButton_16_clicked()// Pictures I can view
{
    this->hide();
    PicturesIcanView P;
    P.setModal(true);
    P.exec();
}
void profilesIcanView::on_pushButton_18_clicked()//Profiles I can view
{

}
void profilesIcanView::on_pushButton_17_clicked()//Requests
{
    this->hide();
    Requests R;
    R.setModal(true);
    R.exec();
}
void profilesIcanView::on_pushButton_clicked()
{
    this->hide();
    FriendAccount F;
    F.setModal(true);
    F.getUsername(ui->label_2->text());
    F.exec();
}

void profilesIcanView::on_pushButton_2_clicked()
{
    this->hide();
    FriendAccount F;
    F.setModal(true);
    F.getUsername(ui->label_3->text());
    F.exec();

}

void profilesIcanView::on_pushButton_3_clicked()
{
    this->hide();
    FriendAccount F;
    F.setModal(true);
    F.getUsername(ui->label_4->text());
    F.exec();
}

void profilesIcanView::on_pushButton_4_clicked()
{
    this->hide();
    FriendAccount F;
    F.setModal(true);
    F.getUsername(ui->label_5->text());
    F.exec();
}

void profilesIcanView::on_Signup_clicked()
{
    this->hide();
    MainWindow M;
    M.setWindowModality(Qt::ApplicationModal);
    M.show();
}
