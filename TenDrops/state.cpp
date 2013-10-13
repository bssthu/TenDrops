//
// Module			: state.cpp
// Author			: bss
// Project			: TenDrops
// State			:
// Creation Date	: 2013-10-13
// Last Modification: 2013-10-13
// Description		:
//

#include "state.h"
#include <memory.h>
#include "Macro.h"
#include <drop.h>

const Grid State::emptyGrids[36] =
{
    Grid(0, 0), Grid(0, 1), Grid(0, 2), Grid(0, 3), Grid(0, 4), Grid(0, 5),
    Grid(1, 0), Grid(1, 1), Grid(1, 2), Grid(1, 3), Grid(1, 4), Grid(1, 5),
    Grid(2, 0), Grid(2, 1), Grid(2, 2), Grid(2, 3), Grid(2, 4), Grid(2, 5),
    Grid(3, 0), Grid(3, 1), Grid(3, 2), Grid(3, 3), Grid(3, 4), Grid(3, 5),
    Grid(4, 0), Grid(4, 1), Grid(4, 2), Grid(4, 3), Grid(4, 4), Grid(4, 5),
    Grid(5, 0), Grid(5, 1), Grid(5, 2), Grid(5, 3), Grid(5, 4), Grid(5, 5),
};

State::State(int *buffer)
    : grids(emptyGrids)
    , drops()
{
    for (int x = 0; x < 6; x++)
    {
        for (int y = 0; y < 6; y++)
        {
            int index = y * 6 + x;
            grids[index].setDropSize(buffer[index]);
        }
    }
}

bool State::operator ==(State& state)
{
    return 0 == memcmp(grids, state.grids, sizeof(grids));
}

State* State::addWater(int x, int y)
{
    int index = y * 6 + x;
    if (!grids[index].canAcceptDrop())
    {
        return nullptr;
    }

    State* newState = new State(*this);
    newState->grids[index].addDrop();
    do
    {
        newState->checkDrops();
        newState->checkBurst();
    } while (!newState->isDropsEmpty());
    return newState;
}

void State::getDropsSize(int* buffer)
{
    for (int x = 0; x < 6; x++)
    {
        for (int y = 0; y < 6; y++)
        {
            int index = y * 6 + x;
            buffer[index] = grids[index].dropSize();
        }
    }
}

void State::checkDrops()
{
    for (int i = 0; i < 4; i++)
    {
        for (std::list<Drop*>::iterator it = drops[i].begin(); it != drops[i].end(); )
        {
            Drop* drop = *it;
            drop->step();
            if (drop->isDead())
            {
                it = drops[i].erase(it);
            }
            else if (grids[drop->Drop::y() * 6 + drop->Drop::x()].canAcceptDrop())
            {
                grids[drop->Drop::y() * 6 + drop->Drop::x()].addDrop();
                it = drops[i].erase(it);
            }
            else
            {
                ++it;
            }
        }
    }
}

void State::checkBurst()
{
    for (int x = 0; x < 6; x++)
    {
        for (int y = 0; y < 6; y++)
        {
            if (grids[y * 6 + x].checkBurst())
            {
                addDrops(x, y);
            }
        }
    }
}

void State::addDrops(int x, int y)
{
    for (int i = 0; i < 4; i++)
    {
        Drop* drop = new Drop((Drop::DropFrom)i, x, y);
        drops[i].push_back(drop);
    }
}

bool State::isDropsEmpty()
{
    bool isEmpty = true;
    for (int i = 0; i < 4; i++)
    {
        isEmpty &= drops[i].empty();
    }
    return isEmpty;
}
