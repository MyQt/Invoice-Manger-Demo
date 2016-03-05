#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QSqlError>

class Database
{
public:
    Database();
    void SetHost(QString &host);
    void SetPort(int port);
    void SetName(QString &name);
    void SetUser(QString &user);
    void SetPassword(QString &pwd);
    bool Connect();

private:
    QString host, name, user, pwd;
    int port;
    QSqlDatabase db;
};

#endif // DATABASE_H
