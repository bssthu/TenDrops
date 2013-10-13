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

MyThread::MyThread(State *state, QObject *parent)
    : QThread(parent)
    , isExit(false)
    , open()
    , closed()
    , opers(nullptr)
    , steps(0)
{
    open.push_back(state);
}

MyThread::~MyThread()
{
    SAFE_DELETE_ARRAY(opers);
    deleteList();
}

void MyThread::deleteList()
{
    for (QLinkedList<State*>::iterator it = open.begin(); it != open.end(); )
    {
        State* state = *it;
        ++it;
        SAFE_DELETE(state);
    }
    open.clear();
    for (QLinkedList<State*>::iterator it = closed.begin(); it != closed.end(); )
    {
        State* state = *it;
        ++it;
        SAFE_DELETE(state);
    }
    closed.clear();
}
