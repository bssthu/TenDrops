//
// Module			: dfsthread.h
// Author			: bss
// Project			: TenDrops
// State			:
// Creation Date	: 2013-10-13
// Last Modification: 2013-10-13
// Description		: Thread of dfs search.
//

#ifndef DFSTHREAD_H
#define DFSTHREAD_H

#include "mythread.h"

class DFSThread : public MyThread
{
public:
    DFSThread(State* state, int water, QObject *parent = 0);
    QString getInfo();

protected:
    void run();
};

#endif // DFSTHREAD_H
