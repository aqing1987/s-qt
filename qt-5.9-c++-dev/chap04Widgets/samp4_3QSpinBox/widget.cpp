#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_btnCal_clicked()
{
    int num = ui->spinNum->value();
    float price = ui->doubleSpinSingle->value();
    float total = num * price;
    ui->doubleSpinTotal->setValue(total);
}

void Widget::on_btnDec_clicked()
{
    int val = ui->spinDec->value();
    ui->spinBin->setValue(val);
    ui->spinHex->setValue(val);
}

void Widget::on_btnBin_clicked()
{
    int val = ui->spinBin->value();
    ui->spinDec->setValue(val);
    ui->spinHex->setValue(val);
}

void Widget::on_btnHex_clicked()
{
    int val = ui->spinHex->value();
    ui->spinDec->setValue(val);
    ui->spinHex->setValue(val);
}
