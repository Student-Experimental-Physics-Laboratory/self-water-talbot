#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include <QWidget>
#include <QImage>
#include <QPainter>

class ImageWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ImageWidget(QWidget *parent = nullptr);

    virtual void reprocess();

protected:
   QImage image;

   void resizeEvent(QResizeEvent *event) override;

   virtual void paintEvent(QPaintEvent *event) override;

private:
   void resizeImage(QImage *image, const QSize &size);
};

#endif // IMAGEWIDGET_H
