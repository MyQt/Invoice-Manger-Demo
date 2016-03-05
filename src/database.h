#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>

class Database
{
public:
    Database();
    void SetHost(const QString &host);
    void SetPort(const int port);
    void SetName(const QString &name);
    void SetUser(const QString &user);
    void SetPassword(const QString &pwd);
    bool Connect();
    void DisConnect();
    bool Login(const QString &username, const QString &password, QString &result);
private:
    QString host, name, user, pwd;
    int port;
    QSqlDatabase db;
    bool isConnected;
};

#endif // DATABASE_H
