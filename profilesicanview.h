#ifndef PROFILESICANVIEW_H
#define PROFILESICANVIEW_H

#include <QWidget>
#include <QDialog>

namespace Ui {
class profilesIcanView;
}

class profilesIcanView : public QDialog
{
    Q_OBJECT

public:
    explicit profilesIcanView(QWidget *parent = nullptr);
    ~profilesIcanView();

private slots:
    void on_pushButton_14_clicked();

    void on_pushButton_15_clicked();

    void on_pushButton_16_clicked();

    void on_pushButton_18_clicked();

    void on_pushButton_17_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_Signup_clicked();

private:
    Ui::profilesIcanView *ui;
};

#endif // PROFILESICANVIEW_H
