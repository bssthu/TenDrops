//
// Module			: drop.cpp
// Author			: bss
// Project			: TenDrops
// State			:
// Creation Date	: 2013-10-09
// Last Modification: 2013-10-09
// Description		:
//

#include "drop.h"
#include <QPainter>

Drop::Drop(DropFrom dropFrom, int x, int y)
    : QObject(nullptr)
    , QGraphicsItem()
    , dropFrom(dropFrom)
    , img("://Data//Textures//drop.png")
    , rect(GRID_SX + GRID_DX * x - WIDTH * 0.5f, GRID_SY + GRID_DY * y - WIDTH * 0.5f, WIDTH, WIDTH)
    , idX(x)
    , idY(y)
{
    setTransformOriginPoint(rect.center());
    setRotation(360.0 / 4.0 * (int)dropFrom);
}

QRectF Drop::boundingRect() const
{
    return rect;
}

void Drop::paint(QPainter *painter, const QStyleOptionGraphicsItem */*option*/, QWidget */*widget*/)
{
    QRectF r = rect;
    r.adjust(0, 30, 0, 30);
    painter->drawImage(r, img);
}

int Drop::x()
{
    return idX;
}

int Drop::y()
{
    return idY;
}

void Drop::step()
{
    static const int dx[] = { 0, 0, 1, -1 };
    static const int dy[] = { -1, 1, 0, 0 };
    idX += dx[(int)dropFrom];
    idY += dy[(int)dropFrom];
}
