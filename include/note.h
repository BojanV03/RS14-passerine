
#include <QGraphicsItem>
#include <QBrush>
#include <QColor>
#include <QRect>
#include <QPainter>
#include <QDebug>
#include <QGraphicsSceneWheelEvent>

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
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

    QBrush getStandardBrush() const;
    void setStandardBrush(const QBrush &value);

    MidiEvent *getOnEvent() const;
    void setOnEvent(MidiEvent *value);

    MidiEvent *getOffEvent() const;
    void setOffEvent(MidiEvent *value);
    virtual void wheelEvent(QGraphicsSceneWheelEvent * event);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
private:
    char _id;
    double _timeBegin;
    double _timeEnd;

    MidiEvent *onEvent;
    MidiEvent *offEvent;

    QBrush standardBrush;
    QRect rect;
};

#endif // NOTE_H
