#include "rulerwidget.h"

RulerProcesser::RulerProcesser(Qt::Orientation orient) : orientation(orient)
{
    setMetrix(100);
}

void RulerProcesser::setOrientation(Qt::Orientation orient)
{
    this->orientation = orient;
}

void RulerProcesser::setMetrix(double mm)
{
    this->mm = mm;
}

void RulerProcesser::process(QImage &image)
{
    QPainter p(&image);
    p.setPen(Qt::black);
    p.setBrush(QColor(0xfaffff));

    QRect r(0, 0, image.width() - 1, image.height() - 1);
    p.drawRect(r);

    double i10 = 0;
    double i5 = 5;

    int cnt = 1;
    int h = image.height(), w = image.width();

    if (orientation == Qt::Horizontal)
    {
        double coeff = (double) w / mm;
        while (i5 < mm) {
            int x = int(i10 * w / mm);
            p.drawLine(x, h, x, h - 8);
            if (i10 > 0 && (coeff >= 1.5 || (coeff >= 0.7 && !(cnt % 2)) || (coeff >= 0.3 && !(cnt % 4)) ))
                p.drawText(x-15, h - 27, 32, h, Qt::AlignHCenter, QString::number(i10/10));

            // 5 mm
            if (coeff >= 1) {
                x = int(i5 * w / mm);
                p.drawLine(x,h,x,h-5);
            }

            // 1 mm
            if (coeff >= 2) {
                for (int i = 1; i < 10; ++i) {
                    x = int((double)(i10+i) * w / mm);
                    p.drawLine(x,h,x,h-3);
                }
            }

            i10 += 10;
            i5 += 10;
            cnt++;
        }
    }
    else
    {
        double coeff = (double)h / mm;

        while (i5 < mm) {
            // 10 mm
            int x = int(i10 * h / mm);
            p.drawLine(w,x,w-8,x);

            if (i10 > 0 && (coeff >= 1.5 || (coeff >= 0.7 && !(cnt % 2)) || (coeff >= 0.3 && !(cnt % 4)) )) {
                p.rotate(-90);
                p.drawText(int(-(i10 * h / mm + 15)),w - 27,32,w,Qt::AlignHCenter, QString::number(i10/10));
                p.rotate(90);
            }

            // 5 mm
            if (coeff >= 1) {
                x = int( i5 * h / mm );
                p.drawLine(w,x,w-5,x);
            }

            // 1 mm
            if (coeff >= 2) {
                for (int i = 1; i < 10; ++i) {
                    x = int( (double)(i10+i) * h / mm );
                    p.drawLine(w,x,w-3,x);
                }
            }

            i10 += 10;
            i5 += 10;
            cnt++;
        }
    }
}

RulerWidget::RulerWidget(QWidget *parent) : ImageWidget(parent),
                                            processer(Qt::Horizontal)
{

}

void RulerWidget::setOrientation(Qt::Orientation orient)
{
    if (processer.Orientation() != orient)
    {
        processer.setOrientation(orient);
        resize(height(), width());
    }
}

void RulerWidget::reprocess()
{
    processer.process(this->image);
    this->update();
}

void RulerWidget::resizeEvent(QResizeEvent *event)
{
    ImageWidget::resizeEvent(event);
    reprocess();
}


