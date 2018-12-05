#ifndef QWDLGMANUAL_H
#define QWDLGMANUAL_H

#include <QDialog>
#include <QCheckBox>
#include <QRadioButton>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QPalette>

class QWDlgManual : public QDialog
{
    Q_OBJECT

private:
    QCheckBox *chkBoxUnder;
    QCheckBox *chkBoxItalic;
    QCheckBox *chkBoxBold;
    QRadioButton *rBtnBlack;
    QRadioButton *rBtnBlue;
    QRadioButton *rBtnRed;
    QPlainTextEdit *txtEdit;
    QPushButton *btnOk;
    QPushButton *btnCancel;
    QPushButton *btnClose;

    void initUi();
    void initSignalSlots();

private slots:
    void on_chkBoxUnder(bool checked);
    void on_chkBoxItalic(bool checked);
    void on_chkBoxBold(bool checked);
    void setTextFontColor();

public:
    QWDlgManual(QWidget *parent = 0);
    ~QWDlgManual();
};

#endif // QWDLGMANUAL_H
