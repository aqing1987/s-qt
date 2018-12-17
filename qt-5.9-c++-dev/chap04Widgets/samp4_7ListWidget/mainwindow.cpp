#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMenu>
#include <QIcon>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setCentralWidget(ui->splitter);
    setActionsForButton();
    createSelectionPopMenu();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setActionsForButton()
{
    ui->tBtnListInit->setDefaultAction(ui->actListInit);
    ui->tBtnListClear->setDefaultAction(ui->actListClear);
    ui->tBtnListInsert->setDefaultAction(ui->actListInsert);
    ui->tBtnListAppend->setDefaultAction(ui->actListAppend);
    ui->tBtnListDelete->setDefaultAction(ui->actListDelete);

    ui->tBtnSelAll->setDefaultAction(ui->actSelAll);
    ui->tBtnSelNone->setDefaultAction(ui->actSelNone);
    ui->tBtnSelInvs->setDefaultAction(ui->actSelInvs);
}

void MainWindow::createSelectionPopMenu()
{
    QMenu *menu = new QMenu(this);
    menu->addAction(ui->actSelAll);
    menu->addAction(ui->actSelNone);
    menu->addAction(ui->actSelInvs);

    ui->tBtnSelectItem->setPopupMode(QToolButton::MenuButtonPopup);
    ui->tBtnSelectItem->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    ui->tBtnSelectItem->setDefaultAction(ui->actSelPopMenu); // link action
    ui->tBtnSelectItem->setMenu(menu); // set pop menu

    // === add pop menu in toolbar
    QToolButton *tBtn = new QToolButton(this);
    tBtn->setPopupMode(QToolButton::InstantPopup);
    tBtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    tBtn->setDefaultAction(ui->actSelPopMenu);
    tBtn->setMenu(menu);
    ui->mainToolBar->addWidget(tBtn);

    ui->mainToolBar->addSeparator();
    ui->mainToolBar->addAction(ui->actQuit);
}

void MainWindow::on_actListClear_triggered()
{
    ui->listWidget->clear();
}

void MainWindow::on_actListInit_triggered()
{
    QListWidgetItem *item;

    QIcon icon;
    icon.addFile(":/images/icons/check2.ico");
    bool chk = ui->checkBoxListEditable->isChecked();

    ui->listWidget->clear();

    for (int i = 0; i < 10; ++i) {
        QString str = QString::asprintf("Item %d", i);
        item = new QListWidgetItem();
        item->setText(str);
        item->setIcon(icon);
        item->setCheckState(Qt::Checked);
        if (chk)
            item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
        else
            item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);

        ui->listWidget->addItem(item);
    }
}

void MainWindow::on_checkBoxListEditable_clicked(bool checked)
{
    QListWidgetItem *item;

    int cnt = ui->listWidget->count();
    for (int i = 0; i < cnt; ++i) {
        item = ui->listWidget->item(i);
        if (checked)
            item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEditable |Qt::ItemIsUserCheckable |Qt::ItemIsEnabled);
        else
            item->setFlags(Qt::ItemIsSelectable |Qt::ItemIsUserCheckable |Qt::ItemIsEnabled);
    }
}

void MainWindow::on_actSelInvs_triggered()
{
    QListWidgetItem *item;

    int cnt = ui->listWidget->count();
    for (int i = 0; i < cnt; ++i) {
        item = ui->listWidget->item(i);
        if (item->checkState() != Qt::Checked)
            item->setCheckState(Qt::Checked);
        else
            item->setCheckState(Qt::Unchecked);
    }
}

void MainWindow::on_actSelAll_triggered()
{
    QListWidgetItem *item;

    int cnt = ui->listWidget->count();
    for (int i = 0; i < cnt; ++i) {
        item = ui->listWidget->item(i);
        if (item->checkState() != Qt::Checked)
            item->setCheckState(Qt::Checked);
    }
}

void MainWindow::on_actSelNone_triggered()
{
    QListWidgetItem *item;

    int cnt = ui->listWidget->count();
    for (int i = 0; i < cnt; ++i) {
        item = ui->listWidget->item(i);
        if (item->checkState() != Qt::Unchecked)
            item->setCheckState(Qt::Unchecked);
    }
}

void MainWindow::on_actListInsert_triggered()
{
    QIcon icon(":/images/icons/check2.ico");

    QListWidgetItem *item = new QListWidgetItem("New Inserted Item");
    item->setIcon(icon);
    item->setCheckState(Qt::Checked);

    bool chk = ui->checkBoxListEditable->isChecked();
    if (chk)
        item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
    else
        item->setFlags(Qt::ItemIsSelectable |Qt::ItemIsUserCheckable |Qt::ItemIsEnabled);

    ui->listWidget->insertItem(ui->listWidget->currentRow(), item); // above current item
}

void MainWindow::on_actListAppend_triggered()
{
    QIcon icon(":/images/icons/check2.ico");

    QListWidgetItem *item = new QListWidgetItem("New Appended Item");
    item->setIcon(icon);
    item->setCheckState(Qt::Checked);

    bool chk = ui->checkBoxListEditable->isChecked();
    if (chk)
        item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
    else
        item->setFlags(Qt::ItemIsSelectable |Qt::ItemIsUserCheckable |Qt::ItemIsEnabled);

    ui->listWidget->addItem(item);
}

void MainWindow::on_actListDelete_triggered()
{
    // Removes and returns the item from the given row in the list widget; otherwise returns 0.
    // Items removed from a list widget will not be managed by Qt, and will need to be deleted manually.
    int row = ui->listWidget->currentRow();
    QListWidgetItem *item = ui->listWidget->takeItem(row);
    if (item)
        delete item;
}

void MainWindow::on_toolBox_currentChanged(int index)
{
    ui->tabWidget->setCurrentIndex(index); // tabWidget changed according to toolBox changed
}

void MainWindow::on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    if (current != NULL) {
        QString str;
        if (previous == NULL) {
            str = "Current: " + current->text();
        } else {
            str = "Previous: " + previous->text() + "; Current: " + current->text();
        }
        ui->editCurrentItemText->setText(str);
    }
}

void MainWindow::on_listWidget_customContextMenuRequested(const QPoint &pos)
{
    Q_UNUSED(pos);

    QMenu *list = new QMenu(this);
    list->addAction(ui->actListInit);
    list->addAction(ui->actListClear);
    list->addAction(ui->actListInsert);
    list->addAction(ui->actListAppend);
    list->addAction(ui->actListDelete);
    list->addSeparator();
    list->addAction(ui->actSelAll);
    list->addAction(ui->actSelNone);
    list->addAction(ui->actSelInvs);

    list->exec(QCursor::pos());
    delete list;
}

void MainWindow::on_tabWidget_currentChanged(int index)
{
    ui->toolBox->setCurrentIndex(index);
}

void MainWindow::on_spinBox_valueChanged(const QString &arg1)
{
    ui->lineEdit->setText(arg1);
}
