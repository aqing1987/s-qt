#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QTreeWidgetItem>
#include <QPixmap>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actDockFloat_triggered(bool checked);

    void on_dockWidget_topLevelChanged(bool topLevel);

    void on_treeWidget_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);

    void on_actZoomFitH_triggered();

    void on_actZoomRealSize_triggered();

    void on_actZoomFitW_triggered();

    void on_actZoomIn_triggered();

    void on_actZoomOut_triggered();

    void on_actAddFolder_triggered();

    void on_actAddFiles_triggered();

    void on_dockWidget_visibilityChanged(bool visible);

    void on_actDockVisible_toggled(bool arg1);

    void on_actScanItems_triggered();

    void on_actDeleteItem_triggered();

private:
    Ui::MainWindow *ui;

    QLabel *labelFileName;
    QPixmap curPixmap;
    float pixRatio; // current picture zoom ratio

    enum treeItemType {
        itTopItem = 1001,
        itGroupItem,
        itImageItem
    };

    enum treeColNum {
        colItem = 0,
        colItemType = 1
    };

    void initTree();
    void displayImage(QTreeWidgetItem *item);
    void addFolderItem(QTreeWidgetItem *parItem, QString dirName);
    QString getFinalFolderName(const QString &fullPathName);
    void addImageItem(QTreeWidgetItem *parItem, QString filename);
    void changeItemCaption(QTreeWidgetItem *item);
};

#endif // MAINWINDOW_H
