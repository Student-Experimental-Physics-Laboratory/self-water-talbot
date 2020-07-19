#include "talbotimagewidget.h"

#include <iostream>

using namespace std;

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
