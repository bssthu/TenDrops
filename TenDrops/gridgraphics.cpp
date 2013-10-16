//
// Module			: gridgraphics.cpp
// Author			: bss
// Project			: TenDrops
// State			:
// Creation Date	: 2013-10-10
// Last Modification: 2013-10-16
// Description		:
//

#include "gridgraphics.h"
#include <qpainter.h>

QImage GridGraphics::img[5];

GridGraphics::GridGraphics(int x, int y)
    : Grid()
    , QGraphicsItem()
    , rect(GRID_SX + GRID_DX * x - WIDTH * 0.5f, GRID_SY + GRID_DY * y - WIDTH * 0.5f, WIDTH, WIDTH)
{
}

QRectF GridGraphics::boundingRect() const
{
    return rect;
}

void GridGraphics::paint(QPainter *painter, const QStyleOptionGraphicsItem */*option*/, QWidget */*widget*/)
{
    painter->drawImage(boundingRect(), img[(int)dropSize_]);
}

void GridGraphics::initImg()
{
    for (int i = 1; i <= 4; ++i)
    {
        img[i].load(QString("://Data//Textures//water%1.png").arg(i));
    }
}

int GridGraphics::getCoordX(float x)
{
    int i = floor((x - (GRID_SX - WIDTH / 2)) / GRID_DX);
    if (x - (GRID_SX - WIDTH / 2) - i * GRID_DX > WIDTH
            || i < 0 || i >= 6)
    {
        return -1;
    }
    else
    {
        return i;
    }
}

int GridGraphics::getCoordY(float y)
{
    int j = floor((y - (GRID_SY - WIDTH / 2)) / GRID_DY);
    if (y - (GRID_SY - WIDTH / 2) - j * GRID_DY > WIDTH
            || j < 0 || j >= 6)
    {
        return -1;
    }
    else
    {
        return j;
    }
}
