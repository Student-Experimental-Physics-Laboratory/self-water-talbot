#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "talbotmatrix.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->on_drawButton_clicked();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_drawButton_clicked()
{
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
