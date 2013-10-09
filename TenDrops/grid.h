//
// Module			: grid.h
// Author			: bss
// Project			: TenDrops
// State			:
// Creation Date	: 2013-10-08
// Last Modification: 2013-10-09
// Description		: A grid in board. Can contain a drop of water.
//

#ifndef GRID_H
#define GRID_H

#include <QGraphicsItem>

// 一格，静止的水珠
class Grid : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    explicit Grid(int x, int y);

    QRectF boundingRect() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void setDropSize(int size);
    int getDropSize();
    // 加一滴水
    void addDrop();

    static int getCoordX(float x);
    static int getCoordY(float y);

signals:
    // 水滴爆炸
    void burst(int x, int y);

public slots:

public:
    static const int WIDTH = 48;
    static const int MAX_DROP_SIZE = 4;
    static const int GRID_SX = 50;
    static const int GRID_SY = 40;
    static const int GRID_DX = 54;
    static const int GRID_DY = 54;

private:
    static QImage img[];
    int idX, idY;
    QRectF rect;
    int dropSize;
};

#endif // GRID_H
