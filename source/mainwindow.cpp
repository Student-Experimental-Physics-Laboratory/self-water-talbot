#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "talbotmatrix.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_drawButton_clicked()
{
//    пример использования
//    vector<double> newX(100), newY(100);
//    for (size_t i = 0; i < newX.size(); ++i)
//        newX[i] = i;
//    for (size_t i = 0; i < newY.size(); ++i)
//        newY[i] = i * i;
//    ui->chartWidget->updateDots(newX, newY);
    ui->chartWidget->paintEvent();

    int sources = this->ui->sources_input->value();
    double phase = this->ui->phase_input->value();
    double wave_len = this->ui->wavelen_input->value();
    double wave_slope = this->ui->slope_input->value();
    bool is_reflectible = this->ui->is_reflectible_input->isChecked();
    double viscosity = this->ui->viscosity_input->value();
    TalbotMatrix buf_mat(this->ui->widget->size().height(), this->ui->widget->size().width());
    buf_mat.updateSources(sources, is_reflectible);
    buf_mat.updateParams(phase, wave_len, wave_slope, viscosity);
    ui->widget->drawVector(buf_mat.getMatrix());
}
