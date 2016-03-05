#include "database.h"

Database::Database()
{
    this->isConnected = false;
}

void Database::SetHost(const QString &host)
{
    this->host = host;
}

void Database::SetName(const QString &name)
{
    this->name = name;
}

void Database::SetPort(const int port)
{
    this->port = port;
}

void Database::SetUser(const QString &user)
{
    this->user = user;
}

void Database::SetPassword(const QString &pwd)
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
        //return false;
    }
    this->isConnected = true;
    return true;
}

void Database::DisConnect()
{
    db.close();
}

bool Database::Login(const QString &username, const QString &password, QString &result)
{
    QSqlQuery query;
    QString str = "password";
    QString queryString = QString("select * from user where number like '%%0%'").arg(username);
    if (!query.exec(queryString)) {
        result = query.lastError().text();
        return false;
    }
    if (query.first()) {
        QString md5 = query.value(str).toString();
        if (md5 == password) {
            result = "登录成功!";
            return true;
        } else {
            result = "密码错误!";
            return false;
        }
    } else {
        result = "未找到此用户!";
        return false;
    }
    result = "Unknow error!";
    return false;
}
