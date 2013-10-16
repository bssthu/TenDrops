//
// Module			: dropgraphics.cpp
// Author			: bss
// Project			: TenDrops
// State			:
// Creation Date	: 2013-10-10
// Last Modification: 2013-10-16
// Description		: Graphics of drop.
//

#include "dropgraphics.h"
#include <QPainter>

QImage DropGraphics::img;

const float DropGraphics::ROT[] =
{
    0.0f,
    180.0f,
    -90.0f,
    90.0f
};

DropGraphics::DropGraphics(DropFrom dropFrom, int x, int y)
    : Drop(dropFrom, x, y)
    , QGraphicsItem()
    , rect(GRID_SX + GRID_DX * x - WIDTH * 0.5f, GRID_SY + GRID_DY * y - WIDTH * 0.5f, WIDTH, WIDTH)
    , movePercent(0.0f)
{
    setTransformOriginPoint(rect.center());
    setRotation(ROT[(int)dropFrom]);
}


QRectF DropGraphics::boundingRect() const
{
    return QRectF(GRID_SX, GRID_SY, GRID_DX * 6, GRID_DY * 6);
}

void DropGraphics::paint(QPainter *painter, const QStyleOptionGraphicsItem */*option*/, QWidget */*widget*/)
{
    QRectF r = rect;
    r.adjust(0, movePercent * GRID_DX, 0, movePercent * GRID_DX);
    painter->drawImage(r, img);
}

void DropGraphics::step()
{
    Drop::step();

    movePercent = 0.0f;
    resetTransform();
    rect.setRect(GRID_SX + GRID_DX * idX - WIDTH * 0.5f, GRID_SY + GRID_DY * idY - WIDTH * 0.5f, WIDTH, WIDTH);
    setTransformOriginPoint(rect.center());
    setRotation(ROT[(int)dropFrom]);
}

void DropGraphics::move(float percent)
{
    movePercent += percent;
}

void DropGraphics::initImg()
{
    img.load("://Data//Textures//drop.png");
}
