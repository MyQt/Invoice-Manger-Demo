#ifndef NEWPRODUCTIONDIALOG_H
#define NEWPRODUCTIONDIALOG_H

#include <QDialog>
#include <QDate>
#include <QMessageBox>
#include "database.h"

namespace Ui {
class NewProductionDialog;
}

class NewProductionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewProductionDialog(QWidget *parent = 0);
    ~NewProductionDialog();

private slots:
    void on_saveButton_clicked();

private:
    Ui::NewProductionDialog *ui;
    void SetDefault();
    bool SaveProductionInfo();
};

#endif // NEWPRODUCTIONDIALOG_H
