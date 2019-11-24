#ifndef PICTURESICANVIEW_H
#define PICTURESICANVIEW_H

#include <QWidget>
#include <QDialog>
namespace Ui {
class PicturesIcanView;
}

class PicturesIcanView : public QDialog
{
    Q_OBJECT

public:
    explicit PicturesIcanView(QWidget *parent = nullptr);
    ~PicturesIcanView();
    //QString sendpicture(QString s);
    QString filename1;
    QString filename2;
    QString filename3;
    QString filename4;
    QString filename5;
    QString filename6;

private slots:
    void on_pushButton_14_clicked();

    void on_pushButton_15_clicked();

    void on_pushButton_17_clicked();

    void on_pushButton_clicked();


    void on_pushButton_2_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_18_clicked();

    void on_Signup_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::PicturesIcanView *ui;
};

#endif // PICTURESICANVIEW_H
