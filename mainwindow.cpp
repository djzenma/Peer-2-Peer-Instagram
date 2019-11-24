#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "account.h"
#include "headers/Client.h"
#include "headers/Peer.h"
#include "headers/Thread.h"
const char* hostname1 ;
const char* port1 ;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_Login_clicked()
{
    QString Username,Password;
    Username = ui->Username->text();
    Password = ui->Password->text();
    Peer *p = new Peer("127.0.0.1","aya");
    std::string res = p->login(Username.toStdString(),Password.toStdString(), "10.40.55.101");

    if(res == "ok") {
        this->hide();
        Account a;
        a.setModal(true);
        a.exec();
    }
    else
    {
        ui->label_5->setText("No account");
    }


}
void MainWindow::on_Signup_clicked()
{
    this->hide();
    SignUp_Page signup;
    signup.setModal(true);
    signup.exec();
}
