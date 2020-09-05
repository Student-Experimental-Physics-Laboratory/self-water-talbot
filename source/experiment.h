#ifndef EXPERIMENT_H
#define EXPERIMENT_H

#include <QObject>

#include "talbotmatrix.h"

class Experiment : public QObject
{
    Q_OBJECT

public:
    explicit Experiment(QObject *parent = nullptr);

    QImage &getTalbotImage();

    int &getViewX();

    TalbotParams &getTalbotParams();

    bool isSet();

public slots:
    void setTalbotThings(const QImage &image_, int viewX_, const TalbotParams &talbotParams_);

    void setTalbotImage(const QImage &image_);

    void setViewX(int viewX_);

    void setTalbotParams(const TalbotParams &params);

private:
    QImage talbotImage;

    int talbotViewX;

    TalbotParams talbotParams;

    bool isSet_ = false;
};

#endif // EXPERIMENT_H
