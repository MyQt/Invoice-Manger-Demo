#ifndef MODEL_H
#define MODEL_H

#include <QStandardItemModel>

class Model
{
public:
    Model();
    static void SetUserModel();
    static void SetProductionModel();
    static QStandardItemModel *userModel;
    static QStandardItemModel *productionModel;

private:
};

#endif // MODEL_H
