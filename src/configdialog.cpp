#include "configdialog.h"
#include "ui_configdialog.h"

ConfigDialog::ConfigDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigDialog)
{
    ui->setupUi(this);
}

ConfigDialog::~ConfigDialog()
{
    delete ui;
}

void ConfigDialog::on_saveButton_clicked()
{
    Setting set;
    QString host = ui->hostEdit->text();
    int port = ui->portEdit->text().toInt();
    QString databaseName = ui->nameEdit->text();
    QString databaseUser = ui->userEdit->text();
    QString databasePwd = ui->pwdEdit->text();
    //test
    QString user = "test";
    QString pwd = "123456";

    set.SetHost(host);
    set.SetPort(port);
    set.SetName(databaseName);
    set.SetDatabaseUser(databaseUser);
    set.SetDatabasePassword(databasePwd);
    set.SetUser(user);
    set.SetPassword(pwd);

    try
    {
        if (set.SaveConfigToXml()) {
            QMessageBox::information(this, "OK!", "config saved!", QMessageBox::Ok);
            accept();
        }
    }
    catch (QString ex)
    {
        QMessageBox::warning(this, "Error!", ex, QMessageBox::Cancel);
        close();
    }
}
