//#include "runbackground.h"
//#include "ui_runbackground.h"
//#include <pthread.h>
//#include <thread>
//runbackground::runbackground(QWidget *parent) :
//    QDialog(parent),
//    ui(new Ui::runbackground)
//{
//    ui->setupUi(this);
//    server *s;
//    std::thread t2 (&server::server_thread,&s);
//    t2.join();
//}
////void runbackground::client_thread()
////{
////    Client * c = new Client("127.0.0.1", "4040"); //always run on local ip
////    c->executePrompt(0);
////    pthread_cancel(threads[1]);
////    pthread_exit(NULL);
////}
////void runbackground::server_thread()
////{
////    bool cli = true;
////    Server* s = new Server("127.0.0.1", "4040"); //needs to connect to client thus gets ip and port from argsv
////       while(1) {
////           if (cli == true) {
////               std::thread t1 (&runbackground::client_thread);
////               t1.join();
////           } else
////               s->serveRequest();
////       }
////}
//runbackground::~runbackground()
//{
//    delete ui;
//}
