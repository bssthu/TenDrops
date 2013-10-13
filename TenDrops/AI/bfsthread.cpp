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
#include <QStack>
#include "state.h"
#include "Macro.h"

bool BFSThread::isBFS = true;

BFSThread::BFSThread(State* state, int water, QObject *parent)
    : MyThread(water, parent)
    , open()
    , closed()
    , deep(0)
    , isOutOfMemory(false)
{
    state->setWater(water);
    open.insert(state);
}

void BFSThread::run()
{
    State* finalState = nullptr;
    do
    {
        ++deep;
        finalState = bfs_traversal();
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
//        if (curState->getG() > deep)    // 保证是严格的宽度优先搜索
//        {
//            ++it;
//            continue;
//        }
        // 水不能为负
        if (curState->getWater() <= 1)
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
                        bfs_addToOpenList(newState);
                        return newState;
                    }
                    bfs_addToOpenList(newState);
                }
            }
        }
        it = open.erase(it);
        closed.insert(curState);
    }
    return nullptr;
}

void BFSThread::bfs_addToOpenList(State* newState)
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
    }
    QString str = QString("open=%1; closed=%2; round=%3").arg(openSize).arg(closedSize).arg(deep);
    if (isOutOfMemory)
    {
        str.append("; 内存耗尽，无解");
    }
    if ((isSucceed || isExit) && isRunning())
    {
        str.append("; 正在释放资源");
    }
    return str;
}
