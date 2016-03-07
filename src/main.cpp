#include "mainwindow.h"
#include "configdialog.h"
#include "logindialog.h"
#include "newuserdialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Database db;
    Setting set;
    MainWindow w;
    ConfigDialog clf;
    LoginDialog ldl;
    try {
        set.LoadConfigFromXml();
    }
    catch (QString e) {
        QMessageBox::warning(&clf, "Error!", QString("未找到配置文件/数据库配置错误，请从新配置!"), QMessageBox::Ok);
        if (clf.exec() != QDialog::Accepted) {
            return -1;
        } else {
            set.LoadConfigFromXml();
        }
    }
    set.SetDatabase(db);
    ldl.show();
    QElapsedTimer et;
    et.start();
    while(et.elapsed() < 300)
    {
        QCoreApplication::processEvents();
        ldl.ConnectDatabase();
    }
    if (ldl.exec() == ldl.Accepted) {
        w.SetUserModel();
        w.show();
    } else {
        return 0;
    }

    return a.exec();
}
