//
// Module			: mygraphicsview.cpp
// Author			: bss
// Project			: TenDrops
// State			:
// Creation Date	: 2013-10-09
// Last Modification: 2013-10-13
// Description		:
//

#include "mygraphicsview.h"
#include <QMouseEvent>
#include <QTimer>
#include <QGraphicsTextItem>
#include <QTextDocument>
#include "gameboard.h"

MyGraphicsView::MyGraphicsView(QWidget *parent)
    : QGraphicsView(parent)
    , uiMode(UIMode::FREE)
    , gameboard(NULL)
    , timer(new QTimer(this))
    , text(new QGraphicsTextItem())
{
    initUI();
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void MyGraphicsView::initUI()
{
    setScene(new QGraphicsScene());
    scene()->addPixmap(QPixmap("://Data//Textures//background.png"));
    gameboard = new GameBoard(scene(), this);

    QTextDocument* doc = text->document();
    QTextOption opt = doc->defaultTextOption();
    opt.setAlignment(Qt::AlignCenter | Qt::AlignHCenter);
    doc->setDefaultTextOption(opt);
    QFont font("MSYH", 40);
    doc->setDefaultFont(font);
    text->setPlainText("????");
    text->setTextWidth(doc->idealWidth());
    text->setPlainText("10");
    text->setPos(395.0f, 25.0f);
    scene()->addItem(text);

    connect(this, &MyGraphicsView::clicked, gameboard, &GameBoard::onClicked);
    connect(this, &MyGraphicsView::loadMap, gameboard, &GameBoard::onLoadMap);
    connect(this, &MyGraphicsView::saveMap, gameboard, &GameBoard::onSaveMap);
    connect(gameboard, &GameBoard::updated, this, &MyGraphicsView::invalidate);
    connect(gameboard, &GameBoard::beginRun, this, &MyGraphicsView::beginManualRun);
    connect(gameboard, &GameBoard::endRound, this, &MyGraphicsView::endRound);
    connect(gameboard, &GameBoard::beginAutoRun, this, &MyGraphicsView::beginAutoRun);
    connect(gameboard, &GameBoard::endAutoRun, this, &MyGraphicsView::endAutoRun);
    connect(gameboard, &GameBoard::setDropsLeft, this, &MyGraphicsView::onSetDropsLeft);
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
        timer->start(20);
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

void MyGraphicsView::onLoadMap(const char* filename)
{
    emit loadMap(filename);
}

void MyGraphicsView::onSaveMap()
{
    emit saveMap();
}

void MyGraphicsView::onDebug(void*)
{
#ifdef QT_DEBUG
#endif
}

void MyGraphicsView::onSetDropsLeft(int dropNum)
{
    text->setPlainText(QString::number(dropNum));
}
