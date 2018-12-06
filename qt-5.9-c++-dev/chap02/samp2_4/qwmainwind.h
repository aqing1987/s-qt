#ifndef QWMAINWIND_H
#define QWMAINWIND_H

#include <QMainWindow>
#include <QLabel>
#include <QProgressBar>
#include <QSpinBox>
#include <QFontComboBox>

namespace Ui {
class QWMainWind;
}

class QWMainWind : public QMainWindow
{
    Q_OBJECT

public:
    explicit QWMainWind(QWidget *parent = 0);
    ~QWMainWind();

private slots:
    void on_actFontBold_triggered(bool checked);

    void on_actFontItalic_triggered(bool checked);

    void on_actFontUnderline_triggered(bool checked);

    void on_textEdit_copyAvailable(bool b);

    void on_textEdit_selectionChanged();

    void on_spinBoxFontSize_valueChanged(int aFontSize);
    void on_comboFont_currentIndexChanged(const QString &arg1);

    void on_actOpen_triggered();

    void on_actNew_triggered();

    void on_actToolbarShowText_triggered(bool checked);

    void on_actFontBold1_triggered(bool checked);

private:
    Ui::QWMainWind *ui;

    QString fCurFileName;
    QLabel *fLabCurFile; // put to status bar
    QProgressBar *progressBar; // put to status bar
    QSpinBox *spinFontSize;
    QFontComboBox *comboFont; // font name

    void initUi();
    void initSignalSlots();
    void updateCurFile(QString aFile);

};

#endif // QWMAINWIND_H
