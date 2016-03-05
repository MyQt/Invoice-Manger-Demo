#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QMessageBox>
#include "setting.h"
#include "database.h"

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = 0);
    ~LoginDialog();
    void ConnectDatabase();
private slots:
    void on_loginButton_clicked();
private:
    Ui::LoginDialog *ui;
    Database db;

};

#endif // LOGINDIALOG_H
