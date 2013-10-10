//
// Module			: gameboard.h
// Author			: bss
// Project			: TenDrops
// State			:
// Creation Date	: 2013-10-09
// Last Modification: 2013-10-10
// Description		: Game controller.
//

#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QObject>
#include <list>

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

public slots:
    void onClicked(const QPointF* point);
    void step();

private:
    void createGrids();
    void addDrop(int x, int y);
    void checkDropList();
    void checkBurst();

private:
    QGraphicsScene* scene;
    // 可以包含水珠的格子
    GridGraphics** grids;
    // 飞行的水滴，按优先级排序
    std::list<DropGraphics*> drops[4];
};

#endif // GAMEBOARD_H
