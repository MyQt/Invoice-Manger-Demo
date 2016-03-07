#ifndef NEWUSERDIALOG_H
#define NEWUSERDIALOG_H

#include <QDialog>
#include <QDate>
#include "database.h"
#include "user.h"
#include "setting.h"

namespace Ui {
class NewUserDialog;
}

class NewUserDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewUserDialog(QWidget *parent = 0);
    ~NewUserDialog();

private slots:
    void on_saveButton_clicked();

private:
    Ui::NewUserDialog *ui;
    void SetDefault();
};

#endif // NEWUSERDIALOG_H
