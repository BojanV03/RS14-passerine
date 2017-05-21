#ifndef KEY_H
#define KEY_H

#include <QGraphicsItem>
#include <QBrush>
#include <QColor>
#include <QRect>
#include <QPainter>
#include <QGraphicsItem>
#include <QDebug>

class Key : public QGraphicsItem
{
public:
    Key(int midiID, QRect rect);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void pressKey();
    void releaseKey();

    bool getIsPressed() const;
    void setIsPressed(bool value);

    QBrush getStandardColor() const;
    void setStandardColor(const QBrush &value);

    QBrush getPressedColor() const;
    void setPressedColor(const QBrush &value);

    int getMidiID() const;
    void setMidiID(int value);

    QRect getRect() const;
    void setRect(const QRect &value);
    void setRect(float x, float y, float width, float height);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
private:
    bool isPressed;
    QBrush standardColor;
    QBrush pressedColor;
    QRect rect;
    int midiID;
};

#endif // KEY_H
