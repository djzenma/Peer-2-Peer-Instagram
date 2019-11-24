#ifndef IMAGEINFO_H
#define IMAGEINFO_H

#include <QWidget>
#include <QDialog>

namespace Ui {
class ImageInfo;
}

class ImageInfo : public QDialog
{
    Q_OBJECT

public:
    explicit ImageInfo(QWidget *parent = nullptr);
    ~ImageInfo();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_14_clicked();

    void on_pushButton_15_clicked();

    void on_pushButton_16_clicked();

    void on_pushButton_18_clicked();

    void on_pushButton_17_clicked();

private:
    Ui::ImageInfo *ui;
};

#endif // IMAGEINFO_H
