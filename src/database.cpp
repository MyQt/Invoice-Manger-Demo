#include "database.h"

QString Database::host = "";
int Database::port = 3306;
QString Database::name = "";
QString Database::user = "";
QString Database::password = "";
bool Database::isConnected = false;
QSqlDatabase Database::db = QSqlDatabase::addDatabase("QMYSQL");

Database::Database()
{

}

void Database::SetHost(const QString &host)
{
    Database::host = host;
}

void Database::SetName(const QString &name)
{
    Database::name = name;
}

void Database::SetPort(const int port)
{
    Database::port = port;
}

void Database::SetUser(const QString &user)
{
    Database::user = user;
}

void Database::SetPassword(const QString &pwd)
{
    Database::password = pwd;
}

bool Database::Connect()
{
    db.setDatabaseName(name);
    db.setHostName(host);
    db.setPort(port);
    db.setUserName(user);
    db.setPassword(password);

    if (!db.open()) {
        throw "Connect to MySql error: " + db.lastError().text();
        //return false;
    }
    isConnected = true;
    return true;
}

void Database::DisConnect()
{
    db.close();
}

bool Database::Login(const QString &username, const QString &password, QString &result)
{
    QSqlQuery query;
    QString str1 = "password";
    QString str2 = "name";
    QString str3 = "level";
    QString queryString = QString("select * from user where number like '%%0%'").arg(username);
    if (!query.exec(queryString)) {
        result = query.lastError().text();
        return false;
    }
    if (query.first()) {
        QString md5 = query.value(str1).toString();
        if (md5 == password) {
            result = "登录成功!";
            QString username = query.value(str2).toString();
            int level = query.value(str3).toString().toInt();
            User::username = username;
            User::level = level;
            User::isLogined = true;
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
