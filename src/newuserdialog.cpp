#include "newuserdialog.h"
#include "ui_newuserdialog.h"

NewUserDialog::NewUserDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewUserDialog)
{
    ui->setupUi(this);
    SetDefault();
}

NewUserDialog::~NewUserDialog()
{
    delete ui;
}

void NewUserDialog::GetAlterUser()
{
    if (AlterUser::isAltered) {
        ui->label->setText(tr("修改用户信息(带*号必填）"));
        ui->nameEdit->setText(AlterUser::name);
        ui->pwdEdit->setText(AlterUser::password);
        if (AlterUser::gender.toInt() == 0) {
            ui->manRadio->isChecked();
        } else {
            ui->womanRadio->isChecked();
        }
        ui->phoneEdit->setText(AlterUser::phone);
        ui->mailEdit->setText(AlterUser::email);
        ui->dateEdit->setDate(QDate::fromString(AlterUser::employedDate));
        ui->addressEdit->setText(AlterUser::address);
        ui->levelBox->setCurrentIndex(AlterUser::level.toInt() - 1);
        ui->noteEdit->setText(AlterUser::ps);
    }
}

void NewUserDialog::SetDefault()
{
    QDate now = QDate::currentDate();
    qDebug() << now.toString("yyyy-MM-dd");
    ui->dateEdit->setDate(now);
    ui->manRadio->setChecked(true);
    ui->levelBox->addItem("销售");
    if (User::level > User::SALESMAN) {
        ui->levelBox->addItem("经理");
    }
    if (User::level > User::MANAGER) {
        ui->levelBox->addItem("管理员");
    }
}

void NewUserDialog::on_saveButton_clicked()
{
    if (AlterUser::isAltered) {
        AlterUserInfo();
    } else {
        SaveUserInfo();
    }
}

void NewUserDialog::SaveUserInfo()
{
    //INSERT INTO `invoice`.`user` (`password`, `name`, `gender`, `phone`, `email`, `employed`, `address`, `level`, `ps`) VALUES ('e10adc3949ba59abbe56e057f20f883e', 'test3', '0', '12345678888', '10003@xxxxx.com', '2013-01-25', 'Mars', '1', 'test3')"
    QString name = ui->nameEdit->text().toUtf8();
    QString password = ui->pwdEdit->text();
    if (name.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "warning!", "姓名/密码不能为空!", QMessageBox::Ok);
        return;
    }
    if (password.length() < 6) {
        QMessageBox::warning(this, "warning", "密码长度过短!", QMessageBox::Ok);
    }
    password = Setting::ToMD5(password);
    QString gender = ui->manRadio->isChecked() ? "0" : "1";
    QString phone = ui->phoneEdit->text();
    QString email = ui->mailEdit->text();
    QString employedDate = ui->dateEdit->date().toString("yyyy-MM-dd");
    QString address = ui->addressEdit->text();
    QString level = QString::number(ui->levelBox->currentIndex() + 1);
    QString ps = ui->noteEdit->text();
    QString queryString = QString("insert into user (`password`, `name`, `gender`, `phone`, `email`, `employed`, `address`, `level`, `ps`) values ('%0', '%1', '%2', '%3', '%4', '%5', '%6', '%7', '%8')")
            .arg(password).arg(name).arg(gender).arg(phone).arg(email).arg(employedDate).arg(address).arg(level).arg(ps);
    qDebug() << queryString;

    QString result;
    if (Database::Query(queryString, result)) {
        accept();
    } else {
        QMessageBox::warning(this, "Error!", result, QMessageBox::Ok);
    }

}

void NewUserDialog::AlterUserInfo()
{
    QString name = ui->nameEdit->text().toUtf8();
    QString password = ui->pwdEdit->text();
    if (name.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "warning!", "姓名/密码不能为空!", QMessageBox::Ok);
        return;
    }
    if (password.length() < 6) {
        QMessageBox::warning(this, "warning", "密码长度过短!", QMessageBox::Ok);
    }
    password = Setting::ToMD5(password);
    QString gender = ui->manRadio->isChecked() ? "0" : "1";
    QString phone = ui->phoneEdit->text();
    QString email = ui->mailEdit->text();
    QString employedDate = ui->dateEdit->date().toString("yyyy-MM-dd");
    QString address = ui->addressEdit->text();
    QString level = QString::number(ui->levelBox->currentIndex() + 1);
    QString ps = ui->noteEdit->text();
    QString queryString = QString("update user set password = '%0', name = '%1', gender = '%2', phone = '%3', email = '%4', employed = '%5', address = '%6', level = '%7', ps = '%8' where number = %9")
            .arg(password).arg(name).arg(gender).arg(phone).arg(email).arg(employedDate).arg(address).arg(level).arg(ps).arg(AlterUser::number);
    qDebug() << queryString;
    QString result;
    if (Database::Query(queryString, result)) {
        accept();
    } else {
        QMessageBox::warning(this, "Error!", result, QMessageBox::Ok);
    }
}
