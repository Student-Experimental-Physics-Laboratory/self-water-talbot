#ifndef RULERWIDGET_H
#define RULERWIDGET_H

#include "imagewidget.h"
#include "imageprocesser.h"

// In this shit you store all your parameters (for example
// vertical/horizontal ruler
class RulerProcesser : public ImageProcesser
{
public:
   void process(QImage &image) override; // TODO implement
};


class RulerWidget : public ImageWidget
{
public:
    RulerWidget();
    void reprocess() override; //  TODO here just use process(QImage) from your
    // processer

protected:
    void paintEvent(QPaintEvent *event) override; // TODO just draw image
    // (image is in base class)

private:
    RulerProcesser processer;
};

#endif // RULERWIDGET_H
