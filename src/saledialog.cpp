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
    SetInvetory();
}

void SaleDialog::SetInvetory()
{
    QString name = ui->nameBox->currentText();
    QString queryString = QString("select from production where name = '%0'").arg(name);
    int inventory = Database::FindValue(queryString, 2).toInt();
    ui->inventoryLabel->setText(tr("库存: ") + QString::number(inventory));

}

void SaleDialog::on_saveButton_clicked()
{

}

void SaleDialog::on_nameBox_currentIndexChanged(int index)
{
    SetInvetory();
}
