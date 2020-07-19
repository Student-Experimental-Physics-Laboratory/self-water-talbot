#ifndef TALBOT_IMAGEWIDGET_H
#define TALBOT_IMAGEWIDGET_H

#include "imagewidget.h"
#include <QMouseEvent>


class TalbotImageWidget : public ImageWidget
{
    Q_OBJECT
public:
    explicit TalbotImageWidget(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;

    void mousePressEvent(QMouseEvent *event) override;

private:
    int viewX;
};

#endif // IMAGEWIDGET_H
