#include "qwdialog.h"
#include "ui_qwdialog.h"

QWDialog::QWDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QWDialog)
{
    ui->setupUi(this);

    connect(ui->radioButtonBlack, SIGNAL(clicked()), this, SLOT(setTextFontColor()));
    connect(ui->radioButtonBlue, SIGNAL(clicked()), this, SLOT(setTextFontColor()));
    connect(ui->radioButtonRed, SIGNAL(clicked()), this, SLOT(setTextFontColor()));
}

QWDialog::~QWDialog()
{
    delete ui;
}

void QWDialog::on_checkBoxUnderline_clicked(bool checked)
{
    QFont font = ui->plainTextEdit->font();
    font.setUnderline(checked);
    ui->plainTextEdit->setFont(font);
}

void QWDialog::on_checkBoxItalic_clicked(bool checked)
{
    QFont font = ui->plainTextEdit->font();
    font.setItalic(checked);
    ui->plainTextEdit->setFont(font);
}

void QWDialog::on_checkBoxBold_clicked(bool checked)
{
    QFont font = ui->plainTextEdit->font();
    font.setBold(checked);
    ui->plainTextEdit->setFont(font);
}

void QWDialog::setTextFontColor()
{
    QPalette plet = ui->plainTextEdit->palette();
    if (ui->radioButtonBlack->isChecked())
        plet.setColor(QPalette::Text, Qt::black);
    else if (ui->radioButtonBlue->isChecked())
        plet.setColor(QPalette::Text, Qt::blue);
    else if (ui->radioButtonRed->isChecked())
        plet.setColor(QPalette::Text, Qt::red);
    else
        plet.setColor(QPalette::Text, Qt::black);

    ui->plainTextEdit->setPalette(plet);
}
