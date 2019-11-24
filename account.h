#ifndef ACCOUNT_H
#define ACCOUNT_H
#include <QDialog>
namespace Ui {
class Account;
}

class Account : public QDialog
{
    Q_OBJECT

public:
    explicit Account(QDialog *parent = nullptr);
    ~Account();

private slots:
    void on_pushButton_7_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_18_clicked();

    void on_Signup_clicked();

    void on_Signup_2_clicked();

    void on_Signup_3_clicked();

    void on_Signup_4_clicked();

    void on_Signup_5_clicked();

    void on_Signup_6_clicked();

    void on_Signup_7_clicked();

private:
    Ui::Account *ui;
};
#endif // ACCOUNT_H
