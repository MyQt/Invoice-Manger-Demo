#ifndef NEWUSERDIALOG_H
#define NEWUSERDIALOG_H

#include <QDialog>
#include <QDate>
#include "database.h"
#include "user.h"
#include "setting.h"
#include "alteruser.h"

namespace Ui {
class NewUserDialog;
}

class NewUserDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewUserDialog(QWidget *parent = 0);
    ~NewUserDialog();
    void GetAlterUser();

private slots:
    void on_saveButton_clicked();

private:
    Ui::NewUserDialog *ui;

    Database *db;
    void SetDefault();
    void SaveUserInfo();
    void AlterUserInfo();
    void DeleteUserInfo();
};

#endif // NEWUSERDIALOG_H
