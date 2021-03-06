#ifndef RULERWIDGET_H
#define RULERWIDGET_H

#include "imagewidget.h"
#include "imageprocesser.h"

#include <QPainter>
#include <QResizeEvent>

// In this shit you store all your parameters (for example
// vertical/horizontal ruler
class RulerProcesser : public ImageProcesser
{
public:
    RulerProcesser(Qt::Orientation orient);
    void setOrientation(Qt::Orientation orient);
    void setMetrix(double mm);

    inline Qt::Orientation Orientation() {return this->orientation;}

    void process(QImage &image) override; // TODO implement
private:
    Qt::Orientation orientation;
    double mm;
};


class RulerWidget : public ImageWidget
{
public:
    explicit RulerWidget(QWidget *parent = nullptr);
    void setOrientation(Qt::Orientation orient);

    void reprocess() override;

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    RulerProcesser processer;
};

#endif // RULERWIDGET_H
