//
// Module			: mainwindow.cpp
// Author			: bss
// Project			: TenDrops
// State			:
// Creation Date	: 2013-10-08
// Last Modification: 2013-10-09
// Description		:
//

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsView>
#include "gameboard.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    gameboard(NULL)
{
    ui->setupUi(this);
    InitUI();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::InitUI()
{
    setWindowIcon(QIcon("://Data//icon.ico"));
    QGraphicsScene* scene = new QGraphicsScene();
    ui->graphicsView->setScene(scene);
    gameboard = new GameBoard(scene, this);
    connect(ui->graphicsView, &MyGraphicsView::clicked, gameboard, &GameBoard::onClicked);
    connect(gameboard, &GameBoard::updated, ui->graphicsView, &MyGraphicsView::invalidate);
    connect(gameboard, &GameBoard::beginRun, ui->graphicsView, &MyGraphicsView::beginManualRun);
    connect(gameboard, &GameBoard::endRound, ui->graphicsView, &MyGraphicsView::endRound);
    connect(gameboard, &GameBoard::beginAutoRun, ui->graphicsView, &MyGraphicsView::beginAutoRun);
    connect(gameboard, &GameBoard::endAutoRun, ui->graphicsView, &MyGraphicsView::endAutoRun);
}
