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
#include "state.h"

DFSThread::DFSThread(State *state, int water, QObject *parent)
    : MyThread(water, parent)
{
    state->setWater(water);
    open.push_back(state);
}

void DFSThread::run()
{
    //open.
    for (int x = 0; x < 6; ++x)
    {
        for (int y = 0; y < 6; ++y)
        {
        }
    }
}

QString DFSThread::getInfo()
{
    return QString("open=%1; closed=%2").arg(open.size()).arg(closed.size());
}
