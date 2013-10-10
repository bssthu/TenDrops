//
// Module			: gameboard.cpp
// Author			: bss
// Project			: TenDrops
// State			:
// Creation Date	: 2013-10-09
// Last Modification: 2013-10-10
// Description		:
//

#include "gameboard.h"
#include <QGraphicsView>
#include "gridgraphics.h"
#include "dropgraphics.h"
#include "Macro.h"

GameBoard::GameBoard(QGraphicsScene *scene, QObject *parent)
    : QObject(parent)
    , scene(scene)
    , grids(new GridGraphics*[36])
    , drops()
{
    createGrids();
}

GameBoard::~GameBoard()
{
    SAFE_DELETE(scene);
    SAFE_DELETE_ARRAY(grids);
}

void GameBoard::onClicked(const QPointF *point)
{
    // 判断格子
    int i = GridGraphics::getCoordX(point->x());
    int j = GridGraphics::getCoordY(point->y());
    if (i >= 0 && j >= 0)
    {
        // 加水
        grids[i * 6 + j]->addDrop();
        if (grids[i * 6 + j]->checkBurst())
        {
            addDrop(i, j);
            emit beginRun();
        }
        emit updated();
    }
}

void GameBoard::createGrids()
{
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            grids[i * 6 + j] = new GridGraphics(i, j);
            scene->addItem(grids[i * 6 + j]);
        }
    }
}

void GameBoard::step()
{
    checkDropList();
    checkBurst();
    if (drops[0].size() == 0
            && drops[1].size() == 0
            && drops[2].size() == 0
            && drops[3].size() == 0)
    {
        emit endRound();
    }
    emit updated();
}

void GameBoard::checkDropList()
{
    for (int i = 0; i < 4; i++)
    {
        for (std::list<DropGraphics*>::iterator it = drops[i].begin(); it != drops[i].end(); )
        {
            DropGraphics* drop = *it;
            drop->step();
            // 碰到边沿
            if ((*it)->isDead())
            {
                // Remove
                scene->removeItem(drop);
                it = drops[i].erase(it);
            }
            // 碰到水滴
            else if (grids[drop->Drop::x() * 6 + drop->Drop::y()]->canAcceptDrop())
            {
                grids[drop->Drop::x() * 6 + drop->Drop::y()]->addDrop();
                // Remove
                scene->removeItem(drop);
                it = drops[i].erase(it);
            }
            else
            {
                ++it;
            }
        }
    }
}

void GameBoard::checkBurst()
{
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            if (grids[i * 6 + j]->checkBurst())
            {
                addDrop(i, j);
            }
        }
    }
}

void GameBoard::addDrop(int x, int y)
{
    for (int i = 0; i < 4; i++)
    {
        DropGraphics* drop = new DropGraphics((Drop::DropFrom)i, x, y);
        drops[i].push_back(drop);
        scene->addItem(drop);
    }
}
