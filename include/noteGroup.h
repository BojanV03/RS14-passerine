#ifndef NOTEGROUP_H
#define NOTEGROUP_H

#include <QGraphicsItem>

class noteGroup : public QGraphicsItem {
public:
    noteGroup();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;

    QRect getRect() const;
    void setRect(const QRect &value);

private:
    QRect rect;

};

#endif // NOTEGROUP_H
