#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "talbotmatrix.h"
#include "experiment.h"
#include "talbotreporter.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void setParams(const TalbotParams &params);

private slots:
    void on_drawButton_clicked();

    void on_add_new_experiment_clicked();

    void on_delete_selected_experiments_clicked();


    void on_safeButton_clicked();

private:
    void setSplitter();
    void setUpConnections();

    TalbotParams readParams();
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
