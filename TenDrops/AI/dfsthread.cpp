//
// Module			: dfsthread.cpp
// Author			: bss
// Project			: TenDrops
// State			:
// Creation Date	: 2013-10-13
// Last Modification: 2013-10-13
// Description		:
//

#include "dfsthread.h"

DFSThread::DFSThread(State *state, int water, QObject *parent)
    : MyThread(state, water, parent)
{
}

void DFSThread::run()
{
}

QString DFSThread::getInfo()
{
    return QString("open=%1; closed=%2").arg(open.size()).arg(closed.size());
}
