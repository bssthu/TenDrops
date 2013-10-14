//
// Module			: main.cpp
// Author			: bss
// Project			: TenDrops
// State			:
// Creation Date	: 2013-10-08
// Last Modification: 2013-10-11
// Description		:
//

#include "mainwindow.h"
#include <QApplication>

#ifdef QT_DEBUG
#include <QDir>
#endif

int main(int argc, char *argv[])
{
#ifdef QT_DEBUG
    QDir::setCurrent("C://Projects//TenDrops//TenDrops");
#endif
    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    return a.exec();
}
