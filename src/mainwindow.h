#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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

    void SetUser();
    void SetUserModel();
private slots:
    void on_userTableView_clicked(const QModelIndex &index);

    void on_newUserButton_clicked();

private:
    Ui::MainWindow *ui;
    Database db;
};

#endif // MAINWINDOW_H
