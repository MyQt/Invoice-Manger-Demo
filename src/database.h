#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include <QStandardItemModel>
#include <QMutex>

#include "user.h"

class Database
{
public:
    ~Database();

    static Database* Init();

    //set database config
    void SetHost(const QString &host);
    void SetPort(const int port);
    void SetName(const QString &name);
    void SetUser(const QString &user);
    void SetPassword(const QString &pwd);

    //config
    static int userColumnCount;
    static int productionColumnCount;
    static int inputlogColumnCount;
    static int outputlogColumnCount;
    static int customerColumnCount;
    static int producerColumnCount;

    //Connect and login
    bool Connect();
    void DisConnect();
    bool Login(const QString &number, const QString &password, QString &error);

    //set models
    bool SetUserModel(QStandardItemModel *model, QString &result);
    bool SetProductionModel(QStandardItemModel *model, QString &result);
    bool SetProducerModel(QStandardItemModel*model, QString &result);

    //SQL query
    bool Query(const QString& queryString, QString &result);
    bool Find(const QString& queryString, QString& result);
    QString FindValue(const QString& queryString, int index = 0);
    bool GetInOutLogById(int number, QStringList& strList, QString type = "inputlog");

private:
    Database();
    QString host, name, user, password;
    int port;
    QSqlDatabase db;
    bool isConnected;
};

#endif // DATABASE_H
