#ifndef TALBOT_IMAGEWIDGET_H
#define TALBOT_IMAGEWIDGET_H

#include "imagewidget.h"
#include "imageprocesser.h"

#include <QMouseEvent>

#include "chartwidget.h"
#include "talbotmatrix.h"
#include "experiment.h"

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

    QImage getImage() override;

signals:
    void talbotParamsUpdated(const TalbotParams &params);

public slots:
    void connectExperiment(Experiment *experiment);

    void setViewX(const int viewX_);
    void setImage(const QImage &image_);
    void updateTalbotParams(const TalbotParams &newParams);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

    void drawViewX(QPainter &p);
private:
    // QImage in parent class
    TalbotImageProcesser processer;
    int viewX;

    Experiment *currentExperiment;

    ChartWidget *talbotChart;
    vector<double> getGraph();
};

#endif // IMAGEWIDGET_H
