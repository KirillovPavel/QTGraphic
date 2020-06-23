#ifndef ARROW_H
#define ARROW_H

#include <QGraphicsItem>
#include <QPen>

enum Axis_type{
    X_axis,
    Y_axis
};

class AxisItem{
public:
    AxisItem(qint32 e_x, qint32 e_y, Axis_type axisType = X_axis);
    QGraphicsItemGroup* getItem();          //return axis
    void resize(qint32 e_x, qint32 e_y);    //resizing the axis connected with window resizing

private:
    QGraphicsPolygonItem* arrow;
    QGraphicsLineItem* line;
    QGraphicsItemGroup* axis;
    const qint32 init_x;            //for moving the arrow
    const qint32 init_y;
};

#endif // ARROW_H
