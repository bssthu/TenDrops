//
// Module			: gameboard.cpp
// Author			: bss
// Project			: TenDrops
// State			:
// Creation Date	: 2013-10-09
// Last Modification: 2013-10-09
// Description		:
//

#include "gameboard.h"
#include <QGraphicsView>
#include <QMessageBox>
#include "grid.h"
#include "Macro.h"

GameBoard::GameBoard(QGraphicsScene *scene, QObject *parent)
    : QObject(parent)
    , scene(scene)
    , grids(new Grid*[36])
{
    scene->addPixmap(QPixmap("://Data//Textures//background.png"));
    CreateGrids();
}

GameBoard::~GameBoard()
{
    SAFE_DELETE(scene);
    SAFE_DELETE_ARRAY(grids);
}

void GameBoard::onClicked(const QPointF *point)
{
    // 判断格子
    int i = Grid::getCoordX(point->x());
    int j = Grid::getCoordY(point->y());
    if (i >= 0 && j >= 0)
    {
        // 加水
        grids[i * 6 + j]->addDrop();
        emit updated();
    }
}

void GameBoard::dropBurst(int x, int y)
{
    emit beginRun();
}

void GameBoard::CreateGrids()
{
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            grids[i * 6 + j] = new Grid(i, j);
            scene->addItem(grids[i * 6 + j]);
            connect(grids[i * 6 + j], &Grid::burst, this, &GameBoard::dropBurst);
        }
    }
}
