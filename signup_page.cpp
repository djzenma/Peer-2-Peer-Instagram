#include "signup_page.h"
#include "ui_signup_page.h"
#include "headers/Peer.h"
#include "account.h"
#include "mainwindow.h"
SignUp_Page::SignUp_Page(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SignUp_Page)
{
    ui->setupUi(this);
}

SignUp_Page::~SignUp_Page()
{
    delete ui;
}

void SignUp_Page::on_Signup_clicked()
{
    QString Username,Password;
    Username = ui->UsernameSU->text();
    Password = ui->PasswordSU->text();
    Peer *p = new Peer("127.0.0.1","aya");
    std::string res = p->authenticate(Username.toStdString(),Password.toStdString(), "10.40.55.101");
    if(res == "ok") {
        this->hide();
        Account a;
        a.setModal(true);
        a.exec();
    }
    else
    {
        ui->label_4->setText("No account");
//        this->hide();
//        MainWindow a;
//        a.show();

    }

}
