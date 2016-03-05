#include "mainwindow.h"
#include "configdialog.h"
#include "logindialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Setting set;
    Database db;
    MainWindow w;
    ConfigDialog clf;
    LoginDialog ldl;
    try {
        set.LoadConfigFromXml();
    }
    catch (QString e) {
        QMessageBox::warning(&clf, "Error!", e, QMessageBox::Ok);
        if (clf.exec() != QDialog::Accepted) {
            return -1;
        }
    }
    set.SetDatabase(db);
    ldl.show();
    ldl.ConnectDatabase(db);

    return a.exec();
}
