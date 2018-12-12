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

void Widget::on_pushButton_clicked()
{
    QString str1, str2;
    str1 = ui->comboBox->currentText();
    str2 = ui->comboBox_2->currentText();
    str1.append(str2);

    ui->lineEditResult->setText(str1);
}

void Widget::on_pushButton_2_clicked()
{
    QString str1, str2;
    str1 = ui->comboBox->currentText();
    str2 = ui->comboBox_2->currentText();
    str1.prepend(str2);

    ui->lineEditResult->setText(str1);
}

void Widget::on_pushButton_16_clicked()
{
    QString str1, str2;
    str1 = ui->comboBox->currentText();
    str2 = ui->comboBox_2->currentText();

    bool chk;
    chk = str1.contains(str2);
    ui->checkBox->setChecked(chk);
    if (chk) {
        ui->checkBox->setText("contains()");
        ui->checkBox->sizeHint();
    } else {
        ui->checkBox->setText("No contains()");
    }
}

void Widget::on_pushButton_10_clicked()
{
    QString str1 = ui->comboBox->currentText();
    int i = str1.count();
    ui->spinBox->setValue(i);
    ui->labSpin->setText("count()");
}

void Widget::on_pushButton_11_clicked()
{
    QString str1 = ui->comboBox->currentText();
    int i = str1.size();
    ui->spinBox->setValue(i);
    ui->labSpin->setText("size()");
}

void Widget::on_pushButton_14_clicked()
{
    QString str1, str2;
    str1 = ui->comboBox->currentText();
    str2 = ui->comboBox_2->currentText();

    bool chk;
    chk = str1.endsWith(str2);
    ui->checkBox->setChecked(chk);
    if (chk) {
        ui->checkBox->setText("endsWith()");
        ui->checkBox->sizeHint();
    } else {
        ui->checkBox->setText("No endsWith()");
    }
}

void Widget::on_pushButton_12_clicked()
{
    QString str1, str2;
    str1 = ui->comboBox->currentText();
    str2 = ui->comboBox_2->currentText();

    int i;
    i = str1.indexOf(str2);
    ui->spinBox->setValue(i);
    ui->labSpin->setText("indexOf()");
}

void Widget::on_pushButton_18_clicked()
{
    QString str1;
    str1 = ui->comboBox->currentText();
    bool chk;
    chk = str1.isEmpty();
    ui->checkBox->setChecked(chk);
    if (chk) {
        ui->checkBox->setText("isEmpty()");
        ui->checkBox->sizeHint();
    } else {
        ui->checkBox->setText("No isEmpty()");
    }
}

void Widget::on_pushButton_13_clicked()
{
    QString str1, str2;
    str1 = ui->comboBox->currentText();
    str2 = ui->comboBox_2->currentText();

    int i;
    i = str1.lastIndexOf(str2);
    ui->spinBox->setValue(i);
    ui->labSpin->setText("lastIndexOf()");
}

void Widget::on_pushButton_15_clicked()
{
    QString str1, str2;
    str1 = ui->comboBox->currentText();
    str2 = ui->comboBox_2->currentText();

    bool chk;
    chk = str1.startsWith(str2);
    ui->checkBox->setChecked(chk);
    if (chk) {
        ui->checkBox->setText("startsWith()");
        ui->checkBox->sizeHint();
    } else {
        ui->checkBox->setText("No startsWith()");
    }
}

void Widget::on_pushButton_3_clicked()
{
    QString str1, str2;
    str1 = ui->comboBox->currentText();
    str2 = str1.toUpper();
    ui->lineEditResult->setText(str2);
}

void Widget::on_pushButton_4_clicked()
{
    QString str1, str2;
    str1 = ui->comboBox->currentText();
    str2 = str1.toLower();
    ui->lineEditResult->setText(str2);
}

void Widget::on_pushButton_17_clicked()
{
    QString str1;
    str1 = ui->comboBox->currentText();
    bool chk;

    chk = str1.isNull();
    ui->checkBox->setChecked(chk);
    if (chk) {
        ui->checkBox->setText("isNull()");
        ui->checkBox->sizeHint();
    } else {
        ui->checkBox->setText("No isNull()");
    }
}

void Widget::on_pushButton_8_clicked()
{
    QString str1;
    str1 = ui->comboBox->currentText();
    ui->lineEditResult->setText(str1.simplified());
}

void Widget::on_pushButton_9_clicked()
{
    QString str1;
    str1 = ui->comboBox->currentText();
    ui->lineEditResult->setText(str1.trimmed());
}

void Widget::on_pushButton_5_clicked()
{
    QString str1, str2;
    str1 = ui->comboBox->currentText();
    int v = ui->spinBox->value();
    str2 = str1.left(v);
    ui->lineEditResult->setText(str2);
}

void Widget::on_pushButton_6_clicked()
{
    QString str1,str2;
    str1=ui->comboBox->currentText();
    int cnt=str1.size();
    int v=ui->spinBox->value();
    str2=str1.right(cnt-v-1);
    ui->lineEditResult->setText(str2);
}

void Widget::on_pushButton_7_clicked()
{
    int i;
    QString str1, str2, str3;
    str1 = ui->comboBox->currentText();
    i = ui->spinBox->value();

    str3 = ui->comboBox_2->currentText();
    if (QString::compare(str3, "\\", Qt::CaseInsensitive) == 0)
        str2 = str1.section("\\", i, i+1);
    else
        str2 = str1.section(str3, i, i+1);

    ui->lineEditResult->setText(str2);
}
