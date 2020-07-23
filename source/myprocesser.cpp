#include "myprocesser.h"

MyProcesser::MyProcesser() :
    params_({1})
{}

void MyProcesser::process(QImage &image)
{
    QPainter p(&image);
    image.fill(qRgb(255, 255, 255));
    p.drawEllipse(image.rect());
}
