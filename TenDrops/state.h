//
// Module			: state.h
// Author			: bss
// Project			: TenDrops
// State			:
// Creation Date	: 2013-10-13
// Last Modification: 2013-10-13
// Description		: State in search.
//

#ifndef STATE_H
#define STATE_H

#include "grid.h"
#include <QList>

class Drop;

class State
{
public:
    explicit State(int* buffer);

    // compare drop size
    bool operator ==(State& state);

    State* addWater(int x, int y);
    void getDropsSize(int *buffer);
    bool isClear();

    State* getPrev();
    int getX();
    int getY();

private:
    void checkDrops();
    void checkBurst();
    bool isDropsEmpty();
    void addDrops(int x, int y);

private:
    Grid grids[36];
    QList<Drop*> drops[4];
    State* prev;
    int deep;
    int x, y;
};

#endif // STATE_H
