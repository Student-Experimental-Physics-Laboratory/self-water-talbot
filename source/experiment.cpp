#include "experiment.h"

Experiment::Experiment(QWidget *parent) : QWidget(parent)
{
    layout = new QHBoxLayout();
    this->setLayout(layout);
    this->layout->addWidget(new QLabel("#1"));
    this->layout->addWidget(new QLineEdit());
}
