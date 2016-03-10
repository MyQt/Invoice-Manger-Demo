#include "newproductiondialog.h"
#include "ui_newproductiondialog.h"

NewProductionDialog::NewProductionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewProductionDialog)
{
    ui->setupUi(this);
    SetDefault();
}

NewProductionDialog::~NewProductionDialog()
{
    delete ui;
}

void NewProductionDialog::SetDefault()
{
    QDate now = QDate::currentDate();
    ui->dateEdit->setDate(now);
}

void NewProductionDialog::on_saveButton_clicked()
{
    if (SaveProductionInfo())
    {
        accept();
    }
}

bool NewProductionDialog::SaveProductionInfo()
{
    QString name = ui->nameEdit->text();
    QString quantity = ui->quantityBox->text();
    bool isOk;
    QString producer = QString::number(ui->producerEdit->text().toInt(&isOk));
    if (!isOk)
    {
        QMessageBox::warning(this, "Error!", "供应商编号必须为数字!", QMessageBox::Ok);
        return false;
    }
    QString date = ui->dateEdit->date().toString("yyyy-MM-dd");
    QString price = ui->priceBox->text();
    QString note = ui->nodeEdit->text();

    QString queryString = QString("select * from production where name = '%0'").arg(name);
    QString result;
    if (Database::Find(queryString, result))
    {
        queryString = QString("update production set inventory = inventory + %0 where name = '%1'").arg(quantity).arg(name);
        if (!Database::Query(queryString, result))
        {
            QMessageBox::warning(this, "Error!", result, QMessageBox::Ok);
            return false;
        }
        else
        {
            //QMessageBox::information(this, "Success!", "保存成功!", QMessageBox::Yes);
            //return true;
        }
    } else {
        queryString = QString("insert into production (`name`, `inventory`, `ps`) values ('%0', '%1', '%2')").arg(name).arg(quantity).arg(note);
        if (Database::Query(queryString, result))
        {
            //QMessageBox::information(this, "Success!", "保存成功!", QMessageBox::Yes);
            //return true;
        }
        else
        {
            QMessageBox::warning(this, "Error!", result, QMessageBox::Ok);
            return false;
        }
    }

    queryString = QString("select * from production where name = '%0'").arg(name);
    int number = Database::FindValue(queryString, 0).toInt();

    queryString = QString("insert into inputlog (`itemid`, `producerid`, `quantity`, `date`, `price`, `ps`) values ('%0', '%1', '%2', '%3', '%4', '%5')")
            .arg(number).arg(producer).arg(quantity).arg(date).arg(price).arg(note);
    if (Database::Query(queryString, result))

    {
        return true;
    }
    return false;
}

