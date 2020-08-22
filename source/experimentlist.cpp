#include "experimentlist.h"


#include <QDebug>

ExperimentList::ExperimentList(QWidget *parent) : QListWidget(parent)
{
    connect(this, &ExperimentList::itemSelectionChanged, this, &ExperimentList::changeSelectedExperiment);
    add();
}

void ExperimentList::add(const QString &title)
{

    Experiment *newExperiment = new Experiment;
    experiments.push_back(newExperiment);

    QListWidgetItem *newItem = new QListWidgetItem(title);
    newItem->setFlags(newItem->flags() |
                      Qt::ItemIsUserCheckable |
                      Qt::ItemIsEditable);
    newItem->setSizeHint(QSize(10, 40));
    newItem->setCheckState(Qt::Unchecked);
    addItem(newItem);
    newItem->setSelected(true);
}

void ExperimentList::removeSelected()
{
    QList<QListWidgetItem *> checkedItems;
    QList<Experiment *> checkedExperiments;
    for (int i = 0; i < count(); ++i)
        if (item(i)->checkState() == Qt::Checked)
        {
            checkedItems.push_back(item(i));
            checkedExperiments.push_back(experiments.at(i));
        }
    if (checkedExperiments.size() == experiments.size())
       add("Зачем все удаляешь а?");
    while (!checkedItems.empty())
    {
        QListWidgetItem *it = checkedItems.first();
        Experiment *ex = checkedExperiments.first();
        checkedItems.pop_front();
        checkedExperiments.pop_front();
        experiments.removeOne(ex);
        delete ex;
        delete it;
    }
}

void ExperimentList::changeSelectedExperiment()
{
    Experiment *newSelected = experiments.at(indexFromItem(selectedItems().first()).row());
    emit experimentSelectionChanged(newSelected);
}
