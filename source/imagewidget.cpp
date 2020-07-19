#include "imagewidget.h"

ImageWidget::ImageWidget(QWidget *parent) : QWidget(parent)
{

}

void ImageWidget::resizeImage(QImage *image, const QSize &newSize)
{
    if (image->size() == newSize)
        return;

    QImage newImage(newSize, QImage::Format_RGB32);
    newImage.fill(qRgb(0, 0, 0));
    QPainter painter(&newImage);
    painter.drawImage(QPoint(0, 0), *image);
    *image = newImage;
}

void ImageWidget::resizeEvent(QResizeEvent *event)
{
    int newWidth = width();
    int newHeight = height();

    resizeImage(&image, QSize(newWidth, newHeight));
}

void ImageWidget::paintEvent(QPaintEvent *event)
{
    QRect thisRect = rect();
    QPainter p(this);
    p.drawImage(thisRect, image, thisRect);
}
