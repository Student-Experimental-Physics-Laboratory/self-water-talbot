#ifndef DRAWCHART_H
#define DRAWCHART_H

#include <QWidget>

class DrawChart : public QWidget
{
    Q_OBJECT
public:
    explicit DrawChart(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *event) override;
};

#endif // DRAWCHART_H
