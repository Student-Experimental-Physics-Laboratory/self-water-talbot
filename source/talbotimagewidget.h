#ifndef TALBOT_IMAGEWIDGET_H
#define TALBOT_IMAGEWIDGET_H

#include "imagewidget.h"
#include "imageprocesser.h"
#include "chartwidget.h"

#include <QMouseEvent>

#include <talbotmatrix.h>

using namespace std;

class TalbotImageProcesser : public ImageProcesser
{
public:
    TalbotImageProcesser() = default;

    void process(QImage &image) override;
    void updateTalbotParams(const TalbotParams &newParams);
private:
    TalbotMatrix ohThisIsTalbot;
};

class TalbotImageWidget : public ImageWidget
{
    Q_OBJECT
public:
    explicit TalbotImageWidget(QWidget *parent = nullptr);
    void reprocess() override;

    void connectChart(ChartWidget *widget);
    void drawChart();

    void updateTalbotParams(const TalbotParams &newParams);

public slots:
    void setViewX(int viewX_);
    void setImage(QImage &image_);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
private:
    // QImage in parent class
    vector<double> getGraph();
    ChartWidget *talbotChart;
    TalbotImageProcesser processer;
    int viewX;
};

#endif // IMAGEWIDGET_H
