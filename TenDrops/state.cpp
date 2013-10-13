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

State::State(int *buffer)
    : grids()
    , drops()
    , prev(nullptr)
    , deep(0)
    , x(-1)
    , y(-1)
{
    memcpy_s(grids, sizeof(grids), buffer, sizeof(grids));
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
    newState->prev = this;
    newState->deep = deep + 1;
    newState->x = x;
    newState->y = y;
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

bool State::isClear()
{
    int buffer[36] = { 0 };
    return 0 == memcmp(grids, buffer, sizeof(grids));
}

State* State::getPrev()
{
    return prev;
}

int State::getX()
{
    return x;
}

int State::getY()
{
    return y;
}

void State::checkDrops()
{
    for (int i = 0; i < 4; i++)
    {
        for (QList<Drop*>::iterator it = drops[i].begin(); it != drops[i].end(); )
        {
            Drop* drop = *it;
            drop->step();
            if (drop->isDead())
            {
                it = drops[i].erase(it);
                SAFE_DELETE(drop);
            }
            else if (grids[drop->Drop::y() * 6 + drop->Drop::x()].canAcceptDrop())
            {
                grids[drop->Drop::y() * 6 + drop->Drop::x()].addDrop();
                it = drops[i].erase(it);
                SAFE_DELETE(drop);
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
