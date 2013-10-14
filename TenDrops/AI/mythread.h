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
    int getRemainSteps();
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
    bool isSucceed;
    char water;
    int deep;
    char steps;
    char stepsCompleted;
    Point* opers;
    QTime* time;
    float elapsedSec;
    bool isOutOfMemory;
};

#endif // MYTHREAD_H
