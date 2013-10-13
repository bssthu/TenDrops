//
// Module			: mythread.cpp
// Author			: bss
// Project			: TenDrops
// State			:
// Creation Date	: 2013-10-13
// Last Modification: 2013-10-13
// Description		:
//

#include "mythread.h"
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
