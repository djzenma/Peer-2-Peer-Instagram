#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include"/Users/ayashaker/Desktop/Distributed_Project2/signup_page.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_Login_clicked();

    void on_Signup_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
