#include "widget.h"
#include "ui_widget.h"

#include <QColor>
#include <QPalette>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    connect(ui->sliderRed, SIGNAL(valueChanged(int)), this, SLOT(on_sliderColor_valueChanged(int)));
    connect(ui->sliderGreen, SIGNAL(valueChanged(int)), this, SLOT(on_sliderColor_valueChanged(int)));
    connect(ui->sliderBlue, SIGNAL(valueChanged(int)), this, SLOT(on_sliderColor_valueChanged(int)));
    connect(ui->sliderAlpha, SIGNAL(valueChanged(int)), this, SLOT(on_sliderColor_valueChanged(int)));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_dial_valueChanged(int value)
{
    ui->lcdNumber->display(value);
}

void Widget::on_sliderColor_valueChanged(int value)
{
    Q_UNUSED(value)

    int r = ui->sliderRed->value();
    int g = ui->sliderGreen->value();
    int b = ui->sliderBlue->value();
    int alpha = ui->sliderAlpha->value();
    QColor color;
    color.setRgb(r, g, b, alpha);

    QPalette pal = ui->textEdit->palette();
    pal.setColor(QPalette::Base, color); // background
    ui->textEdit->setPalette(pal);
}

void Widget::on_sliderH_valueChanged(int value)
{
    ui->scrollBarH->setValue(value);
    ui->proBarH->setValue(value);
}

void Widget::on_radioDec_clicked()
{
    ui->lcdNumber->setDigitCount(3);
    ui->lcdNumber->setDecMode();
}

void Widget::on_radioBin_clicked()
{
    ui->lcdNumber->setDigitCount(8);
    ui->lcdNumber->setBinMode();
}

void Widget::on_radioOct_clicked()
{
    ui->lcdNumber->setDigitCount(4);
    ui->lcdNumber->setOctMode();
}

void Widget::on_radioHex_clicked()
{
    ui->lcdNumber->setDigitCount(3);
    ui->lcdNumber->setHexMode();
}


void Widget::on_sliderV_valueChanged(int value)
{
    ui->progressBarV->setValue(value);
    ui->scrollBarV->setValue(value);
}

void Widget::on_scrollBarV_sliderMoved(int position)
{
    ui->progressBarV->setValue(position);
}

void Widget::on_scrollBarH_sliderMoved(int position)
{
    ui->proBarH->setValue(position);
}
