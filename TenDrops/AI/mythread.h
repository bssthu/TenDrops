//
// Module			: mythread.h
// Author			: bss
// Project			: TenDrops
// State			:
// Creation Date	: 2013-10-13
// Last Modification: 2013-10-13
// Description		: Thread for AI.
//

#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
#include <QLinkedList>

class State;

class MyThread : public QThread
{
    Q_OBJECT
public:
    explicit MyThread(State* state, QObject *parent = 0);
    ~MyThread();

    virtual QString getInfo() = 0;

signals:

public slots:

protected:
    void deleteList();

public:
    struct Point
    {
        int x;
        int y;
    };

public:
    volatile bool isExit;

protected:
    QLinkedList<State*> open;
    QLinkedList<State*> closed;
    Point* opers;
    int steps;
};

#endif // MYTHREAD_H
