#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "talbotmatrix.h"

#include <QList>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setSplitter();
    ui->talbotImage->connectChart(ui->talbotChart);
    ui->vruler->setOrientation(Qt::Vertical);
    ui->hruler->setOrientation(Qt::Horizontal);
    ui->cruler->setOrientation(Qt::Horizontal);
    ui->vruler->reprocess();
    ui->hruler->reprocess();
    ui->cruler->reprocess();
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
