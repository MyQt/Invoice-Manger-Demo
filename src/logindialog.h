#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include "database.h"
#include <QMessageBox>

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = 0);
    ~LoginDialog();
    void ConnectDatabase(Database &db);
private slots:
    void on_loginButton_clicked();

private:
    Ui::LoginDialog *ui;
};

#endif // LOGINDIALOG_H
