
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "talbotmatrix.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_drawButton_clicked();

    void on_add_new_experiment_clicked();

    void on_delete_selected_experiments_clicked();

private:
    void setSplitter();
    TalbotParams readParams();
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
