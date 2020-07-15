#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QImage>

class ImageWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ImageWidget(QWidget *parent = nullptr);

    void resizeEvent(QResizeEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
private:
    QImage image;
};

#endif // IMAGEWIDGET_H
