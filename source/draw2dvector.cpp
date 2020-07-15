#include "draw2dvector.h"

#include <exception>
#include <string>
#include <iterator>

#define GRAYTORGB(x) ((x<<16) + (x << 8) + (x))

Draw2DVector::Draw2DVector(QWidget *parent) : QWidget(parent)
{

}

void Draw2DVector::setVector(std::vector<std::vector<unsigned int> > vec)
{
    if (vec.size() == 0)
        throw std::invalid_argument("Empty vector!");
    if ((int)vec.size() > this->width())
        throw std::invalid_argument("Row count must too big");
    if ((int)vec[0].size() > this->height())
        throw std::invalid_argument("Column count is too big");

    points = vec;
}

void Draw2DVector::mousePressEvent(QMouseEvent *event)
{
    this->graphicX = event->x();
    this->update();
}

void Draw2DVector::drawVector(std::vector<std::vector<unsigned int> > vec)
{
    this->setVector(vec);
    this->update();
}

void Draw2DVector::paintEvent(QPaintEvent *event)
{
    if (points.size())
    {
        QPainter p(this);
        int r = points.size();
        int c = points[0].size();
        QImage im(r, c, QImage::Format_RGB32);
        for (int i = 0; i < r; ++i)
            for (int j = 0; j < c; ++j)
            {
                im.setPixel(i, j, GRAYTORGB(points[i][j]));
            }
        for (int i = 0; i < c; i++)
        {
            im.setPixel(this->graphicX, i, 255 << 16);
        }
        p.drawImage(0, 0, im);
    }
}
