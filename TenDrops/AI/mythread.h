//
// Module			: mythread.h
// Author			: bss
// Project			: TenDrops
// State			:
// Creation Date	: 2013-10-13
// Last Modification: 2013-10-14
// Description		: Thread for AI.
//

#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>

class State;

class MyThread : public QThread
{
    Q_OBJECT
public:
    struct Point
    {
        int x;
        int y;
    };

public:
    explicit MyThread(int water, QObject *parent = 0);
    ~MyThread();

    virtual QString getInfo() = 0;
    bool succeed();
    Point nextOper();

signals:

public slots:

protected:
    virtual void deleteElements() { }
    void traceBackState(State* state);

public:
    volatile bool isExit;

protected:
    int openSize;
    int closedSize;
    int water;
    bool isSucceed;
    Point* opers;
    int steps;
    int stepsCompleted;
    QTime* time;
    float elapsedSec;
};

#endif // MYTHREAD_H
