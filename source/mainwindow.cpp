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

