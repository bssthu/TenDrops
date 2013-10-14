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
    , open()
    , closed()
{
    state->calcH();
    open.push_back(state);
}

void DFSThread::run()
{
    time->start();
    State* finalState = nullptr;
    for (deep = water; deep <= water && nullptr == finalState; ++deep)
    {
        closedToOpen();
        do
        {
            finalState = traversal();
            if (open.size() == 0)
            {
                steps = 0;
                break;
            }
            if (open.size() + closed.size() > 10000000)
            {
                isExit = true;
                isOutOfMemory = true;
                deleteElements();
                return;
            }
        } while (nullptr == finalState && !isExit);

        if (isExit)
        {
            deleteElements();
            return;
        }
    }
    if (nullptr == finalState)
    {
        isSucceed = true;
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
    std::list<State*>::iterator itMin = open.begin();
    for (std::list<State*>::iterator it = open.begin(); it != open.end(); ++it)
    {
        if (*itMin < *it)
        {
            itMin = it;
        }
    }
    State* curState = *itMin;
    open.erase(itMin);
    closed.insert(curState);
    // 水不能为负
    if (curState->getG() >= deep)
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
    for (std::list<State*>::iterator it = open.begin(); it != open.end(); )
    {
        State* state = *it;
        if (*state == *newState)
        {
            if (state->getG() > newState->getG())
            {
                state->updateTo(newState);
            }
            SAFE_DELETE(newState);
            return;
        }
        ++it;
    }
    if (closed.contains(newState))
    {
        State* state = *closed.find(newState);
        if (state->getG() > newState->getG())
        {
            state->updateTo(newState);
            closed.remove(state);
            open.push_back(state);
        }
        SAFE_DELETE(newState);
        return;
    }
    newState->calcH();
    open.push_back(newState);
}

void DFSThread::closedToOpen()
{
    for (QSet<State*>::iterator it = closed.begin(); it != closed.end(); )
    {
        State* state = *it;
        ++it;
        open.push_back(state);
    }
    closed.clear();
}

void DFSThread::deleteElements()
{
    openSize = open.size();
    for (std::list<State*>::iterator it = open.begin(); it != open.end(); )
    {
        State* state = *it;
        ++it;
        SAFE_DELETE(state);
    }
    open.clear();
    closedSize = closed.size();
    for (QSet<State*>::iterator it = closed.begin(); it != closed.end(); )
    {
        State* state = *it;
        ++it;
        SAFE_DELETE(state);
    }
    closed.clear();
}

QString DFSThread::getInfo()
{
    if (!isSucceed && !isExit)
    {
        openSize = open.size();
        closedSize = closed.size();
        elapsedSec = (float)time->elapsed() / 1000.0f;
    }
    QString str = QString("open=%1; closed=%2; round=%3; elapsed=%4s")
            .arg(openSize).arg(closedSize).arg(deep).arg(elapsedSec);
    if (0 == openSize && isSucceed)
    {
        str.append("; 已遍历所有情况，无解");
    }
    return str;
}
