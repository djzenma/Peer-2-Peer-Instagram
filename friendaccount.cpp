#include "friendaccount.h"
#include "ui_friendaccount.h"
#include "requests.h"
#include "account.h"
#include "homepage2.h"
#include "picturesicanview.h"
#include "profilesicanview.h"
#include "headers/Client.h"
#include "headers/Thread.h"
#include <string>
//#include "headers/utils.h"
FriendAccount::FriendAccount(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FriendAccount)
{
    ui->setupUi(this);
    QString filename1 = "/Users/ayashaker/Desktop/Distributed_Project2/images/requested/0.jpg";
    QString filename2 = "/Users/ayashaker/Desktop/Distributed_Project2/images/requested/1.jpg";
    QString filename3 = "/Users/ayashaker/Desktop/Distributed_Project2/images/requested/2.jpg";
    QString filename4 = "/Users/ayashaker/Desktop/Distributed_Project2/images/requested/3.jpg";
    QString filename5 = "/Users/ayashaker/Desktop/Distributed_Project2/images/requested/4.jpg";
    QString filename6 = "/Users/ayashaker/Desktop/Distributed_Project2/images/requested/5.jpg";
    QPixmap pix;
    QPixmap pix2;
    QPixmap pix3;
    QPixmap pix4;
    QPixmap pix5;
    QPixmap pix6;
    cout<<"IP num: "<< getIp("4")<<"Port Number"<<getPort("4")<<endl;

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
        ui->label_3->setPixmap(pix3.scaled(w,h));
    }
    if(pix4.load(filename4))
    {
        ui->label_4->setPixmap(pix4.scaled(w,h));
    }
    if(pix5.load(filename5))
    {
        ui->label_5->setPixmap(pix5.scaled(w,h));
    }
    if(pix6.load(filename6))
    {
        ui->label_6->setPixmap(pix6.scaled(w,h));
    }
}

FriendAccount::~FriendAccount()
{
    delete ui;
}
void FriendAccount::getUsername(QString name)
{
    ui->label_7->setText(name);
}

void FriendAccount::on_pushButton_3_clicked() // Home Page
{
    this->hide();
    homepage2 H;
    H.setModal(true);
    H.exec();
}

void FriendAccount::on_pushButton_4_clicked() // My Profile
{
    this->hide();
    Account A;
    A.setModal(true);
    A.exec();
}

void FriendAccount::on_pushButton_5_clicked() // Pics I can view
{
    this->hide();
    PicturesIcanView P;
    P.setModal(true);
    P.exec();
}


void FriendAccount::on_pushButton_18_clicked() // Profile I can view
{
    this->hide();
    profilesIcanView I;
    I.setModal(true);
    I.exec();
}

void FriendAccount::on_pushButton_10_clicked() // Requests
{
    this->hide();
    Requests R;
    R.setModal(true);
    R.exec();
}

void FriendAccount::on_pushButton_8_clicked() // First View
{
   Thread * thrd = new Thread(true , false ,  2 , 0 ,  "serverName",stoi(getPort("0")) , getIp("0") , getPort("0"),0);

}

void FriendAccount::on_pushButton_7_clicked() // Second
{
      Thread * thrd = new Thread(true , false ,  2 , 1 ,  "serverName",stoi(getPort("1")), getIp("1") , getPort("1"),0  );
}

void FriendAccount::on_pushButton_6_clicked() // Third
{
       Thread * thrd = new Thread(true , false ,  2 , 2 ,  "serverName",stoi(getPort("2")) , getIp("2") , getPort("2"),0  );
}
void FriendAccount::on_pushButton_clicked() // Fourth
{
       Thread * thrd = new Thread(true , false ,  2 , 3 ,  "serverName",stoi(getPort("3")) , getIp("3") , getPort("3"),0  );
}
void FriendAccount::on_pushButton_2_clicked() // Fifth
{
     Thread * thrd = new Thread(true , false ,  2 , 4 ,  "serverName",stoi(getPort("4")) , getIp("4") , getPort("4") ,0 );
}
void FriendAccount::on_pushButton_9_clicked() // Sixth
{
    Thread * thrd = new Thread(true , false ,  2 , 5 ,  "serverName",stoi(getPort("5")) , getIp("5") , getPort("5") ,0 );
}
