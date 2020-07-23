#ifndef MYPROCESSER_H
#define MYPROCESSER_H

#include "imageprocesser.h"
#include <QPainter>

struct MyParams
{
    int count;
};

class MyProcesser : public ImageProcesser
{
public:
    MyProcesser();
    void process(QImage &image) override;
    void updateParams(MyParams params);
private:
    MyParams params_;
};

#endif // MYPROCESSER_H
