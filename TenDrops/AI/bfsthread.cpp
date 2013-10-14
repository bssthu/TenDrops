//
// Module			: bfsthread.cpp
// Author			: bss
// Project			: TenDrops
// State			:
// Creation Date	: 2013-10-13
// Last Modification: 2013-10-14
// Description		:
//

#include "bfsthread.h"
#include <QTime>
#include "state.h"
#include "Macro.h"

bool BFSThread::isBFS = true;

BFSThread::BFSThread(State* state, int water, QObject *parent)
    : MyThread(water, parent)
    , open()
    , closed()
{
    open.insert(state);
}

void BFSThread::run()
{
    time->start();
    State* finalState = nullptr;
    do
    {
        ++deep;
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

State* BFSThread::traversal()
{
    int i = 0;
    int iEnd = open.size();
    for (QSet<State*>::iterator it = open.begin(); i < iEnd && it != open.end(); ++i)
    {
        if (open.size() + closed.size() > 10000000)
        {
            isExit = true;
            isOutOfMemory = true;
        }
        if (isExit)
        {
            return nullptr;
        }
        State* curState = *it;
        if (curState->getG() > deep)    // 保证是严格的宽度优先搜索
        {
            ++it;
            continue;
        }
        // 水不能为负
        if (curState->getG() >= water)
        {
            it = open.erase(it);
            closed.insert(curState);
            continue;
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
        it = open.erase(it);
        closed.insert(curState);
    }
    return nullptr;
}

void BFSThread::addToOpenList(State* newState)
{
    if (open.contains(newState))
    {
        SAFE_DELETE(newState);
        return;
    }
    if (closed.contains(newState))
    {
        SAFE_DELETE(newState);
        return;
    }
    open.insert(newState);
}

void BFSThread::deleteElements()
{
    openSize = open.size();
    for (QSet<State*>::iterator it = open.begin(); it != open.end(); )
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

QString BFSThread::getInfo()
{
    if (!isSucceed && !isExit)
    {
        openSize = open.size();
        closedSize = closed.size();
        elapsedSec = (float)time->elapsed() / 1000.0f;
    }
    QString str = QString("open=%1; closed=%2; round=%3; elapsed=%4s")
            .arg(openSize).arg(closedSize).arg(deep).arg(elapsedSec);
    if (isOutOfMemory)
    {
        str.append("; 内存耗尽，无解");
    }
    if (0 == openSize && isSucceed)
    {
        str.append("; 已遍历所有情况，无解");
    }
    if ((isSucceed || isExit) && isRunning())
    {
        str.append("; 正在释放资源");
    }
    return str;
}
