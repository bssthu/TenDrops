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

MyThread::MyThread(State *state, int water, QObject *parent)
    : QThread(parent)
    , isExit(false)
    , open()
    , closed()
    , openSize(0)
    , closedSize(0)
    , water(water)
    , isSucceed(false)
    , opers(nullptr)
    , steps(0)
    , stepsCompleted(0)
{
    open.push_back(state);
}

MyThread::~MyThread()
{
    SAFE_DELETE_ARRAY(opers);
    deleteList();
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

void MyThread::deleteList()
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
