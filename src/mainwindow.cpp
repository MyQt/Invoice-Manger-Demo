#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::SetUser()
{

}

void MainWindow::SetUserModel()
{
    Model::SetUserModel();
    QString result;
    Database::SetUserModel(Model::userModel, result);
    ui->userTableView->setModel(Model::userModel);
    ui->userTableView->horizontalHeader()->setDefaultAlignment(Qt::AlignHCenter);
    for (int i = 0; i < 9; i++) {
        ui->userTableView->setColumnWidth(i, 100);
    }
    ui->userTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
}
