//
// Module			: drop.h
// Author			: bss
// Project			: TenDrops
// State			:
// Creation Date	: 2013-10-09
// Last Modification: 2013-10-10
// Description		: A flying drop.
//

#ifndef DROP_H
#define DROP_H

class Drop
{
public:
    enum class DropFrom
    {
        NORTH = 0,
        SOUTH = 1,
        WEST = 2,
        EAST = 3
    };

    Drop(DropFrom dropFrom, int x, int y);

    int x();
    int y();
    void step();

    bool isDead();

protected:
    DropFrom dropFrom;
    int idX, idY;
    bool isDead_;
    bool isNew_;
};

#endif // DROP_H
