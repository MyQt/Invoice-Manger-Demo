#include "database.h"

Database::Database()
{

}

void Database::SetHost(QString &host)
{
    this->host = host;
}

void Database::SetName(QString &name)
{
    this->name = name;
}

void Database::SetPort(int port)
{
    this->port = port;
}

void Database::SetUser(QString &user)
{
    this->user = user;
}

void Database::SetPassword(QString &pwd)
{
    this->pwd = pwd;
}

bool Database::Connect()
{
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setDatabaseName(this->name);
    db.setHostName(host);
    db.setPort(port);
    db.setUserName(user);
    db.setPassword(pwd);

    if (!db.open()) {
        throw "Connect to MySql error: " + db.lastError().text();
        return false;
    }
    return true;
}
