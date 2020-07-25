#ifndef EXPERIMENT_H
#define EXPERIMENT_H

#include <QWidget>
#include <QHBoxLayout>
#include <QCheckBox>
#include <QLabel>
#include <QLineEdit>

class Experiment : public QWidget
{
    Q_OBJECT
public:
    explicit Experiment(QWidget *parent = nullptr);

private:
    QHBoxLayout *layout;

};

#endif // EXPERIMENT_H
