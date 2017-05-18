#ifndef KEY_H
#define KEY_H

#include <QGraphicsItem>
#include <QColor>

class Key : public QGraphicsItem
{
public:
    Key(int midiID);

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

private:
    bool isPressed;
    QBrush standardColor;
    QBrush pressedColor;
    int midiID;
};

#endif // KEY_H
