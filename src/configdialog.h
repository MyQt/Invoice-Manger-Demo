#ifndef CONFIGDIALOG_H
#define CONFIGDIALOG_H

#include <QDialog>
#include <QMessageBox>
#include "setting.h"

namespace Ui {
class ConfigDialog;
}

class ConfigDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConfigDialog(QWidget *parent = 0);
    ~ConfigDialog();

private slots:
    void on_saveButton_clicked();

private:
    Ui::ConfigDialog *ui;
};

#endif // CONFIGDIALOG_H
