#ifndef SIGNUP_PAGE_H
#define SIGNUP_PAGE_H

#include <QDialog>

namespace Ui {
class SignUp_Page;
}

class SignUp_Page : public QDialog
{
    Q_OBJECT

public:
    explicit SignUp_Page(QWidget *parent = nullptr);
    ~SignUp_Page();

private slots:
    void on_Signup_clicked();

private:
    Ui::SignUp_Page *ui;
};

#endif // SIGNUP_PAGE_H
