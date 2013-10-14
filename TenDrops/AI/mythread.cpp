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
    , isSucceed(false)
    , water(water)
    , deep(0)
    , steps(0)
    , stepsCompleted(0)
    , opers(nullptr)
    , time(new QTime())
    , elapsedSec(0.0f)
    , isOutOfMemory(false)
{
}

MyThread::~MyThread()
{
    SAFE_DELETE_ARRAY(opers);
    SAFE_DELETE(time);
    deleteElements();
}

bool MyThread::succeed()
{
    return isSucceed;
}

int MyThread::getRemainSteps()
{
    return steps - stepsCompleted;
}

MyThread::Point MyThread::nextOper()
{
    if (stepsCompleted >= steps)
    {
        Point pt;
        pt.x = pt.y = -1;
        return pt;
    }
    return opers[(int)stepsCompleted++];
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
