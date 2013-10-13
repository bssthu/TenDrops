//
// Module			: mainwindow.h
// Author			: bss
// Project			: TenDrops
// State			:
// Creation Date	: 2013-10-08
// Last Modification: 2013-10-11
// Description		: Game controller.
//

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void loadMap(const char* filename);
    void saveMap();
    void sigDebug(void* bug);
    void bfs();

private slots:
    void on_loadPushButton_clicked();
    void on_savePushButton_clicked();
    void on_bfsPushButton_clicked();
    void on_debugPushButton_clicked();
    void on_exitAction_triggered();
    void on_aboutAction_triggered();

private:
    void initUI();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
