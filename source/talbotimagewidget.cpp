#include "talbotimagewidget.h"

#include <QDebug>

// ************** TalbotImageProcesser Implementation **************

void TalbotImageProcesser::process(QImage &image)
{
    ohThisIsTalbot.drawTalbot(image);
}

void TalbotImageProcesser::updateTalbotParams(const TalbotParams &newParams)
{
    ohThisIsTalbot.updateParams(newParams);
}

// ************** TalbotImageWidget Implementation **************

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
    setViewX(event->pos().x());
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
//    qDebug() << "This is a drawChart()";
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
    currentExperiment->setTalbotImage(this->image);
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
    currentExperiment->setTalbotParams(newParams);
    processer.updateTalbotParams(newParams);
}

void TalbotImageWidget::setImage(const QImage &image_)
{
    QPainter p(&image);
    QRect drawRect(image.rect());
    p.drawImage(drawRect, image_, drawRect);
    repaint();
}

void TalbotImageWidget::setViewX(const int viewX_)
{
    viewX = viewX_;
    currentExperiment->setViewX(viewX_);
    repaint();
    drawChart();
}

void TalbotImageWidget::connectExperiment(Experiment *experiment)
{
    currentExperiment = experiment;
    if (experiment->isSet())
    {
        updateTalbotParams(experiment->getTalbotParams());;
        setImage(experiment->getTalbotImage());
        setViewX(experiment->getViewX());
    }
}
