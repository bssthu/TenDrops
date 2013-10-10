//
// Module			: grid.cpp
// Author			: bss
// Project			: TenDrops
// State			:
// Creation Date	: 2013-10-08
// Last Modification: 2013-10-09
// Description		:
//

#include "grid.h"
#include <qpainter.h>
#include <QMessageBox>

QImage Grid::img[] =
{
    QImage(),
    QImage("://Data//Textures//water1.png"),
    QImage("://Data//Textures//water2.png"),
    QImage("://Data//Textures//water3.png"),
    QImage("://Data//Textures//water4.png"),
};

Grid::Grid(int x, int y)
    : QObject(nullptr)
    , QGraphicsItem()
    , idX(x)
    , idY(y)
    , rect(GRID_SX + GRID_DX * x - WIDTH * 0.5f, GRID_SY + GRID_DY * y - WIDTH * 0.5f, WIDTH, WIDTH)
    , dropSize_(0)
{
}

QRectF Grid::boundingRect() const
{
    return rect;
}

void Grid::paint(QPainter *painter, const QStyleOptionGraphicsItem */*option*/, QWidget */*widget*/)
{
    painter->drawImage(boundingRect(), img[dropSize_]);
}

void Grid::setDropSize(int size)
{
    if (size < 0)
    {
        size = 0;
    }
    if (size > MAX_DROP_SIZE)
    {
        size = MAX_DROP_SIZE;
    }
    dropSize_ = size;
}

int Grid::dropSize()
{
    return dropSize_;
}

void Grid::addDrop()
{
    dropSize_++;
}

bool Grid::canAcceptDrop()
{
    return dropSize_ > 0 && dropSize_ <= MAX_DROP_SIZE;
}

// Ë®µÎ±¬Õ¨
bool Grid::checkBurst()
{
    if (dropSize_ > MAX_DROP_SIZE)
    {
        dropSize_ = 0;
        return true;
    }
    else
    {
        return false;
    }
}

int Grid::getCoordX(float x)
{
    int i = floor((x - (GRID_SX - Grid::WIDTH / 2)) / GRID_DX);
    if (x - (GRID_SX - Grid::WIDTH / 2) - i * GRID_DX > Grid::WIDTH
            || i < 0 || i >= 6)
    {
        return -1;
    }
    else
    {
        return i;
    }
}

int Grid::getCoordY(float y)
{
    int j = floor((y - (GRID_SY - Grid::WIDTH / 2)) / GRID_DY);
    if (y - (GRID_SY - Grid::WIDTH / 2) - j * GRID_DY > Grid::WIDTH
            || j < 0 || j >= 6)
    {
        return -1;
    }
    else
    {
        return j;
    }
}
