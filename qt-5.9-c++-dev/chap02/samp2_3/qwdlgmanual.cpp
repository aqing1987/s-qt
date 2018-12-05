#include "qwdlgmanual.h"

void QWDlgManual::initUi()
{
    // create Underline, Italic, Bold CheckBox, and horizontal them
    chkBoxBold = new QCheckBox(tr("Bold"));
    chkBoxItalic = new QCheckBox(tr("Italic"));
    chkBoxUnder = new QCheckBox(tr("Underline"));
    QHBoxLayout *HLay1 = new QHBoxLayout;
    HLay1->addWidget(chkBoxBold);
    HLay1->addWidget(chkBoxItalic);
    HLay1->addWidget(chkBoxUnder);

    // create Black, Red, Blue RadioButton, and horizontal them
    rBtnBlack = new QRadioButton(tr("Black"));
    rBtnBlue = new QRadioButton(tr("Blue"));
    rBtnRed = new QRadioButton(tr("Red"));
    rBtnBlack->setChecked(true);
    QHBoxLayout *HLay2 = new QHBoxLayout;
    HLay2->addWidget(rBtnBlack);
    HLay2->addWidget(rBtnBlue);
    HLay2->addWidget(rBtnRed);

    // create ok, cancel, close PushButton, and horizontal them
    btnOk = new QPushButton(tr("Ok"));
    btnCancel = new QPushButton(tr("Cancel"));
    btnClose = new QPushButton(tr("Close"));
    QHBoxLayout *HLay3 = new QHBoxLayout;
    HLay3->addStretch();
    HLay3->addWidget(btnOk);
    HLay3->addWidget(btnCancel);
    HLay3->addStretch();
    HLay3->addWidget(btnClose);

    // create editText
    txtEdit = new QPlainTextEdit;
    txtEdit->setPlainText("Hello world");
    QFont font = txtEdit->font(); // get font
    font.setPointSize(20); // change font size
    txtEdit->setFont(font);

    // create vertial layout, and set as main layout
    QVBoxLayout *VLay = new QVBoxLayout;
    VLay->addLayout(HLay1);
    VLay->addLayout(HLay2);
    VLay->addWidget(txtEdit);
    VLay->addLayout(HLay3);
    setLayout(VLay); // set as the widget main layout

}

void QWDlgManual::initSignalSlots()
{
    // RadioButton
    connect(rBtnBlack, SIGNAL(clicked()), this, SLOT(setTextFontColor()));
    connect(rBtnBlue, SIGNAL(clicked()), this, SLOT(setTextFontColor()));
    connect(rBtnRed, SIGNAL(clicked()), this, SLOT(setTextFontColor()));

    // CheckBox
    connect(chkBoxBold, SIGNAL(clicked(bool)), this, SLOT(on_chkBoxBold(bool)));
    connect(chkBoxItalic, SIGNAL(clicked(bool)), this, SLOT(on_chkBoxItalic(bool)));
    connect(chkBoxUnder, SIGNAL(clicked(bool)), this, SLOT(on_chkBoxUnder(bool)));

    // PushButton
    connect(btnOk, SIGNAL(clicked()), this, SLOT(accept()));
    connect(btnCancel, SIGNAL(clicked()), this, SLOT(reject()));
    connect(btnClose, SIGNAL(clicked()), this, SLOT(close()));
}

void QWDlgManual::on_chkBoxUnder(bool checked)
{
    QFont font = txtEdit->font();
    font.setUnderline(checked);
    txtEdit->setFont(font);
}

void QWDlgManual::on_chkBoxItalic(bool checked)
{
    QFont font = txtEdit->font();
    font.setItalic(checked);
    txtEdit->setFont(font);
}

void QWDlgManual::on_chkBoxBold(bool checked)
{
    QFont font = txtEdit->font();
    font.setBold(checked);
    txtEdit->setFont(font);
}

void QWDlgManual::setTextFontColor()
{
    QPalette plet = txtEdit->palette();
    if (rBtnBlack->isChecked())
        plet.setColor(QPalette::Text, Qt::black);
    else if (rBtnBlue->isChecked())
        plet.setColor(QPalette::Text, Qt::blue);
    else if (rBtnRed->isChecked())
        plet.setColor(QPalette::Text, Qt::red);
    else
        plet.setColor(QPalette::Text, Qt::black);

    txtEdit->setPalette(plet);
}

QWDlgManual::QWDlgManual(QWidget *parent)
    : QDialog(parent)
{
    initUi();
    initSignalSlots();
    setWindowTitle("Form created mannually");
}

QWDlgManual::~QWDlgManual()
{

}
