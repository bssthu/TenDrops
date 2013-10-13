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
class State;

unsigned int qHash(State key);

class State
{
public:
    explicit State(int* buffer);

    // compare drop size
    bool operator ==(State& state);
    // sort by f
    bool operator <(State& state);

    void setWater(int dropsLeft);
    int getWater();
    State* addWater(int x, int y);
    void getDropsSize(int *buffer);
    bool isClear();

    State* getPrev();
    int getX();
    int getY();

    int getG();
    int getH();
    int getF();

private:
    void checkDrops();
    void checkBurst();
    bool isDropsEmpty();
    void addDrops(int x, int y);

private:
    Grid grids[36];
    QList<Drop*> drops[4];
    State* prev;
    int water;
    int combo;
    int deep;
    int x, y;
};

#endif // STATE_H
