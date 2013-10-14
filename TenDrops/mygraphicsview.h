//
// Module			: mygraphicsview.h
// Author			: bss
// Project			: TenDrops
// State			:
// Creation Date	: 2013-10-09
// Last Modification: 2013-10-14
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
    enum class UIMode
    {
        FREE,
        MANUALRUN,
        AUTORUN,
        AUTOCALC,
        CALCOK
    };

public:
    explicit MyGraphicsView(QWidget *parent = 0);

signals:
    void setUIMode(MyGraphicsView::UIMode uiMode);
    void toNextLevel();

public slots:
    virtual void mousePressEvent(QMouseEvent *event);
    void invalidate();

    void beginManualRun();
    void endRound();
    void beginAutoRun();
    void endAutoRun();
    void beginAutoCalc();
    void calcOK();

    void onLoadMap(const char* filename);
    void onSaveMap(const char* filename);
    void onDebug(void*);
    void onSetDropsLeft(int dropNum);
    void onBFS();
    void onDFS();
    void onBeginAutoRun();
    void onSetSingleStep(bool isSingle);

    void onClose();
    QString checkThreadInfo();
    void checkThreadResult();
    void abortThread();

private:
    void initUI();

private:
    UIMode uiMode;
    GameBoard* gameboard;
    QTimer* timer;
    QGraphicsTextItem* text;
    bool isSingleStep;
};

#endif // MYGRAPHICSVIEW_H
