#include "widget.h"
#include "ui_widget.h"

#include <QTextDocument>
#include <QTextBlock>
#include <QMenu>
#include <QMap>

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

void Widget::on_btnInitItems_clicked()
{
    QIcon icon;
    icon.addFile(":/images/icons/aim.ico");

    ui->comboBox->clear();
    for (int i = 0; i < 20; ++i)
        ui->comboBox->addItem(icon, QString::asprintf("Item %d", i));

    // QStringList strList;
    // strList<<"北京"<<"上海"<<"天津"<<"河北省"<<"山东省"<<"山西省";
    // ui->comboBox->addItems(strList);
}

void Widget::on_btnClearItems_clicked()
{
    ui->comboBox->clear();
}

void Widget::on_checkBoxEditable_clicked(bool checked)
{
    ui->comboBox->setEditable(checked);
}

void Widget::on_comboBox_currentIndexChanged(const QString &arg1)
{
    ui->plainTextEdit->appendPlainText(arg1);
}

void Widget::on_btnClearText_clicked()
{
    ui->plainTextEdit->clear();
}

void Widget::on_checkBoxReadOnly_clicked(bool checked)
{
    ui->plainTextEdit->setReadOnly(checked);
}

void Widget::on_btnToComboBox_clicked()
{
    QTextDocument *doc = ui->plainTextEdit->document();
    int cnt = doc->blockCount();

    QIcon icon(":/images/icons/aim.ico");
    ui->comboBox->clear();
    for (int i = 0; i < cnt; ++i) {
        QTextBlock textline = doc->findBlockByNumber(i);
        QString str = textline.text();
        ui->comboBox->addItem(icon, str);
    }
}

void Widget::on_plainTextEdit_customContextMenuRequested(const QPoint &pos)
{
    QMenu *menu = ui->plainTextEdit->createStandardContextMenu();
    menu->exec(pos);
}

void Widget::on_btnInitCityItems_clicked()
{
    QMap<QString, int> city_zone;
    city_zone.insert("北京", 10);
    city_zone.insert("上海", 21);
    city_zone.insert("天津", 22);
    city_zone.insert("大连", 411);
    city_zone.insert("锦州", 416);
    city_zone.insert("徐州", 516);
    city_zone.insert("福州", 591);
    city_zone.insert("青岛", 532);

    ui->comboBox_2->clear();

    foreach(const QString &str, city_zone.keys())
        ui->comboBox_2->addItem(str, city_zone.value(str));
}

void Widget::on_comboBox_2_currentIndexChanged(const QString &arg1)
{
    QString zone = ui->comboBox_2->currentData().toString();
    ui->plainTextEdit->appendPlainText(arg1 + " zone: " + zone);
}
