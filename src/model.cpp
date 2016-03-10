#include "model.h"

QStandardItemModel *Model::userModel = new QStandardItemModel();
QStandardItemModel *Model::productionModel = new QStandardItemModel();

Model::Model()
{

}

void Model::SetUserModel()
{
    userModel->setColumnCount(Database::userColumnCount - 1);
    QStringList strList;
    strList << "编号" << "姓名" << "性别" << "电话" << "邮箱" << "入职日期" << "地址" << "职位" << "备注";
    for (int i = 0; i < Database::userColumnCount - 1; i++)
    {
        userModel->setHeaderData(i, Qt::Horizontal, strList[i]);
    }

}

void Model::SetProductionModel()
{
    productionModel->setColumnCount(Database::productionColumnCount);
    QStringList strList;
    strList << "编号" << "名称" << "库存" << "备注";
    for (int i = 0; i < Database::productionColumnCount; i++)
    {
        productionModel->setHeaderData(i, Qt::Horizontal, strList[i]);
    }
}
