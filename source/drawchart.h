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

#include <QWidget>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <vector>
#include <utility>

#include <cmath>

#define PI 3.14159265

using namespace std;

QT_CHARTS_USE_NAMESPACE

class DrawChart : public QWidget
{
    Q_OBJECT
public:
    explicit DrawChart(QWidget *parent = nullptr);

    void updateDots(vector<pair<double, double>> newVec); // пары (x, y)
    void updateDots(const vector<double> &newX, const vector<double> &newY);
    void updateDots(QVector<QPointF> newVec);
    void paintEvent(QPaintEvent *event=nullptr) override;
private:

    void setSeries();
    void setChart();
    void setChartView();

    vector<double> x;
    vector<double> y;

    QChartView *chartView;
    QChart *chart;
    QLineSeries *series;
};

#endif // DRAWCHART_H
