#include "logindialog.h"
#include "ui_logindialog.h"

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    ui->statusLabel->setText(tr("正在连接数据库..."));
    ui->userEdit->setDisabled(true);
    ui->pwdEdit->setDisabled(true);
    ui->loginButton->setDisabled(true);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_loginButton_clicked()
{
    QString number = ui->userEdit->text();
    QString pwd = Setting::ToMD5(ui->pwdEdit->text());
    QString result;
    if (db.Login(number, pwd, result)) {
        //db.DisConnect();
        QMessageBox::information(this, "Success!", result, QMessageBox::Ok);
        accept();
    } else {
        QMessageBox::warning(this, "Error!", result, QMessageBox::Ok);
    }
}

void LoginDialog::ConnectDatabase()
{
    try {
        if (db.Connect()) {
            ui->userEdit->setEnabled(true);
            ui->pwdEdit->setEnabled(true);
            ui->loginButton->setEnabled(true);
            ui->statusLabel->setText(tr("已连接数据库..."));
        }
    }
    catch (QString e) {
        qDebug() << e;
    }
}

