#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_dial_valueChanged(int value);

    void on_sliderColor_valueChanged(int value);

    void on_sliderH_valueChanged(int value);

    void on_radioDec_clicked();

    void on_radioBin_clicked();

    void on_radioOct_clicked();

    void on_radioHex_clicked();

    void on_sliderV_valueChanged(int value);

    void on_scrollBarV_sliderMoved(int position);

    void on_scrollBarH_sliderMoved(int position);

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
