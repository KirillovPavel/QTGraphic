#include "axis.h"

AxisItem::AxisItem(qint32 e_x, qint32 e_y, Axis_type axisType):
    init_x(e_x),
    init_y(e_y)
{
    QColor color(20, 140, 200);
    QPolygon polygon;
    if(axisType == Y_axis)
        polygon << QPoint(e_x, e_y) << QPoint(e_x - 7, e_y - 20) << QPoint(e_x + 7, e_y - 20);
    else
        polygon << QPoint(e_x, e_y) << QPoint(e_x - 20, e_y - 7) << QPoint(e_x - 20, e_y + 7);
    arrow = new QGraphicsPolygonItem(polygon);
    arrow->setPen(color);
    arrow->setBrush(color);

    line = new QGraphicsLineItem(0, 0, e_x, e_y);
    line->setPen(color);

    axis = new QGraphicsItemGroup();
    axis->addToGroup(line);
    axis->addToGroup(arrow);
}

QGraphicsItemGroup* AxisItem::getItem(){
    return axis;
}

void AxisItem::resize(qint32 e_x, qint32 e_y){
    line->setLine(QLine(0, 0, e_x, e_y));
    arrow->setPos(e_x - init_x, e_y - init_y);
   // axis->setPos(100, 100);
}
