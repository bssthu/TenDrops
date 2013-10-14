//
// Module			: mainwindow.h
// Author			: bss
// Project			: TenDrops
// State			:
// Creation Date	: 2013-10-08
// Last Modification: 2013-10-14
// Description		: Game controller.
//

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mygraphicsview.h"

namespace Ui {
class MainWindow;
}

class QLabel;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void loadMap(const char* filename);
    void saveMap(const char* filename);
    void sigDebug(void* bug);
    void bfs();
    void dfs();

private slots:
    void on_loadPushButton_clicked();
    void on_savePushButton_clicked();
    void on_bfsPushButton_clicked();
    void on_dfsPushButton_clicked();
    void on_runPushButton_clicked();
    void on_stepRadioButton_toggled();
    void on_abortPushButton_clicked();
    void on_exitAction_triggered();
    void on_aboutAction_triggered();

    void checkThreadInfo();

    void onSetUIMode(MyGraphicsView::UIMode uiMode);
    void toNextLevel();

protected:
    void closeEvent(QCloseEvent* event);

private:
    void initUI();
    void loadMapLevel(int level);

private:
    Ui::MainWindow *ui;
    QLabel* infoLabel;
    QLabel* modeLabel;
    QTimer* timer;
};

#endif // MAINWINDOW_H
