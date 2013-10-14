//
// Module			: mygraphicsview.cpp
// Author			: bss
// Project			: TenDrops
// State			:
// Creation Date	: 2013-10-09
// Last Modification: 2013-10-14
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
    , isSingleStep(true)
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

    connect(gameboard, &GameBoard::updated, this, &MyGraphicsView::invalidate);
    connect(gameboard, &GameBoard::beginRun, this, &MyGraphicsView::beginManualRun);
    connect(gameboard, &GameBoard::endRound, this, &MyGraphicsView::endRound);
    connect(gameboard, &GameBoard::beginAutoRun, this, &MyGraphicsView::beginAutoRun);
    connect(gameboard, &GameBoard::endAutoRun, this, &MyGraphicsView::endAutoRun);
    connect(gameboard, &GameBoard::beginAutoCalc, this, &MyGraphicsView::beginAutoCalc);
    connect(gameboard, &GameBoard::calcOK, this, &MyGraphicsView::calcOK);
    connect(gameboard, &GameBoard::setDropsLeft, this, &MyGraphicsView::onSetDropsLeft);
    connect(timer, &QTimer::timeout, gameboard, &GameBoard::step);
}

void MyGraphicsView::mousePressEvent(QMouseEvent *event)
{
    if (Qt::LeftButton == event->button() && UIMode::FREE == uiMode)
    {
        gameboard->onClicked(&event->localPos());
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
        emit setUIMode(uiMode);
        timer->start(20);
    }
}

void MyGraphicsView::endRound()
{
    if (UIMode::MANUALRUN == uiMode)
    {
        uiMode = UIMode::FREE;
        emit setUIMode(uiMode);
        timer->stop();
    }
    else if (UIMode::AUTORUN == uiMode)
    {
        timer->stop();
        uiMode = UIMode::AUTOCALC;
        emit setUIMode(uiMode);
        gameboard->checkCalcResult();
        if (!isSingleStep && UIMode::CALCOK == uiMode)
        {
            beginAutoRun();
        }
    }
}

void MyGraphicsView::beginAutoRun()
{
    if (UIMode::CALCOK == uiMode)
    {
        uiMode = UIMode::AUTORUN;
        emit setUIMode(uiMode);
        gameboard->nextOper();
        timer->start(20);
    }
}

void MyGraphicsView::endAutoRun()
{
    uiMode = UIMode::FREE;
    emit setUIMode(uiMode);
}

void MyGraphicsView::beginAutoCalc()
{
    if (UIMode::FREE == uiMode)
    {
        uiMode = UIMode::AUTOCALC;
        emit setUIMode(uiMode);
    }
}

void MyGraphicsView::calcOK()
{
    if (UIMode::AUTOCALC == uiMode)
    {
        uiMode = UIMode::CALCOK;
        emit setUIMode(uiMode);
    }
}

void MyGraphicsView::onLoadMap(const char* filename)
{
    gameboard->onLoadMap(filename);
}

void MyGraphicsView::onSaveMap()
{
    gameboard->onSaveMap();
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

void MyGraphicsView::onBFS()
{
    gameboard->onBFS();
}

void MyGraphicsView::onDFS()
{
    gameboard->onDFS();
}

void MyGraphicsView::onBeginAutoRun()
{
    if (UIMode::CALCOK == uiMode)
    {
        uiMode = UIMode::AUTORUN;
        emit setUIMode(uiMode);
        gameboard->nextOper();
        timer->start(20);
    }
}

void MyGraphicsView::onSetSingleStep(bool isSingle)
{
    isSingleStep = isSingle;
}

void MyGraphicsView::onClose()
{
    gameboard->abortThread();
}

QString MyGraphicsView::checkThreadInfo()
{
    return gameboard->checkThreadInfo();
}

void MyGraphicsView::checkThreadResult()
{
    if (UIMode::AUTOCALC == uiMode)
    {
        gameboard->checkCalcResult();
    }
}

void MyGraphicsView::abortThread()
{
    gameboard->abortThread();
}
