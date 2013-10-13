//
// Module			: bfsthread.h
// Author			: bss
// Project			: TenDrops
// State			:
// Creation Date	: 2013-10-13
// Last Modification: 2013-10-14
// Description		: Thread of bfs search.
//

#ifndef BFSTHREAD_H
#define BFSTHREAD_H

#include "mythread.h"
#include <QSet>

class BFSThread : public MyThread
{
    Q_OBJECT
public:
    explicit BFSThread(State* state, int water, QObject *parent = 0);
    QString getInfo();

signals:

public slots:

protected:
    void run();
    void deleteElements();

private:
    State *bfs_traversal();
    void bfs_addToOpenList(State* newState);

public:
    static bool isBFS;

private:
    QSet<State*> open;
    QSet<State*> closed;
    int deep;
    bool isOutOfMemory;
};

#endif // BFSTHREAD_H
