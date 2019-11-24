//#ifndef RUNBACKGROUND_H
//#define RUNBACKGROUND_H
//#include <pthread.h>
//#include <thread>
//#include <string>
//#include "../headers/Client.h"
//#include "../headers/Server.h"
//#include <QDialog>

//namespace Ui {
//class runbackground;
//}

//class runbackground : public QDialog
//{
//    Q_OBJECT

//public:
//    explicit runbackground(QWidget *parent = nullptr);
//    ~runbackground();
//    #define NUM_THREADS 2

//   static pthread_t threads[NUM_THREADS];
//    const char* hostname ;
//    const char* port ;
//    bool cli = false ;
//    struct client{
//    static void client_thread()
//    {
//        Client * c = new Client("127.0.0.1", "4040"); //always run on local ip
//        c->executePrompt(0);
//        pthread_cancel(threads[1]);
//        pthread_exit(NULL);
//    }
//    };
//    struct server{
//    static void server_thread()
//    {
//        bool cli = true;
//        Server* s = new Server("127.0.0.1", "4040"); //needs to connect to client thus gets ip and port from argsv
//           while(1) {
//               if (cli == true) {
//                   client *c;
//                   std::thread t1 (&client::client_thread,&c);
//                   t1.join();
//               } else
//                   s->serveRequest();
//           }
//    }
//    };
//private:
//    Ui::runbackground *ui;
//};

//#endif // RUNBACKGROUND_H
