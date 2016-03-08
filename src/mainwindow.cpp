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

//userTabControl

void MainWindow::SetUserModel()
{
    if (User::level < User::ADMIN) {
        ui->removeUserButton->setDisabled(true);
    }

    LoadUserModel();
}

void MainWindow::LoadUserModel()
{
    ui->userTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->userTabStatus->setText(tr("状态:获取员工数据..."));
    Model::SetUserModel();
    QString result;
    if (db.SetUserModel(Model::userModel, result)) {
        ui->userTableView->setModel(Model::userModel);
        ui->userTableView->horizontalHeader()->setDefaultAlignment(Qt::AlignHCenter);
        ui->userTableView->verticalHeader()->hide();
        for (int i = 0; i < 9; i++) {
            ui->userTableView->setColumnWidth(i, 100);
        }
        ui->userTabStatus->setText(tr("状态:Ok!"));
    } else {
        ui->userTabStatus->setText(tr("状态:") + result);
    }
}

void MainWindow::ReloadUserModel()
{
    Model::userModel->clear();
    LoadUserModel();
}

void MainWindow::on_userTableView_clicked(const QModelIndex &index)
{
    SetTextDetail(index);
}

void MainWindow::SetTextDetail(const QModelIndex &index)
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
        QMessageBox::information(this, "Success!", "保存成功!", QMessageBox::Ok);
        ReloadUserModel();
    }
}


void MainWindow::on_reloadButton_clicked()
{
    ReloadUserModel();
}

void MainWindow::on_removeUserButton_clicked()
{
    int currentRow = ui->userTableView->currentIndex().row();
    int number = ui->userTableView->model()->index(currentRow, 0).data().toInt();
    if (number == User::number.toInt()) {
        QMessageBox::warning(this, "Error!", "不能删除自身!", QMessageBox::Ok);
    }
    if (QMessageBox::warning(this, "Warning!", "确认删除此用户?", QMessageBox::Yes, QMessageBox::Cancel)
            == QMessageBox::Yes) {
        QString queryString = QString("delete from user where number = %0").arg(number);
        QString result;
        if (!db.Query(queryString, result)) {
            QMessageBox::warning(this, "Error!", result, QMessageBox::Ok);
        } else {
            QMessageBox::information(this, "Success", "删除成功!", QMessageBox::Ok);
            ReloadUserModel();
        }
    }
}

void MainWindow::on_alterUserButton_clicked()
{
    NewUserDialog ndlg;
    int currentRow = ui->userTableView->currentIndex().row();
    int number = ui->userTableView->model()->index(currentRow, 0).data().toInt();
    if (number == User::number.toInt() || User::level >= User::ADMIN ) {
        AlterUser::isAltered = true;
        SetAlterUser();
        ndlg.GetAlterUser();
        if (ndlg.exec() == QDialog::Accepted)
        {
            QMessageBox::information(this, "Success!", "保存成功!", QMessageBox::Ok);
            ReloadUserModel();
        }
    } else {
        QMessageBox::warning(this, "Error!", "没有足够权限!", QMessageBox::Cancel);
    }
    AlterUser::isAltered = false;
}

void MainWindow::SetAlterUser()
{
    int currentRow = ui->userTableView->currentIndex().row();
    AlterUser::number = ui->userTableView->model()->index(currentRow, 0).data().toString();
    AlterUser::name = ui->userTableView->model()->index(currentRow, 1).data().toString();
    AlterUser::gender = ui->userTableView->model()->index(currentRow, 2).data().toString();
    AlterUser::phone = ui->userTableView->model()->index(currentRow, 3).data().toString();
    AlterUser::email = ui->userTableView->model()->index(currentRow, 4).data().toString();
    AlterUser::employedDate = ui->userTableView->model()->index(currentRow, 5).data().toString();
    AlterUser::address = ui->userTableView->model()->index(currentRow, 6).data().toString();
    AlterUser::level = QString::number(User::GetLevel(ui->userTableView->model()->index(currentRow, 7).data().toString()));
    AlterUser::ps = ui->userTableView->model()->index(currentRow, 8).data().toString();
}

void MainWindow::on_findUserButton_clicked()
{
    int number = QInputDialog::getInt(this, tr("Input"), tr("请输入员工编号"), User::number.toInt());
    for (int row = 0; row < ui->userTableView->model()->rowCount(); row++) {
        if (number == ui->userTableView->model()->index(row, 0).data().toInt()) {
            ui->userTableView->setCurrentIndex(ui->userTableView->model()->index(row, 0));
            SetTextDetail(ui->userTableView->currentIndex());
        }
    }
}

//productionTabControl
void MainWindow::SetProductionModel()
{
    LoadProductionModel();
}

void MainWindow::LoadProductionModel()
{
    ui->productionTabStatus->setText(tr("状态:获取商品数据"));
    ui->productionTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    Model::SetProductionModel();
    QString result;
    if (db.SetProductionModel(Model::productionModel, result)) {
        ui->productionTableView->setModel(Model::productionModel);
        ui->productionTableView->horizontalHeader()->setDefaultAlignment(Qt::AlignHCenter);
        ui->productionTableView->verticalHeader()->hide();
        for (int i = 0; i < 4; i++) {
            ui->productionTableView->setColumnWidth(i, 125);
        }
        ui->productionTabStatus->setText(tr("状态:Ok!"));
    } else {
        ui->productionTabStatus->setText(tr("状态:") + result);
    }
}

void MainWindow::ReloadProductionModel()
{
    Model::productionModel->clear();
    LoadProductionModel();
}

void MainWindow::on_productionTableView_clicked(const QModelIndex &index)
{
    SetProductionDetail(index);
}

void MainWindow::SetProductionDetail(const QModelIndex &index)
{
    QString text;
    QStringList detailList;
    detailList << "编号" << "名称" << "生产商" << "单件成本" << "库存";
    for (int i = 0; i < 5; i++) {
        text += detailList[i] + ": " + ui->productionTableView->model()->index(index.row(), i).data().toString() + "\n";
    }
    QString inputDetail = tr("进货记录: \n");
    QString outputDetail = tr("出库记录: \n");


    text += inputDetail + outputDetail;
    ui->produtionDetailEdit->setText(text);
}

