#ifndef EXPERIMENTLIST_H
#define EXPERIMENTLIST_H

#include <QWidget>
#include <QListWidget>
#include <QListWidgetItem>
#include <QList>
#include <QPair>


class ExperimentList : public QListWidget
{
    Q_OBJECT
public:
    ExperimentList(QWidget *parent = nullptr);
    void makeSampleData();

    void add();
    void removeSelected();
private:
};

#endif // EXPERIMENTLIST_H
