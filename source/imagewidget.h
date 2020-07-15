#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QImage>
#include <QMouseEvent>

class TalbotImageWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TalbotImageWidget(QWidget *parent = nullptr);

    void resizeEvent(QResizeEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

    void mousePressEvent(QMouseEvent *event) override;

private:
    QImage image;
    int viewX;
};

#endif // IMAGEWIDGET_H
