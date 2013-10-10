//
// Module			: drop.h
// Author			: bss
// Project			: TenDrops
// State			:
// Creation Date	: 2013-10-09
// Last Modification: 2013-10-10
// Description		: A flying drop.
//

#ifndef DROP_H
#define DROP_H

#include <QGraphicsItem>

class Drop : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    enum class DropFrom
    {
        NORTH = 0,
        SOUTH = 1,
        WEST = 2,
        EAST = 3
    };

    explicit Drop(DropFrom dropFrom, int x, int y);

    QRectF boundingRect() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    int x();
    int y();
    void step();

    bool isDead();

signals:

public slots:

private:
    static const int WIDTH = 48;
    static const int GRID_SX = 50;
    static const int GRID_SY = 40;
    static const int GRID_DX = 54;
    static const int GRID_DY = 54;
    static const float ROT[];

    DropFrom dropFrom;
    QImage img;
    QRectF rect;
    int idX, idY;
    bool isDead_;
    bool isNew_;
};

#endif // DROP_H
