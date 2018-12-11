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
    if (ui->lineEditNum->text().isEmpty() || ui->lineEditPrice->text().isEmpty())
        return;

    int num = ui->lineEditNum->text().toInt();
    float price = ui->lineEditPrice->text().toFloat();

    float total = num * price;
    QString str;
    str = str.sprintf("%.2f", total);
    ui->lineEditTotal->setText(str);
}


// read int and convert to hex, bin
void Widget::on_btnDec_clicked()
{
    int val = ui->lineEditDec->text().toInt(); // get int

    QString str = QString::number(val, 16); // int to Hex Str
    str = str.toUpper();
    ui->lineEditHex->setText(str);

    str = QString::number(val, 2); // int to bin str
    ui->lineEditBin->setText(str);
}

// read bin and convert to int, hex
void Widget::on_btnbin_clicked()
{
    bool ok;

    int val = ui->lineEditBin->text().toInt(&ok, 2);

    QString str = QString::number(val, 10); // to int str
    ui->lineEditDec->setText(str);

    str = QString::number(val, 16);
    ui->lineEditHex->setText(str.toUpper());
}

void Widget::on_btnHex_clicked()
{
    bool ok;

    int val = ui->lineEditHex->text().toInt(&ok, 16);

    QString str = QString::number(val, 10); // to int str
    ui->lineEditDec->setText(str);

    str = QString::number(val, 2);
    ui->lineEditBin->setText(str);
}
