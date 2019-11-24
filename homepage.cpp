#include "homepage.h"
#include "ui_homepage.h"
#include <QPushButton>
#include <QVBoxLayout>
HomePage::HomePage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HomePage)
{
    ui->setupUi(this);
    QString filename = "/Users/ayashaker/Desktop/instagram-trends-940x470.jpg";
    QPixmap pix;
    if(pix.load(filename))
       {
//        int w = ui->label_11->width();
//        int h = ui->label_11->height();
//         ui->label_11->setPixmap(pix.scaled(w,h));
//         ui->label_12->setPixmap(pix.scaled(w,h));
//         ui->label_13->setPixmap(pix.scaled(w,h));
//         ui->label_29->setPixmap(pix.scaled(w,h));
//         ui->label_30->setPixmap(pix.scaled(w,h));
//         ui->label_31->setPixmap(pix.scaled(w,h));
        QVBoxLayout *lay = new QVBoxLayout(this);
        for (int i=0;i<15;i++)
        {
        QPushButton *b = new QPushButton("Hello");
        lay ->addWidget(b);
        }

    //ui->scrollContents->setLayout(lay);

    }
}

HomePage::~HomePage()
{
    delete ui;
}
