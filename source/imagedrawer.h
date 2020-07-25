#ifndef IMAGEDRAWER_H
#define IMAGEDRAWER_H

#include <QImage>

class ImageDrawer
{
public:
    ImageDrawer();

    virtual void draw(QImage &) = 0;
};

#endif // IMAGEDRAWER_H
