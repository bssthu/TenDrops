//
// Module			: mygraphicsview.cpp
// Author			: bss
// Project			: TenDrops
// State			:
// Creation Date	: 2013-10-09
// Last Modification: 2013-10-09
// Description		:
//

#include "mygraphicsview.h"
#include <QMouseEvent>

MyGraphicsView::MyGraphicsView(QWidget *parent)
    : QGraphicsView(parent)
    , uiMode(UIMode::FREE)
{
}

void MyGraphicsView::mousePressEvent(QMouseEvent *event)
{
    if (Qt::LeftButton == event->button())
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
    }
}

void MyGraphicsView::endRound()
{
    if (UIMode::MANUALRUN == uiMode)
    {
        uiMode = UIMode::FREE;
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
