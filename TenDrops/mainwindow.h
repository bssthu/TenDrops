//
// Module			: mainwindow.h
// Author			: bss
// Project			: TenDrops
// State			:
// Creation Date	: 2013-10-08
// Last Modification: 2013-10-10
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

private slots:

private:
    void initUI();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
