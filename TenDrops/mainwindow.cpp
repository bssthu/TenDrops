//
// Module			: mainwindow.cpp
// Author			: bss
// Project			: TenDrops
// State			:
// Creation Date	: 2013-10-08
// Last Modification: 2013-10-15
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
    , infoLabel(new QLabel(this))
    , modeLabel(new QLabel(this))
    , timer(new QTimer(this))
{
    ui->setupUi(this);
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
    ui->statusBar->addWidget(modeLabel);
    ui->statusBar->addWidget(infoLabel);
    ui->levelSpinBox->setMinimum(1);
    onSetUIMode(MyGraphicsView::UIMode::FREE);

    connect(this, &MainWindow::loadMap, ui->graphicsView, &MyGraphicsView::onLoadMap);
    connect(this, &MainWindow::saveMap, ui->graphicsView, &MyGraphicsView::onSaveMap);
    connect(this, &MainWindow::sigDebug, ui->graphicsView, &MyGraphicsView::onDebug);
    connect(this, &MainWindow::bfs, ui->graphicsView, &MyGraphicsView::onBFS);
    connect(this, &MainWindow::dfs, ui->graphicsView, &MyGraphicsView::onDFS);
    connect(timer, &QTimer::timeout, ui->graphicsView, &MyGraphicsView::checkThreadResult);
    connect(timer, &QTimer::timeout, this, &MainWindow::checkThreadInfo);
    connect(ui->graphicsView, &MyGraphicsView::setUIMode, this, &MainWindow::onSetUIMode);
    connect(ui->graphicsView, &MyGraphicsView::toNextLevel, this, &MainWindow::toNextLevel);

    loadMapLevel(1);
}

void MainWindow::loadMapLevel(int level)
{
    QString filename = QString("Data//Maps//%1.map").arg(level);
    emit loadMap(filename.toLocal8Bit().data());
}

void MainWindow::on_loadPushButton_clicked()
{
    loadMapLevel(ui->levelSpinBox->value());
}

void MainWindow::on_savePushButton_clicked()
{
    QString num = ui->levelSpinBox->text();
    QString filename = QString("Data//Maps//%1.map").arg(num);
    emit saveMap(filename.toLocal8Bit().data());
}

void MainWindow::on_bfsPushButton_clicked()
{
    emit bfs();
}

void MainWindow::on_dfsPushButton_clicked()
{
    emit dfs();
}

void MainWindow::on_runPushButton_clicked()
{
    ui->graphicsView->onBeginAutoRun();
}

void MainWindow::on_stepRadioButton_toggled()
{
    ui->graphicsView->onSetSingleStep(ui->stepRadioButton->isChecked());
}

void MainWindow::on_cheatPushButton_clicked()
{
    ui->graphicsView->cheat();
}

void MainWindow::on_abortPushButton_clicked()
{
    ui->graphicsView->abortThread();
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
    infoLabel->setText(ui->graphicsView->checkThreadInfo());
}

void MainWindow::onSetUIMode(MyGraphicsView::UIMode uiMode)
{
    switch (uiMode)
    {
    case MyGraphicsView::UIMode::FREE:
        modeLabel->setText("空闲　　");
        ui->loadPushButton->setEnabled(true);
        ui->savePushButton->setEnabled(true);
        ui->bfsPushButton->setEnabled(true);
        ui->dfsPushButton->setEnabled(true);
        ui->runPushButton->setEnabled(false);
        break;

    case MyGraphicsView::UIMode::MANUALRUN:
        modeLabel->setText("手动回合");
        ui->loadPushButton->setEnabled(false);
        ui->savePushButton->setEnabled(false);
        ui->bfsPushButton->setEnabled(false);
        ui->dfsPushButton->setEnabled(false);
        ui->runPushButton->setEnabled(false);
        break;

    case MyGraphicsView::UIMode::AUTORUN:
        modeLabel->setText("自动回合");
        ui->loadPushButton->setEnabled(false);
        ui->savePushButton->setEnabled(false);
        ui->bfsPushButton->setEnabled(false);
        ui->dfsPushButton->setEnabled(false);
        ui->runPushButton->setEnabled(false);
        break;

    case MyGraphicsView::UIMode::AUTOCALC:
        modeLabel->setText("自动计算");
        ui->loadPushButton->setEnabled(false);
        ui->savePushButton->setEnabled(false);
        ui->bfsPushButton->setEnabled(false);
        ui->dfsPushButton->setEnabled(false);
        ui->runPushButton->setEnabled(false);
        break;

    case MyGraphicsView::UIMode::CALCOK:
        modeLabel->setText("计算完成");
        ui->loadPushButton->setEnabled(false);
        ui->savePushButton->setEnabled(false);
        ui->bfsPushButton->setEnabled(false);
        ui->dfsPushButton->setEnabled(false);
        ui->runPushButton->setEnabled(true);
        break;

    default:
        modeLabel->setText("??　　　");
        break;
    }
}

void MainWindow::toNextLevel()
{
    int nextLv = ui->levelSpinBox->value() + 1;
    ui->levelSpinBox->setValue(nextLv);
    loadMapLevel(nextLv);
}

void MainWindow::closeEvent(QCloseEvent* /*event*/)
{
    infoLabel->setText(infoLabel->text().append("; 正在关闭，请稍候"));
    ui->graphicsView->onClose();
}
