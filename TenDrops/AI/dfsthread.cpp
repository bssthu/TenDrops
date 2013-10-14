//
// Module			: dfsthread.cpp
// Author			: bss
// Project			: TenDrops
// State			:
// Creation Date	: 2013-10-13
// Last Modification: 2013-10-14
// Description		:
//

#include "dfsthread.h"
#include <QTime>
#include "state.h"
#include "Macro.h"

DFSThread::DFSThread(State *state, int water, QObject *parent)
    : MyThread(water, parent)
{
    state->setWater(water);
    open.push_back(state);
}

void DFSThread::run()
{
    time->start();
    State* finalState = nullptr;
    do
    {
        finalState = traversal();
        if (open.size() == 0)
        {
            steps = 0;
            isSucceed = true;
            return;
        }
    } while (nullptr == finalState && !isExit);
    if (isExit)
    {
        deleteElements();
        return;
    }

    traceBackState(finalState);

    isSucceed = true;
    elapsedSec = (float)time->elapsed() / 1000.0f;
    deleteElements();
}

State* DFSThread::traversal()
{
    State* curState = open.last();
    open.pop_back();
    closed.push_back(curState);
    if (curState->getWater() <= 0)
    {
        return nullptr;
    }
    for (int x = 0; x < 6; ++x)
    {
        for (int y = 0; y < 6; ++y)
        {
            State* newState = curState->addWater(x, y);
            if (nullptr != newState)
            {
                if (newState->isClear())
                {
                    addToOpenList(newState);
                    return newState;
                }
                addToOpenList(newState);
            }
        }
    }
    return nullptr;
}

void DFSThread::addToOpenList(State* newState)
{
    for (QVector<State*>::iterator it = open.begin(); it != open.end(); )
    {
        State* state = *it;
        if (*state == *newState)
        {
            SAFE_DELETE(newState);
            return;
        }
        ++it;
    }
    for (QStack<State*>::iterator it = closed.begin(); it != closed.end(); )
    {
        State* state = *it;
        if (*state == *newState)
        {
            SAFE_DELETE(newState);
            return;
        }
        ++it;
    }
    open.push_back(newState);
}

QString DFSThread::getInfo()
{
    if (!isSucceed && !isExit)
    {
        openSize = open.size();
        closedSize = closed.size();
        elapsedSec = (float)time->elapsed() / 1000.0f;
    }
    QString str = QString("open=%1; closed=%2; elapsed=%3s").arg(openSize).arg(closedSize).arg(elapsedSec);
    if (0 == openSize && isSucceed)
    {
        str.append("; 已遍历所有情况，无解");
    }
    return str;
}
