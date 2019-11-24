#ifndef REQUESTS_H
#define REQUESTS_H

#include <QDialog>

namespace Ui {
class Requests;
}

class Requests : public QDialog
{
    Q_OBJECT

public:
    explicit Requests(QWidget *parent = nullptr);
    ~Requests();

private slots:
    void on_pushButton_14_clicked();

    void on_pushButton_15_clicked();

    void on_pushButton_16_clicked();

    void on_pushButton_18_clicked();

    void on_Signup_clicked();

private:
    Ui::Requests *ui;
};

#endif // REQUESTS_H
