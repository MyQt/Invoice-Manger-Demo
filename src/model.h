#ifndef MODEL_H
#define MODEL_H

#include <QStandardItemModel>

class Model
{
public:
    Model();
    static void SetUserModel();
    static QStandardItemModel *userModel;
private:
};

#endif // MODEL_H
