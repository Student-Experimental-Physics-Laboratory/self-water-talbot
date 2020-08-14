#include "talbotimagewidget.h"

#include <iostream>

using namespace std;

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
    this->update();
}

void TalbotImageWidget::updateTalbotParams(const TalbotParams &newParams)
{
    processer.updateTalbotParams(newParams);
}
