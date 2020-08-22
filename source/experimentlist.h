#ifndef EXPERIMENTLIST_H
#define EXPERIMENTLIST_H

#include <QWidget>
#include <QListWidget>
#include <QListWidgetItem>
#include <QList>
#include <QPair>

#include "experiment.h"
#include "talbotimagewidget.h"

class ExperimentList : public QListWidget
{
    Q_OBJECT
public:
    ExperimentList(QWidget *parent = nullptr);

    void add(const QString &title = "Новый эксперимент (назовите меня как-нибудь)");
    void removeSelected();

signals:
    void experimentSelectionChanged(Experiment *);

public slots:
    void changeSelectedExperiment();

private:
    QList<Experiment *> experiments;
    Experiment *currentSelectedExperiment;
};

#endif // EXPERIMENTLIST_H
