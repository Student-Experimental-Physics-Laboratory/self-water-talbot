#ifndef DRAW2DVECTOR_H
#define DRAW2DVECTOR_H

#include <QWidget>
#include <QPainter>
#include <QWidget>
#include <vector>
#include <exception>
#include <string>

class Draw2DVector : public QWidget
{
    Q_OBJECT
public:
    explicit Draw2DVector(QWidget *parent = nullptr);
    void setVector(std::vector<std::vector<unsigned int> > vec);
    void drawVector(std::vector<std::vector<unsigned int> > vec);
private:
    void paintEvent(QPaintEvent *event) override;
    std::vector<std::vector<unsigned int> > points;
};

#endif // DRAW2DVECTOR_H
