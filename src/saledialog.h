#ifndef SALEDIALOG_H
#define SALEDIALOG_H

#include <QDialog>
#include <QDate>
#include <QMessageBox>
#include "database.h"
#include "productions.h"

namespace Ui {
class SaleDialog;
}

class SaleDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SaleDialog(QWidget *parent = 0);
    ~SaleDialog();

private slots:
    void on_saveButton_clicked();

    void on_nameBox_currentIndexChanged(int index);

private:
    Ui::SaleDialog *ui;
    void SetDefault();
    void SetInvetory();
};

#endif // SALEDIALOG_H
