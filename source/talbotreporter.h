#ifndef TALBOTREPORTER_H
#define TALBOTREPORTER_H

#include <QImage>
#include <QFileDialog>
#include <QPainter>

#include "talbotmatrix.h"

class TalbotReporter
{
public:
    TalbotReporter(const QImage &talbotImage,
                   const QImage &chartImage,
                   const QImage &hrulerImage,
                   const QImage &vrulerImage,
                   const QImage &crulerImage,
                   const TalbotParams &talbotParams);

    void safeToFile(QString filePath);

protected:
    void drawResImage();

    QImage resImage;

    QImage talbotImage_;
    QImage chartImage_;
    QImage hrulerImage_;
    QImage vrulerImage_;
    QImage crulerImage_;

    TalbotParams talbotParams_;
    int paramsWidth_;
};

#endif // TALBOTREPORTER_H
