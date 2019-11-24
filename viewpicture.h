#ifndef VIEWPICTURE_H
#define VIEWPICTURE_H
#include<string.h>
#include <QWidget>
#include <QDialog>

namespace Ui {
class ViewPicture;
}

class ViewPicture : public QDialog
{
    Q_OBJECT

public:
    QString s;
    explicit ViewPicture(QWidget *parent = nullptr);
    ~ViewPicture();
   void recieveimage(QString s);

private slots:
   void on_pushButton_14_clicked();

   void on_pushButton_15_clicked();

   void on_pushButton_16_clicked();

   void on_pushButton_17_clicked();

   void on_pushButton_18_clicked();

   void on_Signup_clicked();

private:
    Ui::ViewPicture *ui;
};

#endif // VIEWPICTURE_H
