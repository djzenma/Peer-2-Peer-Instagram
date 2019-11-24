#ifndef FRIENDACCOUNT_H
#define FRIENDACCOUNT_H

#include <QWidget>
#include <QDialog>

namespace Ui {
class FriendAccount;
}

class FriendAccount : public QDialog
{
    Q_OBJECT

public:
    explicit FriendAccount(QWidget *parent = nullptr);
    ~FriendAccount();
    QString name;
    void getUsername(QString name);

private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_18_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_9_clicked();

private:
    Ui::FriendAccount *ui;
};

#endif // FRIENDACCOUNT_H
