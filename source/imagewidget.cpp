#include "imagewidget.h"

#include <iostream>

using namespace std;

TalbotImageWidget::TalbotImageWidget(QWidget *parent) : QWidget(parent)
{
    image = QImage(100, 100, QImage::Format_RGB32);
    viewX = image.width() / 2;
}

void TalbotImageWidget::resizeEvent(QResizeEvent *)
{
    image = QImage(width(), height(), QImage::Format_RGB32);
    image.fill(qRgb(0, 0, 0));
    update();
}

void TalbotImageWidget::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    QRect r(this->rect());
    p.drawImage(r, image, r);
    p.setPen(Qt::red);
    p.drawLine(viewX, 0, viewX, height());
}

void TalbotImageWidget::mousePressEvent(QMouseEvent *event)
{
    setFocus();
    viewX = event->pos().x();
    repaint();
}
