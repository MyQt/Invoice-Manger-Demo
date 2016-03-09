#include "saledialog.h"
#include "ui_saledialog.h"

SaleDialog::SaleDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SaleDialog)
{
    ui->setupUi(this);
    SetDefault();
}

SaleDialog::~SaleDialog()
{
    delete ui;
}

void SaleDialog::SetDefault()
{
    ui->inventoryLabel->setText("");
    QDate now = QDate::currentDate();
    ui->dateEdit->setDate(now);

    for (int i = 0; i < Productions::nameList.length(); i++) {
        ui->nameBox->addItem(Productions::nameList[i]);
    }
    ui->nameBox->setCurrentText(Productions::currentName);
}

void SaleDialog::SetInvetory()
{
    QString name = ui->nameBox->currentText();
    QString queryString = QString("select * from production where name = '%0'").arg(name);
    int inventory = Database::FindValue(queryString, 2).toInt();
    ui->inventoryLabel->setText(tr("库存: ") + QString::number(inventory));
    ui->quantityBox->setMaximum(inventory);
}

void SaleDialog::on_saveButton_clicked()
{
    if (QMessageBox::information(this, "确认", "确认保存?", QMessageBox::Yes, QMessageBox::Cancel) == QMessageBox::Yes) {
        if (SaveInfo()) {
            accept();
        }
    }
}

bool SaleDialog::SaveInfo()
{
    QString name = ui->nameBox->currentText();
    QString quantity = ui->quantityBox->text();
    QString price = ui->priceBox->text();
    QString customerId = ui->customerEdit->text();
    QString date = ui->dateEdit->date().toString("yyyy-MM-dd");
    QString note = ui->nodeEdit->text();

    QString queryString = QString("select * from production where name = '%0'").arg(name);
    int ventory = Database::FindValue(queryString, 2).toInt();
    if (quantity.toInt() > ventory) {
        QMessageBox::warning(this, "Error!", "库存不足!", QMessageBox::Cancel);
        SetInvetory();
        return false;
    }
    QString number = Database::FindValue(queryString, 0);
    qDebug() << number;
    queryString = QString("update production set inventory = inventory - %0 where name = '%1'").arg(quantity.toInt()).arg(name);
    QString result;
    if (!Database::Query(queryString, result)) {
        QMessageBox::warning(this, "Error!", result, QMessageBox::Cancel);
        return false;
    }

    queryString = QString("insert into outputlog (`itemid`, `customerid`, `quantity`, `date`, `price`, `ps`) values ('%0', '%1', '%2', '%3', '%4', '%5')")
            .arg(number).arg(customerId).arg(quantity).arg(date).arg(price).arg(note);
    if (Database::Query(queryString, result)) {
        QMessageBox::information(this, "Success!", "保存成功!", QMessageBox::Ok);
        return true;
    }
    return false;
}

void SaleDialog::on_nameBox_currentIndexChanged(int index)
{
    qDebug() << index;
    SetInvetory();
}
