#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_btnInitItems_clicked();

    void on_btnClearItems_clicked();

    void on_checkBoxEditable_clicked(bool checked);

    void on_comboBox_currentIndexChanged(const QString &arg1);

    void on_btnClearText_clicked();

    void on_checkBoxReadOnly_clicked(bool checked);

    void on_btnToComboBox_clicked();

    void on_plainTextEdit_customContextMenuRequested(const QPoint &pos);

    void on_btnInitCityItems_clicked();

    void on_comboBox_2_currentIndexChanged(const QString &arg1);

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
