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
#include <list>

class Drop;

class State
{
public:
    explicit State(int* buffer);

    // compare drop size
    bool operator ==(State& state);

    State* addWater(int x, int y);
    void getDropsSize(int *buffer);

private:
    void checkDrops();
    void checkBurst();
    bool isDropsEmpty();
    void addDrops(int x, int y);

private:
    static const Grid emptyGrids[36];
    Grid grids[36];
    std::list<Drop*> drops[4];
    int deep;
};

#endif // STATE_H
