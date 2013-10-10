//
// Module			: grid.cpp
// Author			: bss
// Project			: TenDrops
// State			:
// Creation Date	: 2013-10-08
// Last Modification: 2013-10-10
// Description		:
//

#include "grid.h"

Grid::Grid(int x, int y)
    : idX(x)
    , idY(y)
    , dropSize_(0)
{
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

// ˮ�α�ը
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
