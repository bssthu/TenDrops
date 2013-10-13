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
#include <list>
#include "state.h"

class QGraphicsScene;
class GridGraphics;
class DropGraphics;

class GameBoard : public QObject
{
    Q_OBJECT
public:
    explicit GameBoard(QGraphicsScene* scene, QObject *parent = 0);
    ~GameBoard();

signals:
    void updated();

    void beginRun();
    void endRound();
    void beginAutoRun();
    void endAutoRun();

    void setDropsLeft(int dropNum);

public slots:
    void onClicked(const QPointF* point);
    void step();
    void onLoadMap(const char* filename);
    void onSaveMap();

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
    std::list<DropGraphics*> drops[4];
    std::list<DropGraphics*> deadDrops;
    int dropNum;
    int combo;
    // 动画相关
    int moves;
    static const int MAX_MOVE = 10;

    State* state;
};

#endif // GAMEBOARD_H
