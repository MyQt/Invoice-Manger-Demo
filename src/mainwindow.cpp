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
    ui->userTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->userTabStatus->setText(tr("状态:获取员工数据..."));
    Model::SetUserModel();
    QString result;
    if (Database::SetUserModel(Model::userModel, result))
    {
        ui->userTableView->setModel(Model::userModel);
        ui->userTableView->horizontalHeader()->setDefaultAlignment(Qt::AlignHCenter);
        for (int i = 0; i < 9; i++) {
            ui->userTableView->setColumnWidth(i, 100);
        }
        ui->userTabStatus->setText(tr("状态:Ok!"));
    } else {
        ui->userTabStatus->setText(tr("状态:") + result);
    }
}

void MainWindow::on_userTableView_clicked(const QModelIndex &index)
{
    QString text;
    QStringList detailList;
    detailList << "编号" << "姓名" << "性别" << "电话" << "邮箱" << "入职日期" << "地址" << "职位" << "备注";
    for (int i = 0; i < 9; i++) {
        text += detailList[i] + ": " + ui->userTableView->model()->index(index.row(), i).data().toString() + "\n";
    }
    ui->userDetailEdit->setText(text);
}

void MainWindow::on_newUserButton_clicked()
{
    NewUserDialog ndlg;
    if (ndlg.exec() == QDialog::Accepted)
    {
        //
    }
}
