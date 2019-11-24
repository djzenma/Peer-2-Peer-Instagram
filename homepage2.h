#ifndef HOMEPAGE2_H
#define HOMEPAGE2_H

#include <QWidget>
#include <QDialog>

namespace Ui {
class homepage2;
}

class homepage2 : public QDialog
{
    Q_OBJECT

public:
    explicit homepage2(QWidget *parent = nullptr);

    ~homepage2();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_18_clicked();

    void on_Signup_clicked();

private:
    Ui::homepage2 *ui;
};

#endif // HOMEPAGE2_H
