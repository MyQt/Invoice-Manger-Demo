#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include "user.h"

class Database
{
public:
    Database();
    static void SetHost(const QString &host);
    static void SetPort(const int port);
    static void SetName(const QString &name);
    static void SetUser(const QString &user);
    static void SetPassword(const QString &pwd);
    static bool Connect();
    static void DisConnect();
    static bool Login(const QString &username, const QString &password, QString &error);
private:
    static QString host, name, user, password;
    static int port;
    static QSqlDatabase db;
    static bool isConnected;
};

#endif // DATABASE_H
