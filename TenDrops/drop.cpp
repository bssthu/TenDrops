//
// Module			: drop.cpp
// Author			: bss
// Project			: TenDrops
// State			:
// Creation Date	: 2013-10-09
// Last Modification: 2013-10-10
// Description		:
//

#include "drop.h"
#include <QPainter>

const float Drop::ROT[] =
{
    0.0f,
    180.0f,
    -90.0f,
    90.0f
};

Drop::Drop(DropFrom dropFrom, int x, int y)
    : QObject(nullptr)
    , QGraphicsItem()
    , dropFrom(dropFrom)
    , img("://Data//Textures//drop.png")
    , rect(GRID_SX + GRID_DX * x - WIDTH * 0.5f, GRID_SY + GRID_DY * y - WIDTH * 0.5f, WIDTH, WIDTH)
    , idX(x)
    , idY(y)
    , isDead_(false)
    , isNew_(true)
{
    setTransformOriginPoint(rect.center());
    setRotation(ROT[(int)dropFrom]);
}

QRectF Drop::boundingRect() const
{
    return rect;
}

void Drop::paint(QPainter *painter, const QStyleOptionGraphicsItem */*option*/, QWidget */*widget*/)
{
    QRectF r = rect;
    r.adjust(0, 15, 0, 15);
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
    static const int dy[] = { 1, -1, 0, 0 };
    idX += dx[(int)dropFrom];
    idY += dy[(int)dropFrom];
    if (idX < 0 || idX >= 6 || idY < 0 || idY >= 6)
    {
        isDead_ = true;
        return;
    }

    resetTransform();
    rect.setRect(GRID_SX + GRID_DX * idX - WIDTH * 0.5f, GRID_SY + GRID_DY * idY - WIDTH * 0.5f, WIDTH, WIDTH);
    setTransformOriginPoint(rect.center());
    setRotation(ROT[(int)dropFrom]);
}

bool Drop::isDead()
{
    return isDead_;
}
