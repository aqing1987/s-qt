#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    labelFileName = new QLabel("");
    ui->statusBar->addWidget(labelFileName);

    this->setCentralWidget(ui->scrollArea);
    initTree();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actDockFloat_triggered(bool checked)
{
    ui->dockWidget->setFloating(checked);
}

void MainWindow::on_dockWidget_topLevelChanged(bool topLevel)
{
    ui->actDockFloat->setChecked(topLevel);
}

void MainWindow::initTree()
{
    QString dataStr = "";

    ui->treeWidget->clear();
    QIcon icon(":/images/icons/15.ico");

    QTreeWidgetItem *item = new QTreeWidgetItem(MainWindow::itTopItem);
    item->setIcon(MainWindow::colItem, icon); // first column icon
    item->setText(MainWindow::colItem, "pic file"); // first column text
    item->setText(MainWindow::colItemType, "type=itTopItem"); // second column text
    item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsAutoTristate);
    item->setCheckState(colItem, Qt::Checked); // set as checked

    item->setData(MainWindow::colItem, Qt::UserRole, QVariant(dataStr)); // set node first column Qt::UserRole data
    ui->treeWidget->addTopLevelItem(item);
}

void MainWindow::displayImage(QTreeWidgetItem *item)
{
    // get file name
    QString fname = item->data(colItem, Qt::UserRole).toString();
    labelFileName->setText(fname);
    curPixmap.load(fname);
    on_actZoomFitH_triggered();

    ui->actZoomFitH->setEnabled(true);
    ui->actZoomFitW->setEnabled(true);
    ui->actZoomIn->setEnabled(true);
    ui->actZoomOut->setEnabled(true);
    ui->actZoomRealSize->setEnabled(true);
}

void MainWindow::addFolderItem(QTreeWidgetItem *parItem, QString dirName)
{
    QIcon icon(":/images/icons/open3.bmp");
    QString NodeText = getFinalFolderName(dirName); // get folder name from the full name

    QTreeWidgetItem *item;
    item = new QTreeWidgetItem(MainWindow::itGroupItem);
    item->setIcon(colItem, icon);
    item->setText(colItem, NodeText); // first column
    item->setText(colItemType, "type=itGroupItem"); // second column
    item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsAutoTristate);
    item->setCheckState(colItem, Qt::Checked);
    item->setData(colItem, Qt::UserRole, QVariant(dirName)); // save full path

    parItem->addChild(item);
}

QString MainWindow::getFinalFolderName(const QString &fullPathName)
{
    int cnt = fullPathName.length();
    int i = fullPathName.lastIndexOf("/");
    QString str = fullPathName.right(cnt - i - 1); // get last folder name
    return str;
}

void MainWindow::addImageItem(QTreeWidgetItem *parItem, QString filename)
{
    QIcon icon(":/images/icons/31.ico");
    QString NodeText = getFinalFolderName(filename);

    QTreeWidgetItem *item;
    item = new QTreeWidgetItem(MainWindow::itImageItem);
    item->setIcon(colItem, icon);
    item->setText(colItem, NodeText);
    item->setText(colItemType, "type=itImageItem");
    item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsAutoTristate);
    item->setCheckState(colItem, Qt::Checked);

    item->setData(colItem, Qt::UserRole, QVariant(filename));
    parItem->addChild(item);
}

void MainWindow::changeItemCaption(QTreeWidgetItem *item)
{
    QString str = "*" + item->text(colItem);
    item->setText(colItem, str);

    if (item->childCount() > 0)
        for (int i = 0; i < item->childCount(); ++i)
            changeItemCaption(item->child(i));
}

void MainWindow::on_treeWidget_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
    Q_UNUSED(previous);
    if (current == NULL)
        return;

    int var = current->type();
    switch (var) {
    case itTopItem: // top node
        ui->actAddFolder->setEnabled(true);
        ui->actAddFiles->setEnabled(true);
        ui->actDeleteItem->setEnabled(false);
        break;

    case itGroupItem: // folder node
        ui->actAddFolder->setEnabled(true);
        ui->actAddFiles->setEnabled(true);
        ui->actDeleteItem->setEnabled(true);
        break;

    case itImageItem: // image file node
        ui->actAddFolder->setEnabled(false);
        ui->actAddFiles->setEnabled(true);
        ui->actDeleteItem->setEnabled(true);
        displayImage(current);
        break;

    default:
        break;
    }
}

void MainWindow::on_actZoomFitH_triggered()
{
    int h = ui->scrollArea->height();
    int realH = curPixmap.height();
    pixRatio = float(h) / realH;

    QPixmap pix = curPixmap.scaledToHeight(h - 30);
    ui->labelPic->setPixmap(pix);
}

void MainWindow::on_actZoomRealSize_triggered()
{
    pixRatio = 1;
    ui->labelPic->setPixmap(curPixmap);
}

void MainWindow::on_actZoomFitW_triggered()
{
    int w = ui->scrollArea->width() - 20;
    int realw = curPixmap.width();
    pixRatio = float(w) / realw;

    QPixmap pix = curPixmap.scaledToWidth(w - 30);
    ui->labelPic->setPixmap(pix);
}

void MainWindow::on_actZoomIn_triggered()
{
    pixRatio = pixRatio*1.2;

    int w = pixRatio * curPixmap.width();
    int h = pixRatio * curPixmap.height();

    QPixmap pix = curPixmap.scaled(w, h);
    ui->labelPic->setPixmap(pix);
}

void MainWindow::on_actZoomOut_triggered()
{
    pixRatio = pixRatio*0.8;

    int w = pixRatio * curPixmap.width();
    int h = pixRatio * curPixmap.height();

    QPixmap pix = curPixmap.scaled(w, h);
    ui->labelPic->setPixmap(pix);
}

void MainWindow::on_actAddFolder_triggered()
{
    QString dir = QFileDialog::getExistingDirectory(); // chose directory
    if (!dir.isEmpty()) {
        QTreeWidgetItem *item = ui->treeWidget->currentItem(); // get current node
        if (item)
            addFolderItem(item, dir); // add group node under current node
    }
}

void MainWindow::on_actAddFiles_triggered()
{
    QStringList files = QFileDialog::getOpenFileNames(this, "select one or more files", "", "Images(*.jpg)");
    if (files.isEmpty())
        return;

    QTreeWidgetItem *parItem, *item;
    item = ui->treeWidget->currentItem();
    if (item->type() == itImageItem)
        parItem = item->parent();
    else
        parItem = item;

    for (int i = 0; i < files.size(); ++i) {
        QString aName = files.at(i); // get file name from StringList
        addImageItem(parItem, aName);
    }

}

void MainWindow::on_dockWidget_visibilityChanged(bool visible)
{
    ui->actDockVisible->setChecked(visible);
}

void MainWindow::on_actDockVisible_toggled(bool arg1)
{
    ui->dockWidget->setVisible(arg1);
}

void MainWindow::on_actScanItems_triggered()
{
    for (int i = 0; i < ui->treeWidget->topLevelItemCount(); ++i) {
        QTreeWidgetItem *item = ui->treeWidget->topLevelItem(i);
        changeItemCaption(item);
    }
}

void MainWindow::on_actDeleteItem_triggered()
{
    QTreeWidgetItem *item = ui->treeWidget->currentItem();
    QTreeWidgetItem *parItem = item->parent();
    parItem->removeChild(item); // the removed item will not be deleted

    delete item; // manually delete
}
