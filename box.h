#ifndef BOX_H
#define BOX_H
#include <QGraphicsItem>
struct box
{
    int _posX;
    int _posY;
    int _size;
    bool _move;
    int _color;
    QGraphicsRectItem *item;
};

#endif // BOX_H
