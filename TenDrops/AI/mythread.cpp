//
// Module			: mythread.cpp
// Author			: bss
// Project			: TenDrops
// State			:
// Creation Date	: 2013-10-13
// Last Modification: 2013-10-14
// Description		:
//

#include "mythread.h"
#include <QStack>
#include <QTime>
#include "Macro.h"
#include "state.h"

MyThread::MyThread(int water, QObject *parent)
    : QThread(parent)
    , isExit(false)
    , openSize(0)
    , closedSize(0)
    , water(water)
    , isSucceed(false)
    , opers(nullptr)
    , steps(0)
    , stepsCompleted(0)
    , time(new QTime())
    , elapsedSec(0.0f)
{
}

MyThread::~MyThread()
{
    SAFE_DELETE_ARRAY(opers);
    deleteElements();
}

bool MyThread::succeed()
{
    return isSucceed;
}

MyThread::Point MyThread::nextOper()
{
    if (stepsCompleted >= steps)
    {
        Point pt;
        pt.x = pt.y = -1;
        return pt;
    }
    return opers[stepsCompleted++];
}

void MyThread::traceBackState(State* state)
{
    QStack<State*> stack;
    do
    {
        stack.push(state);
        state = state->getPrev();
    } while (nullptr != state);

    opers = new Point[stack.size()];
    steps = stack.size() - 1;  // Skip first state
    state = stack.pop();
    for (int i = 0; i < steps; ++i)
    {
        state = stack.pop();
        opers[i].x = state->getX();
        opers[i].y = state->getY();
    }
}
