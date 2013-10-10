//
// Module			: mygraphicsview.cpp
// Author			: bss
// Project			: TenDrops
// State			:
// Creation Date	: 2013-10-09
// Last Modification: 2013-10-10
// Description		:
//

#include "mygraphicsview.h"
#include <QMouseEvent>
#include <QTimer>
#include "gameboard.h"

MyGraphicsView::MyGraphicsView(QWidget *parent)
    : QGraphicsView(parent)
    , uiMode(UIMode::FREE)
    , gameboard(NULL)
    , timer(new QTimer(this))
{
    initUI();
}

void MyGraphicsView::initUI()
{
    setScene(new QGraphicsScene());
    scene()->addPixmap(QPixmap("://Data//Textures//background.png"));
    gameboard = new GameBoard(scene(), this);

    connect(this, &MyGraphicsView::clicked, gameboard, &GameBoard::onClicked);
    connect(gameboard, &GameBoard::updated, this, &MyGraphicsView::invalidate);
    connect(gameboard, &GameBoard::beginRun, this, &MyGraphicsView::beginManualRun);
    connect(gameboard, &GameBoard::endRound, this, &MyGraphicsView::endRound);
    connect(gameboard, &GameBoard::beginAutoRun, this, &MyGraphicsView::beginAutoRun);
    connect(gameboard, &GameBoard::endAutoRun, this, &MyGraphicsView::endAutoRun);
    connect(timer, &QTimer::timeout, gameboard, &GameBoard::step);
}

void MyGraphicsView::mousePressEvent(QMouseEvent *event)
{
    if (Qt::LeftButton == event->button() && UIMode::FREE == uiMode)
    {
        emit clicked(&event->localPos());
    }
}

void MyGraphicsView::invalidate()
{
    scene()->update();
}

void MyGraphicsView::beginManualRun()
{
    if (UIMode::FREE == uiMode)
    {
        uiMode = UIMode::MANUALRUN;
        timer->start(500);
    }
}

void MyGraphicsView::endRound()
{
    if (UIMode::MANUALRUN == uiMode)
    {
        uiMode = UIMode::FREE;
        timer->stop();
    }
}

void MyGraphicsView::beginAutoRun()
{
    if (UIMode::FREE == uiMode)
    {
        uiMode = UIMode::AUTORUN;
    }
}

void MyGraphicsView::endAutoRun()
{
    uiMode = UIMode::FREE;
}
