#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QTimer>
#include <QTime>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private slots:
    void on_timer_timeout();
    void on_btnGetTime_clicked();


    void on_calendarWidget_selectionChanged();

    void on_btnSetTime_clicked();

    void on_btnSetDate_clicked();

    void on_btnSetDatetime_clicked();

    void on_btnSetPeriod_clicked();

    void on_btnStart_clicked();

    void on_btnStop_clicked();

private:
    Ui::Dialog *ui;

    QTimer *m_pTimer;
    QTime m_TimeCounter;
};

#endif // DIALOG_H
