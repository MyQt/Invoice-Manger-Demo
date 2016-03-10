#include "mainwindow.h"
#include "configdialog.h"
#include "logindialog.h"
#include "newuserdialog.h"
#include <QPluginLoader>
#include <QApplication>
#include <QTextCodec>
#include <QLibrary>

void LoadReleaseConfig(char *argv[]);

int main(int argc, char *argv[])
{
#ifdef QT_NO_DEBUG
    LoadReleaseConfig(argv);
#endif
    QApplication a(argc, argv);
    Database db;
    Setting set;
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
    MainWindow w;
    if (ldl.exec() == ldl.Accepted) {
        w.SetUserModel();
        w.SetProductionModel();
        w.SetUser();
        w.show();
    } else {
        return 0;
    }

    return a.exec();
}


void LoadReleaseConfig(char *argv[])
{
    QTextCodec *xcodec = QTextCodec::codecForLocale() ;
    QString exeDir = xcodec->toUnicode( QByteArray(argv[0]) ) ;
    QString BKE_CURRENT_DIR = QFileInfo( exeDir ).path();
    QString pluginsPath = BKE_CURRENT_DIR + QString("/") + "lib";
    QApplication::setLibraryPaths( QApplication::libraryPaths() << BKE_CURRENT_DIR << pluginsPath) ;
}
