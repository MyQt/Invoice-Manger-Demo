#include "mainwindow.h"
#include "configdialog.h"
#include "logindialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
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
        }
    }
    ldl.show();
    ldl.SetDatabase(set);
    ldl.ConnectDatabase();
    if (ldl.exec() == ldl.Accepted) {
        w.show();
    }

    return a.exec();
}
