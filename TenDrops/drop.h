//
// Module			: drop.h
// Author			: bss
// Project			: TenDrops
// State			:
// Creation Date	: 2013-10-09
// Last Modification: 2013-10-09
// Description		: A flying drop.
//

#ifndef DROP_H
#define DROP_H

#include <QGraphicsItem>

class drop : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    explicit drop();

signals:

public slots:

};

#endif // DROP_H
