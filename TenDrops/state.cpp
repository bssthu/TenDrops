//
// Module			: state.cpp
// Author			: bss
// Project			: TenDrops
// State			:
// Creation Date	: 2013-10-13
// Last Modification: 2013-10-14
// Description		:
//

#include "state.h"
#include <memory.h>
#include "Macro.h"
#include <drop.h>

unsigned int qHash(State* key)
{
    // Robert Sedgwicks, Algorithms in C
    unsigned int b = 378551;
    unsigned int a = 63689;
    unsigned int hash = 0;
    int buffer[36];
    key->getDropsSize(buffer);
    for (int i = 0; i < 36; ++i)
    {
        hash = hash * a + buffer[i];
        a = a * b;
    }
    return hash;
}

bool compLess(State *lhs, State* rhs)
{
    return *lhs < *rhs;
}

State::State(char *buffer)
    : grids()
    , drops(nullptr)
    , prev(nullptr)
    , water(0)
    , combo(0)
    , x(-1)
    , y(-1)
    , h(0)
{
    memcpy(grids, buffer, sizeof(grids));
}

void State::updateTo(State* state)
{
    prev = state->prev;
    water = state->water;
    x = state->x;
    y = state->y;
}

bool State::operator ==(State& state)
{
    return 0 == memcmp(grids, state.grids, sizeof(grids));
}

bool State::operator <(State& state)
{
    return getF() < state.getF();
}

void State::setWater(int dropsLeft)
{
    water = dropsLeft;
}

int State::getWater()
{
    return water;
}

State* State::addWater(int x, int y)
{
    int index = y * 6 + x;
    if (!grids[index].canAcceptDrop())
    {
        return nullptr;
    }

    State* newState = new State(*this);
    newState->drops = new QList<Drop*>[4];
    //newState->water = water - 1;
    newState->water = 1;
    newState->combo = 0;
    newState->prev = this;
    newState->x = x;
    newState->y = y;
    newState->grids[index].addDrop();
    do
    {
        newState->checkDrops();
        newState->checkBurst();
    } while (!newState->isDropsEmpty());
    newState->combo = 0;
    SAFE_DELETE_ARRAY(newState->drops);
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

int State::getG()
{
    int g = water;
    State* state = this;
    while ((state = state->prev) != nullptr)
    {
        g += state->water;
    }
    return g;
}

#ifndef H_NEAR_DROP
#define H_NEAR_DROP(w)  \
    if (w > 0)  \
    {  \
        lineEmpty = false;  \
    }  \
    if (w < 3) \
    { \
        h += 1; \
        break; \
    } \
    else if (4 == w) \
    { \
        h -= 1; \
    }
#endif

void State::calcH()
{
    h = 0;
    for (int x = 0; x < 6; ++x)
    {
        for (int y = 0; y < 6; ++y)
        {
            int index = y * 6 + x;
            int w = grids[index].dropSize();
            if (w > 0)
            {
                h += 5 - w;
                bool lineEmpty = true;
                for (int x1 = x - 1; x1 >= 0; --x1)
                {
                    w = grids[y * 6 + x1].dropSize();
                    H_NEAR_DROP(w);
                }
                for (int x1 = x + 1; x1 < 6; ++x1)
                {
                    w = grids[y * 6 + x1].dropSize();
                    H_NEAR_DROP(w);
                }
                for (int y1 = y - 1; y1 >= 0; --y1)
                {
                    w = grids[y1 * 6 + x].dropSize();
                    H_NEAR_DROP(w);
                }
                for (int y1 = y + 1; y1 < 6; ++y1)
                {
                    w = grids[y1 * 6 + x].dropSize();
                    H_NEAR_DROP(w);
                }
                if (lineEmpty)
                {
                    h += 1;
                }
            }
        }
    }
}

int State::getH()
{
    return h;
}

int State::getF()
{
    return getG() + getH();
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
                ++combo;
                if (combo >= 3)
                {
                    combo = 0;
                    ++water;
                }
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
