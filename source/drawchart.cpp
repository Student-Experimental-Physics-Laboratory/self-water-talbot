#include "drawchart.h"

DrawChart::DrawChart(QWidget *parent) : QWidget(parent)
{
}


void DrawChart::updateDots(vector<pair<double, double>> newVec)
{
    x.clear();
    y.clear();
    x.reserve(newVec.size());
    y.reserve(newVec.size());
    for (const auto point: newVec)
    {
        x.push_back(point.first);
        y.push_back(point.second);
    }
}

void DrawChart::updateDots(const vector<double> &newX, const vector<double> &newY)
{
    x = newX;
    y = newY;
}

void DrawChart::updateDots(QVector<QPointF> newVec)
{
    x.clear();
    y.clear();
    x.reserve(newVec.size());
    y.reserve(newVec.size());
    for (const QPointF &point: newVec)
    {
        x.push_back(point.x());
        y.push_back(point.y());
    }
}

void DrawChart::setSeries()
{
    series = new QLineSeries();

    for (size_t i = 0; i < x.size(); ++i)
        series->append(x[i], y[i]);
}

void DrawChart::setChart()
{
    chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(series);
    chart->setBackgroundRoundness(0);
    chart->setContentsMargins(0, 0, 0, 0);
}

void DrawChart::setChartView()
{
    chartView = new QChartView(chart, this);
    chartView->resize(this->width(), this->height());
}

void DrawChart::paintEvent(QPaintEvent *event)
{
    this->setSeries();
    this->setChart();
    this->setChartView();
    chartView->show();
}
