//
// Module			: ai.cpp
// Author			: bss
// Project			: TenDrops
// State			:
// Creation Date	: 2013-10-13
// Last Modification: 2013-10-13
// Description		:
//

#include "ai.h"
#include <QStack>
#include "state.h"

QLinkedList<State*> AI::open;
QLinkedList<State*> AI::closed;

void AI::bfs(State *state, Point **op, int *steps)
{
    open.clear();
    closed.clear();

    open.push_back(state);
    State* finalState = nullptr;
    do
    {
        finalState = bfs_traversal();
        if (open.size() == 0)
        {
            *steps = 0;
            return;
        }
    } while (nullptr == finalState);

    QStack<State*> stack;
    do
    {
        stack.push(finalState);
        finalState = finalState->getPrev();
    } while (nullptr != finalState);

    *op = new Point[stack.size()];
    *steps = stack.size() - 1;  // Skip first state
    finalState = stack.pop();
    for (int i = 0; i < *steps; ++i)
    {
        finalState = stack.pop();
        (*op)[i].x = finalState->getX();
        (*op)[i].y = finalState->getY();
    }
}

State* AI::bfs_traversal()
{
    int i = 0;
    int iEnd = open.size();
    for (QLinkedList<State*>::iterator it = open.begin(); i < iEnd; ++i)
    {
        State* state = *it;
        for (int x = 0; x < 6; ++x)
        {
            for (int y = 0; y < 6; ++y)
            {
                State* newState = state->addWater(x, y);
                if (nullptr != newState)
                {
                    bfs_addToOpenList(newState);
                    if (newState->isClear())
                    {
                        return newState;
                    }
                }
            }
        }
        it = open.erase(it);
        closed.push_back(state);
    }
    return nullptr;
}

void AI::bfs_addToOpenList(State* newState)
{
    //State* state;
    for (QLinkedList<State*>::iterator it = open.begin(); it != open.end(); ++it)
    {
        if (*newState == *(*it))
        {
            return;
        }
    }
    for (QLinkedList<State*>::iterator it = closed.begin(); it != closed.end(); ++it)
    {
        if (*newState == *(*it))
        {
            return;
        }
    }
    open.push_back(newState);
}
