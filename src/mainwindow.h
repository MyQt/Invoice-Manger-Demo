#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QInputDialog>
#include "model.h"
#include "database.h"
#include "newuserdialog.h"

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

private slots:
    void on_userTableView_clicked(const QModelIndex &index);

    void on_newUserButton_clicked();

    void on_reloadButton_clicked();

    void on_removeUserButton_clicked();

    void on_alterUserButton_clicked();

    void on_findUserButton_clicked();

    void on_productionTableView_clicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
    Database db;

    void SetUser();

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
