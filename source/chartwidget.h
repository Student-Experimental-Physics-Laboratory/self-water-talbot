/*
Чеклин Павел
Виджет для отрисовки графиков

Использование:
Для обновления массива точек использовать updateDots
(несколько вариантов, используй какой удобнее)

Отрисовка дергается через DrawChart::paintEvent() (вызвать у объекта)ы
*/

#ifndef DRAWCHART_H
#define DRAWCHART_H

#include "imageprocesser.h"
#include "imagewidget.h"

#include <QWidget>
#include <QColor> #include <vector>
#include <utility>

#include <cmath>
#include <algorithm>

using namespace std;

template <typename T> int sgn(T val)
{
    return (T(0) < val) - (val < T(0));
}

class ChartProcesser : public ImageProcesser
{
public:
    ChartProcesser() = default;
    void process(QImage &image) override;
    void updateDots(vector<pair<double, double>> newVec);
    void updateDots(const vector<double> &newX, const vector<double> &newY);
    void updateDots(QVector<QPointF> newVec);
private:
    void drawLine(QImage &image, int x1, int y1, int x2, int y2, QColor color);
    vector<double> x;
    vector<double> y;
};

class ChartWidget : public ImageWidget
{
    Q_OBJECT
public:
    explicit ChartWidget(QWidget *parent = nullptr);
    void reprocess() override;
    void updateDots(vector<pair<double, double>> newVec);
    void updateDots(const vector<double> &newX, const vector<double> &newY);
    void updateDots(QVector<QPointF> newVec);
private:
    ChartProcesser processer;
};

#endif // DRAWCHART_H
