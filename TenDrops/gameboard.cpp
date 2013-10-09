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
#include "drop.h"
#include "Macro.h"

GameBoard::GameBoard(QGraphicsScene *scene, QObject *parent)
    : QObject(parent)
    , scene(scene)
    , grids(new Grid*[36])
    , drops()
{
    CreateGrids();
}

GameBoard::~GameBoard()
{
    SAFE_DELETE(scene);
    SAFE_DELETE_ARRAY(grids);
}

void GameBoard::onClicked(const QPointF *point)
{
    // �жϸ���
    int i = Grid::getCoordX(point->x());
    int j = Grid::getCoordY(point->y());
    if (i >= 0 && j >= 0)
    {
        // ��ˮ
        grids[i * 6 + j]->addDrop();
        emit updated();
    }
}

void GameBoard::dropBurst(int x, int y)
{
    emit beginRun();
    Drop* drop = nullptr;
    drop = new Drop(Drop::DropFrom::NORTH, x, y);
    drops.push_back(drop);
    scene->addItem(drop);
    drop = new Drop(Drop::DropFrom::SOUTH, x, y);
    drops.push_back(drop);
    scene->addItem(drop);
    drop = new Drop(Drop::DropFrom::WEST, x, y);
    drops.push_back(drop);
    scene->addItem(drop);
    drop = new Drop(Drop::DropFrom::EAST, x, y);
    drops.push_back(drop);
    scene->addItem(drop);
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
