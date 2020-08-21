#include "experimentlist.h"

// debug

#include <iostream>
using namespace std;
// debug end

ExperimentList::ExperimentList(QWidget *parent) : QListWidget(parent)
{
}

void ExperimentList::add()
{
    QListWidgetItem *newItem = new QListWidgetItem("Новый эксперимент (назовите меня как-нибудь)");
    newItem->setFlags(newItem->flags() |
                      Qt::ItemIsUserCheckable |
                      Qt::ItemIsEditable);
    newItem->setSizeHint(QSize(10, 40));
    newItem->setCheckState(Qt::Unchecked);
    addItem(newItem);
}

void ExperimentList::removeSelected()
{

    QList<QListWidgetItem *> checked;
    for (int i = 0; i < count(); ++i)
        if (item(i)->checkState() == Qt::Checked)
            checked.push_back(item(i));
    while (!checked.empty())
    {
        QListWidgetItem *it = checked.first();
        checked.pop_front();
        delete it;
    }
}

void ExperimentList::makeSampleData()
{
    add();
}
