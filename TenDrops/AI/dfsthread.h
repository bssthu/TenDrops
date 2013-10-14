//
// Module			: dfsthread.h
// Author			: bss
// Project			: TenDrops
// State			:
// Creation Date	: 2013-10-13
// Last Modification: 2013-10-14
// Description		: Thread of dfs search.
//

#ifndef DFSTHREAD_H
#define DFSTHREAD_H

#include "mythread.h"
#include <QList>
#include <QVector>
#include <QStack>

class DFSThread : public MyThread
{
public:
    DFSThread(State* state, int water, QObject *parent = 0);
    QString getInfo();

protected:
    void run();

private:
    State *traversal();
    void addToOpenList(State* newState);

private:
    QVector<State*> open;
    QStack<State*> closed;
};

#endif // DFSTHREAD_H
