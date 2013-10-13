//
// Module			: dropgraphics.h
// Author			: bss
// Project			: TenDrops
// State			:
// Creation Date	: 2013-10-10
// Last Modification: 2013-10-13
// Description		: Graphics of drop.
//

#ifndef DROPGRAPHICS_H
#define DROPGRAPHICS_H

#include "drop.h"
#include <QGraphicsItem>

class DropGraphics : public Drop, public QGraphicsItem
{
public:
    explicit DropGraphics(DropFrom dropFrom, int x, int y);
    ~DropGraphics() { }

    QRectF boundingRect() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void step();
    void move(float percent);

private:
    static QImage img;
    static const int WIDTH = 48;
    static const int GRID_SX = 50;
    static const int GRID_SY = 40;
    static const int GRID_DX = 54;
    static const int GRID_DY = 54;
    static const float ROT[];

    QRectF rect;
    float movePercent;
};

#endif // DROPGRAPHICS_H
