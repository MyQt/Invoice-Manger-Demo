#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QInputDialog>
#include "model.h"
#include "database.h"
#include "newuserdialog.h"
#include "newproductiondialog.h"
#include "productions.h"
#include "saledialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void SetUserModel();
    void SetProductionModel();
    void SetUser();

private slots:
    void on_userTableView_clicked(const QModelIndex &index);

    void on_newUserButton_clicked();

    void on_reloadButton_clicked();

    void on_removeUserButton_clicked();

    void on_alterUserButton_clicked();

    void on_findUserButton_clicked();

    void on_productionTableView_clicked(const QModelIndex &index);

    void on_reloadProductionButton_clicked();

    void on_newProductionButton_clicked();

    void on_saleProductionButton_clicked();

private:
    Ui::MainWindow *ui;
    Database db;

    //userTabControl
    void ReloadUserModel();
    void SetAlterUser();
    void SetTextDetail(const QModelIndex &index);
    void LoadUserModel();

    //productionTabControl
    void LoadProductionModel();
    void ReloadProductionModel();
    void SetProductionDetail(const QModelIndex &index);
};

#endif // MAINWINDOW_H
