#include "headers/DoS.h"
#include <string>
#include "headers/Communication.h"
#include "headers/Thread.h"
#include <iostream>
#include "mainwindow.h"
#include <QApplication>

using namespace std;

int main(int argc,char **argv)
{
    int reqNum = -1 ;
    string serverName;
    int image_id;
    Thread * thrd = new Thread(false , true , reqNum, image_id  ,  true, 4040,  "" ,"", 0);
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return  a.exec();
}



