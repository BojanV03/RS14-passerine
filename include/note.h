
#include <QGraphicsItem>
#include <QBrush>
#include <QColor>
#include <QRect>
#include <QPainter>
#include <QGraphicsItem>
#include <QDebug>

#include <include/MidiFile.h>
#ifndef NOTE_H
#define NOTE_H

class Note : public QGraphicsItem
{
public:
    Note(char n, double tb, double te);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    char getId() const;
    void setId(char n);
    double getTimeBegin() const;
    void setTimeBegin(double t);
    double getTimeEnd() const;
    void setTimeEnd(double t);

    QRect getRect() const;
    void setRect(const QRect &value);
    void setRect(float x, float y, float width, float height);

    QBrush getStandardBrush() const;
    void setStandardBrush(const QBrush &value);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
private:
    char _id;
    double _timeBegin;
    double _timeEnd;


    QBrush standardBrush;
    QRect rect;
};

#endif // NOTE_H
