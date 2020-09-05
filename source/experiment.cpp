#include "experiment.h"

Experiment::Experiment(QObject *parent)
{
}

QImage &Experiment::getTalbotImage()
{
    return talbotImage;
}

int &Experiment::getViewX()
{
    return talbotViewX;
}

TalbotParams &Experiment::getTalbotParams()
{
    return talbotParams;
}

void Experiment::setTalbotThings(const QImage &image_, int viewX_, const TalbotParams &talbotParams_)
{
    setTalbotImage(image_);
    setViewX(viewX_);
    setTalbotParams(talbotParams_);
}

void Experiment::setTalbotImage(const QImage &image_)
{
    talbotImage = image_;
    isSet_ = true;
}

void Experiment::setViewX(int viewX_)
{
    talbotViewX = viewX_;
    isSet_ = true;
}

void Experiment::setTalbotParams(const TalbotParams &params)
{
    talbotParams = params;
}

bool Experiment::isSet()
{
    return isSet_;
}
