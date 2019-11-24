#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <QDialog>

namespace Ui {
class HomePage;
}

class HomePage : public QDialog
{
    Q_OBJECT

public:
    explicit HomePage(QWidget *parent = nullptr);
    ~HomePage();

private:
    Ui::HomePage *ui;
};

#endif // HOMEPAGE_H
