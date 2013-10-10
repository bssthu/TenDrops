//
// Module			: mygraphicsview.h
// Author			: bss
// Project			: TenDrops
// State			:
// Creation Date	: 2013-10-09
// Last Modification: 2013-10-10
// Description		: My QGraphicsView.
//

#ifndef MYGRAPHICSVIEW_H
#define MYGRAPHICSVIEW_H

#include <QGraphicsView>

class GameBoard;

class MyGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit MyGraphicsView(QWidget *parent = 0);

signals:
    void clicked(const QPointF* point);

public slots:
    virtual void mousePressEvent(QMouseEvent *event);
    void invalidate();

    void beginManualRun();
    void endRound();
    void beginAutoRun();
    void endAutoRun();

private:
    void initUI();

private:
    enum class UIMode
    {
        FREE,
        MANUALRUN,
        AUTORUN
    };
    UIMode uiMode;
    GameBoard* gameboard;
    QTimer* timer;
};

#endif // MYGRAPHICSVIEW_H
