#include "imagewidget.h"

#include <iostream>

using namespace std;


ImageWidget::ImageWidget(QWidget *parent) : QWidget(parent)
{
    image = QImage(100, 100, QImage::Format_RGB32);
}

void ImageWidget::resizeEvent(QResizeEvent *)
{
    image = QImage(width(), height(), QImage::Format_RGB32);
    image.fill(qRgb(0, 0, 0));
    update();
}


void ImageWidget::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    QRect r(this->rect());
    p.drawImage(r, image, r);
}
