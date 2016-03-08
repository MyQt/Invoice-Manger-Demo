#include "model.h"

QStandardItemModel *Model::userModel = new QStandardItemModel();
QStandardItemModel *Model::productionModel = new QStandardItemModel();

Model::Model()
{

}

void Model::SetUserModel()
{
    userModel->setColumnCount(9);
    QStringList strList;
    strList << "编号" << "姓名" << "性别" << "电话" << "邮箱" << "入职日期" << "地址" << "职位" << "备注";
    for (int i = 0; i < 9; i++) {
        userModel->setHeaderData(i, Qt::Horizontal, strList[i]);
    }

}

void Model::SetProductionModel()
{
    productionModel->setColumnCount(4);
    QStringList strList;
    strList << "编号" << "名称" << "生产商" << "库存";
    for (int i = 0; i < 4; i++) {
        productionModel->setHeaderData(i, Qt::Horizontal, strList[i]);
    }
}
