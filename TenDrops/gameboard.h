//
// Module			: gameboard.h
// Author			: bss
// Project			: TenDrops
// State			:
// Creation Date	: 2013-10-09
// Last Modification: 2013-10-13
// Description		: Game controller.
//

#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QObject>
#include "AI/bfsthread.h"

class QGraphicsScene;
class QTimer;
class GridGraphics;
class DropGraphics;
class BFSThread;

class GameBoard : public QObject
{
    Q_OBJECT
public:
    explicit GameBoard(QGraphicsScene* scene, QObject *parent = 0);
    ~GameBoard();

    void onClicked(const QPointF* point);
    void onLoadMap(const char* filename);
    void onSaveMap();
    void onBFS();
    void onDFS();

    void nextOper();
    void abortThread();
    QString checkThreadInfo();
    void checkCalcResult();

signals:
    void updated();

    void beginRun();
    void endRound();
    void beginAutoRun();
    void endAutoRun();
    void beginAutoCalc();
    void calcOK();

    void setDropsLeft(int water);

public slots:
    void step();

private:
    void createGrids();
    void addDrops(int x, int y);
    void checkDrops();
    void checkBurst();
    void moveDrops(float percent);

private:
    QGraphicsScene* scene;
    // 可以包含水珠的格子
    GridGraphics** grids;
    // 飞行的水滴，按优先级排序
    QList<DropGraphics*> drops[4];
    int water;
    int combo;

    // 动画相关
    int moves;
    static const int MAX_MOVE = 10;

    MyThread* thread;
};

#endif // GAMEBOARD_H
