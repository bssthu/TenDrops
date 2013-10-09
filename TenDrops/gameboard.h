//
// Module			: gameboard.h
// Author			: bss
// Project			: TenDrops
// State			:
// Creation Date	: 2013-10-09
// Last Modification: 2013-10-09
// Description		: Game controller.
//

#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QObject>
#include <list>

class QGraphicsScene;
class Grid;

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
    void dropBurst(int x, int y);

private:
    void CreateGrids();

private:
    QGraphicsScene* scene;
    // 可以包含水珠的格子
    Grid** grids;
    // 飞行的水滴
    std::list<int> drops;
};

#endif // GAMEBOARD_H
