#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include <QStandardItemModel>

#include "user.h"

class Database
{
public:
    Database();
    ~Database();

    //set database config
    static void SetHost(const QString &host);
    static void SetPort(const int port);
    static void SetName(const QString &name);
    static void SetUser(const QString &user);
    static void SetPassword(const QString &pwd);

    static int userColumnCount;
    static int productionColumnCount;
    static int inputlogColumnCount;
    static int outputlogColumnCount;
    static int customerColumnCount;
    static int producerColumnCount;

    //Connect and login
    static bool Connect();
    static void DisConnect();
    static bool Login(const QString &number, const QString &password, QString &error);

    //set models
    static bool SetUserModel(QStandardItemModel *model, QString &result);
    static bool SetProductionModel(QStandardItemModel *model, QString &result);
    static bool SetProducerModel(QStandardItemModel*model, QString &result);

    //SQL query
    static bool Query(const QString& queryString, QString &result);
    static bool Find(const QString& queryString, QString& result);
    static QString FindValue(const QString& queryString, int index = 0);
    static bool GetInOutLogById(int number, QStringList& strList, QString type = "inputlog");

private:
    static QString host, name, user, password;
    static int port;
    static QSqlDatabase db;
    static bool isConnected;
};

#endif // DATABASE_H
