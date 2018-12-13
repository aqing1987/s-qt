#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    m_pTimer = new QTimer(this);
    m_pTimer->stop();
    m_pTimer->setInterval(1000); //ms

    connect(m_pTimer, SIGNAL(timeout()), this, SLOT(on_timer_timeout()));
}

Dialog::~Dialog()
{
    m_pTimer->stop();
    delete m_pTimer;

    delete ui;
}

void Dialog::on_timer_timeout()
{
    QTime curTime = QTime::currentTime();
    ui->lcdHour->display(curTime.hour());
    ui->lcdMin->display(curTime.minute());
    ui->lcdSec->display(curTime.second());

    int val = ui->progressBar->value();
    ++val;
    if (val > 100)
        val = 0;
    ui->progressBar->setValue(val);
}

void Dialog::on_btnGetTime_clicked()
{
    QDateTime curDatetime = QDateTime::currentDateTime();

    ui->timeEdit->setTime(curDatetime.time());
    ui->dateEdit->setDate(curDatetime.date());
    ui->dateTimeEdit->setDateTime(curDatetime);

    ui->editTime->setText(curDatetime.toString("hh:mm:ss"));
    ui->editDate->setText(curDatetime.toString("yyyy-MM-dd"));
    ui->editDatetime->setText(curDatetime.toString("yyyy-MM-dd hh:mm:ss"));
}

void Dialog::on_calendarWidget_selectionChanged()
{
    QDate dt = ui->calendarWidget->selectedDate();
    QString str = dt.toString("yyyy年M月d日");
    ui->editCalendar->setText(str);
}

void Dialog::on_btnSetTime_clicked()
{
    QString str = ui->editTime->text();

    if (!str.isEmpty()) {
        QTime tm = QTime::fromString(str, "hh:mm:ss");
        ui->timeEdit->setTime(tm);
    }
}

void Dialog::on_btnSetDate_clicked()
{
    QString str = ui->editDate->text();
    str = str.trimmed();
    if (!str.isEmpty()) {
        QDate dt = QDate::fromString(str, "yyyy-MM-dd");
        ui->dateEdit->setDate(dt);
    }
}

void Dialog::on_btnSetDatetime_clicked()
{
    QString str = ui->editDatetime->text();
    str = str.trimmed();
    if (!str.isEmpty()) {
        QDateTime datetime = QDateTime::fromString(str, "yyyy-MM-dd hh:mm:ss");
        ui->dateTimeEdit->setDateTime(datetime);
    }
}

void Dialog::on_btnSetPeriod_clicked()
{
    m_pTimer->setInterval(ui->spinInterval->value());
}

void Dialog::on_btnStart_clicked()
{
    m_pTimer->start();
    m_TimeCounter.start();

    ui->btnStart->setEnabled(false);
    ui->btnStop->setEnabled(true);
    ui->btnSetPeriod->setEnabled(false);
}

void Dialog::on_btnStop_clicked()
{
    m_pTimer->stop();

    int tmMsec = m_TimeCounter.elapsed();
    int ms = tmMsec % 1000;
    int sec = tmMsec / 1000;

    QString str = QString::asprintf("elapsed time: %d s, %d ms", sec, ms);
    ui->labelElapsedTime->setText(str);

    ui->btnStart->setEnabled(true);
    ui->btnStop->setEnabled(false);
    ui->btnSetPeriod->setEnabled(true);
}
