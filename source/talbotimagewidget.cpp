#include "talbotimagewidget.h"

#include <iostream>
#include <QDebug>

using namespace std;

void TalbotImageProcesser::process(QImage &image)
{
    image.fill(qRgb(255, 255, 255));
    QPainter p(&image);
    p.setPen(Qt::red);
    p.setBrush(Qt::blue);
    p.drawEllipse(image.rect());
}

TalbotImageWidget::TalbotImageWidget(QWidget *parent) : ImageWidget(parent)
{
    viewX = image.width() / 2;
    setMouseTracking(false);
}

void TalbotImageWidget::paintEvent(QPaintEvent *event)
{
    ImageWidget::paintEvent(event);
    QPainter p(this);
    p.setPen(Qt::red);
    p.drawLine(viewX, 0, viewX, height());
}

void TalbotImageWidget::mousePressEvent(QMouseEvent *event)
{
    setFocus();
    viewX = event->pos().x();
    repaint();
    drawChart();
}

void TalbotImageWidget::mouseMoveEvent(QMouseEvent *event)
{
    setFocus();
    viewX = event->pos().x();
    repaint();
    drawChart();
}

void TalbotImageWidget::drawChart()
{
    qDebug() << "This is a drawChart()";
    vector<double> x = getGraph();
    vector<double> y = getGraph();
    for (size_t i = 0; i < y.size(); i++)
    {
        y.at(i) = i;
    }
    talbotChart->updateDots(x, y);
    talbotChart->reprocess();
}

void TalbotImageWidget::reprocess()
{
    processer.process(this->image);
    this->update();
}

vector<double> TalbotImageWidget::getGraph()
{
    vector<double> result(talbotChart->height());
    for (int i = 0; i < talbotChart->height(); i++)
    {
        QRgb pixel = image.pixel(viewX, i);
        result.at(i) = pixel % 256;
    }
    return result;
}

void TalbotImageWidget::connectChart(ChartWidget *widget)
{
    talbotChart = widget;
}

void TalbotImageWidget::updateTalbotParams(const TalbotParams &newParams)
{
    processer.updateTalbotParams(newParams);
}

