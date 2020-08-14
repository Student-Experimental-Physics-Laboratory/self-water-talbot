#ifndef TALBOT_IMAGEWIDGET_H
#define TALBOT_IMAGEWIDGET_H

#include "imagewidget.h"
#include "imageprocesser.h"
#include <QMouseEvent>

class TalbotImageProcesser : public ImageProcesser
{
public:
    TalbotImageProcesser() = default;

    void process(QImage &image) override;
};

class TalbotImageWidget : public ImageWidget
{
    Q_OBJECT
public:
    explicit TalbotImageWidget(QWidget *parent = nullptr);
    void reprocess() override;

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
private:
    TalbotImageProcesser processer;
    int viewX;
};

#endif // IMAGEWIDGET_H
