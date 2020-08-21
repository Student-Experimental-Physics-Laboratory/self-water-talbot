#ifndef EXPERIMENT_H
#define EXPERIMENT_H

#include "talbotmatrix.h"

class Experiment
{
public:
    Experiment();
private:
    QImage talbotImage;
    QImage chartImage;

    int talbotViewX;

    TalbotParams talbotParams;
};

#endif // EXPERIMENT_H
