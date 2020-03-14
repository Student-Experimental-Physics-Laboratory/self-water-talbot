#include "mainwindow.h"
#include "ui_mainwindow.h"

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
    // добавляй сюда свою функцию
    ui->widget->drawVector(
                std::vector<std::vector<unsigned int>>
                (100, std::vector<unsigned int>(100, 100)));
}
