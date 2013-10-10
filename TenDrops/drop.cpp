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

Drop::Drop(DropFrom dropFrom, int x, int y)
    : dropFrom(dropFrom)
    , idX(x)
    , idY(y)
    , isDead_(false)
    , isNew_(true)
{
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
}

bool Drop::isDead()
{
    return isDead_;
}
