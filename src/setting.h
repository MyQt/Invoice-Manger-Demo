#ifndef SETTING_H
#define SETTING_H

#include <QFile>
#include <QDir>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QMessageBox>
#include <QProcess>
#include <QDebug>
#include <QCryptographicHash>
#include "database.h"

#define mysql_config 1
#define user_config 2

class Setting
{
public:
    static Setting* Init();
    bool SaveConfigToXml();
    bool LoadConfigFromXml();
    void SetDatabase(Database &db);
    QString GetPath();
    static QString ToMD5(const QString &str);

    void SetHost(QString &host);
    void SetPort(int port);
    void SetName(QString &name);
    void SetDatabaseUser(QString &user);
    void SetDatabasePassword(QString &pwd);
    void SetUser(QString &user);
    void SetPassword(QString &pwd);

private:
    Setting();

    static Setting set;

    void ReadMysqlConfig();
    void ReadUserConfig();
    QXmlStreamReader xmlReader;
    QXmlStreamWriter xmlWriter;
    QString host, name, databaseUser, databasePwd, user, pwd;
    QString path;
    int port;
};

#endif // SETTING_H
