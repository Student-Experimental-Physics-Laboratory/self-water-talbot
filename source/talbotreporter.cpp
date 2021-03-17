#include "talbotreporter.h"

#include <QDebug>

TalbotReporter::TalbotReporter(const QImage &talbotImage,
                               const QImage &chartImage,
                               const QImage &hrulerImage,
                               const QImage &vrulerImage,
                               const QImage &crulerImage,
                               const TalbotParams &talbotParams) :
    talbotImage_(talbotImage),
    chartImage_(chartImage),
    hrulerImage_(hrulerImage),
    vrulerImage_(vrulerImage),
    crulerImage_(crulerImage),
    talbotParams_(talbotParams),
    paramsWidth_(250)
{
    int resWidth = vrulerImage.width() + talbotImage.width() + chartImage.width() + paramsWidth_;
    int resHeight = talbotImage.height() + hrulerImage.height();
    resImage = QImage(resWidth, resHeight, QImage::Format_RGB32);
}

void TalbotReporter::safeToFile(QString filePath)
{
    drawResImage();
    resImage.save(filePath + ".png", "png");
}

void TalbotReporter::drawResImage()
{
    QRect vrulerTargetRect(0, 0, vrulerImage_.width(), vrulerImage_.height());
    QRect hrulerTargetRect(vrulerTargetRect.width(), vrulerTargetRect.height(),
                           hrulerImage_.width(), hrulerImage_.height());
    QRect talbotTargetRect(vrulerTargetRect.width(), 0,
                           talbotImage_.width(), talbotImage_.height());
    QRect chartTargetRect(vrulerTargetRect.width() + talbotTargetRect.width(), 0,
                          chartImage_.width(), chartImage_.height());
    QRect crulerTargeRect(vrulerTargetRect.width() + hrulerTargetRect.width(),
                          vrulerTargetRect.height(),
                          crulerImage_.width(), crulerImage_.height());

    QPainter p(&resImage);

    resImage.fill(Qt::white);

    p.drawImage(vrulerTargetRect, vrulerImage_, vrulerImage_.rect());
    p.drawImage(hrulerTargetRect, hrulerImage_, hrulerImage_.rect());
    p.drawImage(talbotTargetRect, talbotImage_, talbotImage_.rect());
    p.drawImage(chartTargetRect, chartImage_, chartImage_.rect());
    p.drawImage(crulerTargeRect, crulerImage_, crulerImage_.rect());

    auto fontYStart = 20;
    auto updateFontY = [&fontYStart] () { fontYStart += 30; };


    p.drawText(resImage.width() - paramsWidth_ + 1, fontYStart,
               QString("Отжажение от бортиков: %1").arg(talbotParams_.reflectible ? "есть" : "нет"));
    updateFontY();

    p.drawText(resImage.width() - paramsWidth_ + 1, fontYStart,
               QString("Количество источников: %1").arg(talbotParams_.n_sources));
    updateFontY();
    p.drawText(resImage.width() - paramsWidth_ + 1, fontYStart,
               QString("Фаза волны: %1").arg(talbotParams_.phase));
    updateFontY();
    p.drawText(resImage.width() - paramsWidth_ + 1, fontYStart,
               QString("Длина волны: %1").arg(talbotParams_.wave_len));
    updateFontY();
    p.drawText(resImage.width() - paramsWidth_ + 1, fontYStart,
               QString("Крутость наклона волны: %1").arg(talbotParams_.wave_slope));
    updateFontY();
    p.drawText(resImage.width() - paramsWidth_ + 1, fontYStart,
               QString("Коэффициент вязкости: %1").arg(talbotParams_.viscosity));
}
