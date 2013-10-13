//
// Module			: bfsthread.cpp
// Author			: bss
// Project			: TenDrops
// State			:
// Creation Date	: 2013-10-13
// Last Modification: 2013-10-13
// Description		:
//

#include "bfsthread.h"
#include <QStack>
#include "state.h"
#include "Macro.h"

BFSThread::BFSThread(State* state, int water, QObject *parent)
    : MyThread(water, parent)
    , open()
    , closed()
    , deep(0)
{
    open.push_back(state);
}

void BFSThread::run()
{
    State* finalState = nullptr;
    do
    {
        finalState = bfs_traversal();
        if (open.size() == 0)
        {
            steps = 0;
            isSucceed = true;
            return;
        }
        ++deep;
    } while (nullptr == finalState && !isExit);
    if (isExit)
    {
        deleteElements();
        return;
    }

    QStack<State*> stack;
    do
    {
        stack.push(finalState);
        finalState = finalState->getPrev();
    } while (nullptr != finalState);

    opers = new Point[stack.size()];
    steps = stack.size() - 1;  // Skip first state
    finalState = stack.pop();
    for (int i = 0; i < steps; ++i)
    {
        finalState = stack.pop();
        opers[i].x = finalState->getX();
        opers[i].y = finalState->getY();
    }

    isSucceed = true;
    deleteElements();
}

State* BFSThread::bfs_traversal()
{
    int i = 0;
    int iEnd = open.size();
    for (QLinkedList<State*>::iterator it = open.begin(); i < iEnd; ++i)
    {
        if (isExit)
        {
            return nullptr;
        }
        State* curState = *it;
        for (int x = 0; x < 6; ++x)
        {
            for (int y = 0; y < 6; ++y)
            {
                State* newState = curState->addWater(x, y);
                if (nullptr != newState)
                {
                    if (newState->isClear())
                    {
                        bfs_addToOpenList(newState);
                        return newState;
                    }
                    bfs_addToOpenList(newState);
                }
            }
        }
        it = open.erase(it);
        closed.push_back(curState);
    }
    return nullptr;
}

void BFSThread::bfs_addToOpenList(State* newState)
{
    for (QLinkedList<State*>::iterator it = open.begin(); it != open.end(); ++it)
    {
        if (*newState == *(*it))
        {
            SAFE_DELETE(newState);
            return;
        }
    }
    for (QLinkedList<State*>::iterator it = closed.begin(); it != closed.end(); ++it)
    {
        if (*newState == *(*it))
        {
            SAFE_DELETE(newState);
            return;
        }
    }
    open.push_back(newState);
}

void BFSThread::deleteElements()
{
    openSize = open.size();
    for (QLinkedList<State*>::iterator it = open.begin(); it != open.end(); )
    {
        State* state = *it;
        ++it;
        SAFE_DELETE(state);
    }
    open.clear();
    closedSize = closed.size();
    for (QLinkedList<State*>::iterator it = closed.begin(); it != closed.end(); )
    {
        State* state = *it;
        ++it;
        SAFE_DELETE(state);
    }
    closed.clear();
}

QString BFSThread::getInfo()
{
    if (!isSucceed && !isExit)
    {
        openSize = open.size();
        closedSize = closed.size();
    }
    return QString("open=%1; closed=%2; deep=%3").arg(openSize).arg(closedSize).arg(deep);
}
