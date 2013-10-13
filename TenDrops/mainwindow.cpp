//
// Module			: mainwindow.cpp
// Author			: bss
// Project			: TenDrops
// State			:
// Creation Date	: 2013-10-08
// Last Modification: 2013-10-13
// Description		:
//

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QTimer>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , label(new QLabel(this))
    , timer(new QTimer(this))
{
    ui->setupUi(this);
    ui->statusBar->addWidget(label);
    initUI();
    timer->start(500);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initUI()
{
    setWindowIcon(QIcon("://Data//icon.ico"));
    connect(this, &MainWindow::loadMap, ui->graphicsView, &MyGraphicsView::onLoadMap);
    connect(this, &MainWindow::saveMap, ui->graphicsView, &MyGraphicsView::onSaveMap);
    connect(this, &MainWindow::sigDebug, ui->graphicsView, &MyGraphicsView::onDebug);
    connect(this, &MainWindow::bfs, ui->graphicsView, &MyGraphicsView::onBFS);
    connect(this, &MainWindow::dfs, ui->graphicsView, &MyGraphicsView::onDFS);
    connect(timer, &QTimer::timeout, ui->graphicsView, &MyGraphicsView::checkThreadResult);
    connect(timer, &QTimer::timeout, this, &MainWindow::checkThreadInfo);
}

void MainWindow::on_loadPushButton_clicked()
{
    emit loadMap("Data//Maps//1.map");
}

void MainWindow::on_savePushButton_clicked()
{
    emit saveMap();
}

void MainWindow::on_bfsPushButton_clicked()
{
    emit bfs();
}

void MainWindow::on_dfsPushButton_clicked()
{
    emit dfs();
}

void MainWindow::on_abortPushButton_clicked()
{
    ui->graphicsView->abortThread();
}

void MainWindow::on_debugPushButton_clicked()
{
    emit sigDebug(nullptr);
}

void MainWindow::on_exitAction_triggered()
{
    close();
}

void MainWindow::on_aboutAction_triggered()
{
    QMessageBox::information(this, "关于", "作者: 蚌绍诗\n班级: 自03\n学号: 2010011428");
}

void MainWindow::checkThreadInfo()
{
    label->setText(ui->graphicsView->checkThreadInfo());
}

void MainWindow::closeEvent(QCloseEvent* /*event*/)
{
    ui->graphicsView->onClose();
}
