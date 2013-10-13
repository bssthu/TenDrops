//
// Module			: gameboard.cpp
// Author			: bss
// Project			: TenDrops
// State			:
// Creation Date	: 2013-10-09
// Last Modification: 2013-10-13
// Description		:
//

#include "gameboard.h"
#include <QGraphicsView>
#include "gridgraphics.h"
#include "dropgraphics.h"
#include "Macro.h"
#include "mapreader.h"
#include "state.h"
#include "AI/bfsthread.h"

GameBoard::GameBoard(QGraphicsScene *scene, QObject *parent)
    : QObject(parent)
    , scene(scene)
    , grids(new GridGraphics*[36])
    , drops()
    , dropNum(10)
    , combo(0)
    , moves(0)
    , thread(nullptr)
    , stepsCompleted(0)
{
    createGrids();
}

GameBoard::~GameBoard()
{
    SAFE_DELETE(scene);
    SAFE_DELETE_ARRAY(grids);
}

DropGraphics* drop = nullptr;

void GameBoard::onClicked(const QPointF *point)
{
    // 判断格子
    int x = GridGraphics::getCoordX(point->x());
    int y = GridGraphics::getCoordY(point->y());
    if (x >= 0 && y >= 0)
    {
        combo = 0;
        // 加水
        grids[y * 6 + x]->addDrop();
        if (grids[y * 6 + x]->checkBurst())
        {
            ++combo;
            addDrops(x, y);
            emit beginRun();
        }
        emit setDropsLeft(--dropNum);
        emit updated();
    }
}

void GameBoard::createGrids()
{
    for (int x = 0; x < 6; ++x)
    {
        for (int y = 0; y < 6; ++y)
        {
            grids[y * 6 + x] = new GridGraphics(x, y);
            scene->addItem(grids[y * 6 + x]);
        }
    }
}

void GameBoard::step()
{
    if (++moves >= MAX_MOVE)
    {
        // 进行判断
        checkDrops();
        checkBurst();
        if (drops[0].size() == 0
                && drops[1].size() == 0
                && drops[2].size() == 0
                && drops[3].size() == 0)
        {
            emit endRound();
        }
        moves = 0;
    }
    else
    {
        // 播放动画
        moveDrops(1.0f / (float)MAX_MOVE);
    }
    emit updated();
}

void GameBoard::onLoadMap(const char* filename)
{
    int buffer[36];
    if (MapReader::readMap(filename, buffer))
    {
        for (int x = 0; x < 6; ++x)
        {
            for (int y = 0; y < 6; ++y)
            {
                grids[y * 6 + x]->setDropSize(buffer[y * 6 + x]);
            }
        }
    }
    emit updated();
}

void GameBoard::onSaveMap()
{
    int buffer[36];
    for (int x = 0; x < 6; ++x)
    {
        for (int y = 0; y < 6; ++y)
        {
            buffer[y * 6 + x] = grids[y * 6 + x]->dropSize();
        }
    }
    MapReader::saveMap("Data//Maps//1.map", buffer);
}

void GameBoard::onBFS()
{
    int buffer[36];
    for (int x = 0; x < 6; ++x)
    {
        for (int y = 0; y < 6; ++y)
        {
            buffer[y * 6 + x] = grids[y * 6 + x]->dropSize();
        }
    }
    State* state = new State(buffer);
    thread = new BFSThread(state);
    thread->start();
    emit beginAutoRun();
}

void GameBoard::nextOper()
{
//    if (stepsCompleted >= steps)
//    {
//        emit endAutoRun();
//        SAFE_DELETE_ARRAY(opers);
//        stepsCompleted = 0;
//        steps = 0;
//        return;
//    }
//    grids[opers[stepsCompleted].y * 6 + opers[stepsCompleted].x]->addDrop();

    ++stepsCompleted;
}

void GameBoard::checkDrops()
{
    for (int i = 0; i < 4; ++i)
    {
        for (QList<DropGraphics*>::iterator it = drops[i].begin(); it != drops[i].end(); )
        {
            DropGraphics* drop = *it;
            drop->step();
            // 碰到边沿
            if ((*it)->isDead())
            {
                // Remove
                scene->removeItem(drop);
                it = drops[i].erase(it);
                SAFE_DELETE(drop);
            }
            // 碰到水滴
            else if (grids[drop->Drop::y() * 6 + drop->Drop::x()]->canAcceptDrop())
            {
                grids[drop->Drop::y() * 6 + drop->Drop::x()]->addDrop();
                // Remove
                scene->removeItem(drop);
                it = drops[i].erase(it);
                SAFE_DELETE(drop);
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
    for (int x = 0; x < 6; ++x)
    {
        for (int y = 0; y < 6; ++y)
        {
            if (grids[y * 6 + x]->checkBurst())
            {
                ++combo;
                if (combo >= 3)
                {
                    combo = 0;
                    emit setDropsLeft(++dropNum);
                }
                addDrops(x, y);
            }
        }
    }
}

void GameBoard::moveDrops(float percent)
{
    for (int i = 0; i < 4; ++i)
    {
        for (QList<DropGraphics*>::iterator it = drops[i].begin(); it != drops[i].end(); ++it)
        {
            DropGraphics* drop = *it;
            drop->move(percent);
        }
    }
}

void GameBoard::addDrops(int x, int y)
{
    for (int i = 0; i < 4; ++i)
    {
        DropGraphics* drop = new DropGraphics((Drop::DropFrom)i, x, y);
        drops[i].push_back(drop);
        scene->addItem(drop);
    }
}

void GameBoard::abortThread()
{
    if (nullptr != thread)
    {
        thread->isExit = true;
        thread->wait();
        SAFE_DELETE(thread);
    }
}

QString GameBoard::checkThreadInfo()
{
    if (nullptr != thread)
    {
        return thread->getInfo();
    }
    else
    {
        return "就绪";
    }
}
