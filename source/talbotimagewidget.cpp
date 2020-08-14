#include "talbotimagewidget.h"

#include <iostream>

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
}

void TalbotImageWidget::reprocess()
{
    processer.process(this->image);
}
