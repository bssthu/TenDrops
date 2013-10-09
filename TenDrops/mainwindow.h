//
// Module			: mainwindow.h
// Author			: bss
// Project			: TenDrops
// State			:
// Creation Date	: 2013-10-08
// Last Modification: 2013-10-09
// Description		: Game controller.
//

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class GameBoard;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void InitUI();

private slots:

private:
    Ui::MainWindow *ui;
    GameBoard* gameboard;
};

#endif // MAINWINDOW_H
