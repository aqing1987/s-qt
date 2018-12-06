#include "qwmainwind.h"
#include "ui_qwmainwind.h"

#include <QFile>
#include <QFileDialog>
#include <QTextStream>

QWMainWind::QWMainWind(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QWMainWind)
{
    ui->setupUi(this);
    initUi();
    initSignalSlots();
}

QWMainWind::~QWMainWind()
{
    delete ui;
}

void QWMainWind::initUi()
{
    // add widgets to status bar
    fLabCurFile = new QLabel;
    fLabCurFile->setMinimumWidth(150);
    fLabCurFile->setText("current: ");
    ui->statusBar->addWidget(fLabCurFile);

    progressBar = new QProgressBar;
    progressBar->setMaximumWidth(200);
    progressBar->setMinimum(5);
    progressBar->setMaximum(50);
    progressBar->setValue(ui->textEdit->font().pointSize());
    ui->statusBar->addWidget(progressBar);

    // add widgets to tool bar
    spinFontSize = new QSpinBox;
    spinFontSize->setMinimum(5);
    spinFontSize->setMaximum(50);
    spinFontSize->setValue(ui->textEdit->font().pointSize());
    spinFontSize->setMinimumWidth(50);

    ui->mainToolBar->addWidget(new QLabel("font size "));
    ui->mainToolBar->addWidget(spinFontSize);

    ui->mainToolBar->addSeparator();
    ui->mainToolBar->addWidget(new QLabel(" font "));
    comboFont = new QFontComboBox;
    comboFont->setMinimumWidth(150);
    ui->mainToolBar->addWidget(comboFont);

    setCentralWidget(ui->textEdit);
}

void QWMainWind::initSignalSlots()
{
    connect(spinFontSize, SIGNAL(valueChanged(int)),
            this, SLOT(on_spinBoxFontSize_valueChanged(int)));
    connect(comboFont, SIGNAL(currentIndexChanged(const QString&)),
            this, SLOT(on_comboFont_currentIndexChanged(const QString&)));
}

void QWMainWind::updateCurFile(QString aFile)
{
    fCurFileName = aFile;
    fLabCurFile->setText("current: " + fCurFileName);
}

void QWMainWind::on_textEdit_copyAvailable(bool b)
{   
    ui->actCut->setEnabled(b);
    ui->actCopy->setEnabled(b);
    ui->actPaste->setEnabled(ui->textEdit->canPaste());
}

void QWMainWind::on_textEdit_selectionChanged()
{
    QTextCharFormat fmt;
    fmt = ui->textEdit->currentCharFormat();

    ui->actFontBold->setChecked(fmt.font().bold());
    ui->actFontItalic->setChecked(fmt.fontItalic());
    ui->actFontUnderline->setChecked(fmt.fontUnderline());
}

void QWMainWind::on_spinBoxFontSize_valueChanged(int aFontSize)
{
    QTextCharFormat fmt;
    fmt.setFontPointSize(aFontSize);
    ui->textEdit->mergeCurrentCharFormat(fmt);
    progressBar->setValue(aFontSize);
}

void QWMainWind::on_comboFont_currentIndexChanged(const QString &arg1)
{
    QTextCharFormat fmt;
    fmt.setFontFamily(arg1);
    ui->textEdit->mergeCurrentCharFormat(fmt);
}

void QWMainWind::on_actOpen_triggered()
{
    QString curPath, aFileName;
    curPath = QCoreApplication::applicationDirPath();

    aFileName = QFileDialog::getOpenFileName(this, tr("open file"), curPath,
                                             "(*.cpp);;(*.h);;(*.txt);;(*.*)");
    if (!aFileName.isEmpty()) {
        QFile aFile(aFileName);
        if (aFile.open(QIODevice::ReadWrite | QIODevice::Text)) {
            QTextStream aStream(&aFile);
            while (!aStream.atEnd()) {
                ui->textEdit->append(aStream.readLine());
            }

            updateCurFile(aFileName);
        }
        aFile.close();
    }
}

void QWMainWind::on_actNew_triggered()
{
    ui->textEdit->clear();
    updateCurFile("");
}

void QWMainWind::on_actFontItalic_triggered(bool checked)
{
    QTextCharFormat fmt;
    fmt = ui->textEdit->currentCharFormat();
    fmt.setFontItalic(checked);
    ui->textEdit->mergeCurrentCharFormat(fmt);
}

void QWMainWind::on_actFontBold_triggered(bool checked)
{
    QTextCharFormat fmt;
    fmt = ui->textEdit->currentCharFormat();
    if (checked) // equal to ui->actFontBold->isChecked()
        fmt.setFontWeight(QFont::Bold);
    else
        fmt.setFontWeight(QFont::Normal);

    ui->textEdit->mergeCurrentCharFormat(fmt);
}

void QWMainWind::on_actFontUnderline_triggered(bool checked)
{
    QTextCharFormat fmt;
    fmt = ui->textEdit->currentCharFormat();
    fmt.setFontUnderline(checked);
    ui->textEdit->mergeCurrentCharFormat(fmt);
}

void QWMainWind::on_actToolbarShowText_triggered(bool checked)
{
    if (checked)
        ui->mainToolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    else
        ui->mainToolBar->setToolButtonStyle(Qt::ToolButtonIconOnly);
}


void QWMainWind::on_actFontBold1_triggered(bool checked)
{
    QTextCharFormat fmt;
    fmt = ui->textEdit->currentCharFormat();
    if (checked) // equal to ui->actFontBold->isChecked()
        fmt.setFontWeight(QFont::Bold);
    else
        fmt.setFontWeight(QFont::Normal);

    ui->textEdit->mergeCurrentCharFormat(fmt);
}
