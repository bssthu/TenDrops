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

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initUI();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initUI()
{
    setWindowIcon(QIcon("://Data//icon.ico"));
    connect(this, &MainWindow::loadMap, ui->graphicsView, &MyGraphicsView::loadMap);
    connect(this, &MainWindow::saveMap, ui->graphicsView, &MyGraphicsView::saveMap);
    connect(this, &MainWindow::sigDebug, ui->graphicsView, &MyGraphicsView::onDebug);
}

void MainWindow::on_loadPushButton_clicked()
{
    emit loadMap("Data//Maps//1.map");
}

void MainWindow::on_savePushButton_clicked()
{
    emit saveMap();
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
