#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>

#include "person.h"

namespace Ui {
class MyWidget;
}

class MyWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MyWidget(QWidget *parent = 0);
    ~MyWidget();

private slots:
    void on_btnBoyInc_clicked();

    void on_btnGirlInc_clicked();

    void on_btnClassInfo_clicked();

    void on_btnClear_clicked();

    void on_ageChanged(int value);
    void on_spin_valueChanged(int arg1);

private:
    Ui::MyWidget *ui;

    Person *boy;
    Person *girl;
};

#endif // MYWIDGET_H
