//
// Module			: gridgraphics.h
// Author			: bss
// Project			: TenDrops
// State			:
// Creation Date	: 2013-10-10
// Last Modification: 2013-10-10
// Description		: A grid in board. Can contain a drop of water.
//

#ifndef GRIDGRAPHICS_H
#define GRIDGRAPHICS_H

#include "grid.h"
#include <QGraphicsItem>

class GridGraphics : public Grid , public QGraphicsItem
{
public:
    GridGraphics(int x, int y);

    QRectF boundingRect() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    static int getCoordX(float x);
    static int getCoordY(float y);

private:
    static QImage img[];
    QRectF rect;
};

#endif // GRIDGRAPHICS_H