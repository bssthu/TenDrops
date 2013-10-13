//
// Module			: grid.h
// Author			: bss
// Project			: TenDrops
// State			:
// Creation Date	: 2013-10-08
// Last Modification: 2013-10-10
// Description		: A grid in board. Can contain a drop of water.
//

#ifndef GRID_H
#define GRID_H

// 一格，静止的水珠
class Grid
{
public:
    explicit Grid(int x, int y);

    void setDropSize(int size);
    int dropSize();
    // 加一滴水
    void addDrop();
    bool canAcceptDrop();
    // 水滴爆炸
    bool checkBurst();

public:
    static const int WIDTH = 48;
    static const int MAX_DROP_SIZE = 4;
    static const int GRID_SX = 50;
    static const int GRID_SY = 40;
    static const int GRID_DX = 54;
    static const int GRID_DY = 54;

protected:
    int idX, idY;
    int dropSize_;
};

#endif // GRID_H
