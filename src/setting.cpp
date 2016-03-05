#include "setting.h"

Setting::Setting()
{

}

void Setting::SetHost(QString &host)
{
    this->host = host;
}

void Setting::SetName(QString &name)
{
    this->name = name;
}

void Setting::SetPort(int port)
{
    this->port = port;
}

void Setting::SetDatabaseUser(QString &user)
{
    this->databaseUser = user;
}

void Setting::SetDatabasePassword(QString &pwd)
{
    this->databasePwd = pwd;
}

void Setting::SetUser(QString &user)
{
    this->user = user;
}

void Setting::SetPassword(QString &pwd)
{
    this->pwd = pwd;
}

QString Setting::GetPath()
{
    QStringList envList = QProcess::systemEnvironment();
    QString tempPath;
    foreach (tempPath, envList) {
        if (tempPath.startsWith("HOME=")) {
            tempPath = tempPath.mid(5);
            break;
        }
    }
    this->path = tempPath + "/Invoice";
    return this->path;
}

bool Setting::LoadConfigFromXml()
{
    if (this->path.isNull())
        this->GetPath();
    QFile file(path + "/config.xml");
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        throw "Cannot read file:" + file.errorString();
        return false;
    }

    xmlReader.setDevice(&file);
    while (!xmlReader.atEnd()) {
        if (xmlReader.isStartElement()) {
            if (xmlReader.name() == "mysql") {
                ReadMysqlConfig();
            } else if (xmlReader.name() == "user") {
                ReadUserConfig();
            } else if (xmlReader.name() != "config"){
                //qDebug()<<xmlReader.name();
                xmlReader.raiseError(QString("Not a valid config file!"));
            } else {
                xmlReader.readNext();
            }
        }
        else {
            xmlReader.readNext();
        }
    }
    file.close();
    if (xmlReader.hasError()) {
        throw xmlReader.errorString();
        return false;
    }
    if (file.error()) {
        throw "Cannot read file:" + file.errorString();
        return false;
    }
    return true;
}

void Setting::ReadMysqlConfig()
{
    xmlReader.readNext();
    while (!xmlReader.isEndElement()) {
        if (xmlReader.isStartElement()) {
            if (xmlReader.name() == "host") {
                this->host = xmlReader.readElementText();
            } else if (xmlReader.name() == "port") {
                this->port = xmlReader.readElementText().toInt();
            } else if (xmlReader.name() == "database") {
                this->name = xmlReader.readElementText();
            } else if (xmlReader.name() == "username") {
                this->databaseUser = xmlReader.readElementText();
            } else if (xmlReader.name() == "password") {
                this->databasePwd = xmlReader.readElementText();
            } else {
                //qDebug() << xmlReader.name();
                xmlReader.raiseError(QString("Not a valid config file!"));
            }
        }
        xmlReader.readNext();
    }
}

void Setting::ReadUserConfig()
{
    xmlReader.readNext();
    while (!xmlReader.isEndElement()) {
        if (xmlReader.isStartElement()) {
            if (xmlReader.name() == "username") {
                this->user = xmlReader.readElementText();
            } else if (xmlReader.name() == "password") {
                this->pwd = xmlReader.readElementText();
            } else {
                //qDebug()<<xmlReader.name();
                xmlReader.raiseError(QString("Not a valid config file!"));
            }
        }
        xmlReader.readNext();
    }
}

bool Setting::SaveConfigToXml()
{
    if (this->path.isNull())
        this->GetPath();
    QDir dir(path);
    if (!dir.exists()) {
        dir.mkdir(path);
    }

    QFile file(path + "/config.xml");
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        throw "Cannot write file:" + file.errorString();
        return false;
    }

    xmlWriter.setDevice(&file);
    xmlWriter.setAutoFormatting(true);
    xmlWriter.writeStartDocument();
    xmlWriter.writeStartElement("config");
    xmlWriter.writeStartElement("mysql");
    xmlWriter.writeAttribute("id", "1");
    xmlWriter.writeTextElement("host", this->host);
    xmlWriter.writeTextElement("port", QString::number(this->port));
    xmlWriter.writeTextElement("database", this->name);
    xmlWriter.writeTextElement("username", this->databaseUser);
    xmlWriter.writeTextElement("password", this->databasePwd);
    xmlWriter.writeEndElement();
    xmlWriter.writeStartElement("user");
    xmlWriter.writeAttribute("id", "2");
    xmlWriter.writeTextElement("username", this->user);
    xmlWriter.writeTextElement("password", this->pwd);
    xmlWriter.writeEndElement();
    xmlWriter.writeEndDocument();
    file.close();

    if (file.error()) {
        throw "Cannot write file:" + file.errorString();
        return false;
    }
    return true;
}

void Setting::SetDatabase(Database &db)
{
    db.SetHost(this->host);
    db.SetName(this->name);
    db.SetPort(this->port);
    db.SetUser(this->databaseUser);
    db.SetPassword(this->databasePwd);
}

QString Setting::ToMD5(const QString &str)
{
    QByteArray bb = QCryptographicHash::hash(str.toUtf8(), QCryptographicHash::Md5);
    return bb.toHex();
}
