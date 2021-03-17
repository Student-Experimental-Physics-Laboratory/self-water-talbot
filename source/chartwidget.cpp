#include "chartwidget.h"

void ChartProcesser::process(QImage &image)
{
    QColor line = Qt::black;
    QColor background = Qt::white;

    image.fill(background);
    double chart_width = image.width();

    double x_dw = 255 / chart_width;

    if (y.size() > 1)
    {
        double last_y = y.at(0);
        double last_x = x.at(0);
        for (size_t i = 1; i < y.size(); i++)
        {
            drawLine(image, last_x / x_dw, last_y,
                     x.at(i) / x_dw, y.at(i), line);
            last_y = y.at(i);
            last_x = x.at(i);
        }
    }
}

void ChartProcesser::updateDots(vector<pair<double, double> > newVec)
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

void ChartProcesser::updateDots(const vector<double> &newX, const vector<double> &newY)
{
    x = newX;
    y = newY;
}

void ChartProcesser::updateDots(QVector<QPointF> newVec)
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

void ChartProcesser::drawLine(QImage &image, int x0, int y0, int x1, int y1, QColor color)
{
    int dx = x1 - x0;
    int dy = y1 - y0;
    if (abs(dx) == 0 && abs(dy) == 0)
    {
        image.setPixel(x0, y0, color.rgb());
        return;
    }

    int sx = sgn(dx);
    int sy = sgn(dy);

    dx = abs(dx);
    dy = abs(dy);

    bool change = false;
    if (dy >= dx)
    {
        swap(dx, dy);
        change = true;
    }
    int e = 2 * dy - dx;
    int x = x0;
    int y = y0;

    for (int i = 0; i <= dx; i++)
    {
        image.setPixel(x, y, color.rgb());
        if (e >= 0)
        {
            if (change)
                x = x + sx;
            else
                y = y + sy;
            e = e - 2 * dx;
        }
        if (change)
            y = y + sy;
        else
            x = x + sx;
        e = e + 2 * dy;
    }
}

ChartWidget::ChartWidget(QWidget *parent) : ImageWidget(parent)
{

}

void ChartWidget::reprocess()
{
    processer.process(this->image);
    this->update();
}

void ChartWidget::updateDots(vector<pair<double, double> > newVec)
{
    processer.updateDots(newVec);
}

void ChartWidget::updateDots(const vector<double> &newX, const vector<double> &newY)
{
    processer.updateDots(newX, newY);
}

void ChartWidget::updateDots(QVector<QPointF> newVec)
{
    processer.updateDots(newVec);
}
