#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "talbotmatrix.h"

#include <QList>
#include <QDebug>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setUpConnections();

    this->setSplitter();
    ui->talbotImage->connectChart(ui->talbotChart);
    ui->vruler->setOrientation(Qt::Vertical);
    ui->hruler->setOrientation(Qt::Horizontal);
    ui->cruler->setOrientation(Qt::Horizontal);
    ui->vruler->reprocess();
    ui->hruler->reprocess();
    ui->cruler->reprocess();

}

void MainWindow::setUpConnections()
{
    connect(ui->experiments, &ExperimentList::experimentSelectionChanged, ui->talbotImage, &TalbotImageWidget::connectExperiment);
    emit ui->experiments->itemSelectionChanged();

    connect(ui->talbotImage, &TalbotImageWidget::talbotParamsUpdated, this, &MainWindow::setParams);
}

TalbotParams MainWindow::readParams()
{
    return TalbotParams(ui->n_sources_input->value(),
                        ui->phase_input->value(),
                        ui->wave_len_input->value(),
                        ui->wave_slope_input->value(),
                        ui->reflectible_input->isChecked(),
                        ui->viscosity_input->value());
}

void MainWindow::setParams(const TalbotParams &params)
{
    ui->n_sources_input->setValue(params.n_sources);
    ui->phase_input->setValue(params.phase);
    ui->wave_len_input->setValue(params.wave_len);
    ui->wave_slope_input->setValue(params.wave_slope);
    ui->reflectible_input->setChecked(params.reflectible);
    ui->viscosity_input->setValue(params.viscosity);
}

void MainWindow::setSplitter()
{
    QList<int> sizes;
    sizes.append(2 * (width() - 250) / 3);
    sizes.append((width() - 250) / 3);
    sizes.append(250);
    ui->splitter->setSizes(sizes);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_drawButton_clicked()
{
    TalbotParams params(readParams());
    ui->talbotImage->updateTalbotParams(params);
    ui->talbotImage->reprocess();
    ui->talbotImage->drawChart();
    ui->vruler->reprocess();
    ui->hruler->reprocess();
    ui->cruler->reprocess();
}

void MainWindow::on_add_new_experiment_clicked()
{
    ui->experiments->add();
}

void MainWindow::on_delete_selected_experiments_clicked()
{
    ui->experiments->removeSelected();
}


void MainWindow::on_safeButton_clicked()
{
    TalbotReporter tr(ui->talbotImage->getImage(),
                      ui->talbotChart->getImage(),
                      ui->hruler->getImage(),
                      ui->vruler->getImage(),
                      ui->cruler->getImage(),
                      readParams());

    tr.safeToFile(QFileDialog().getSaveFileName());
}
