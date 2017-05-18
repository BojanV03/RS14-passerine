#include <include/Key.h>
#include <QPainter>
#include <QGraphicsItem>

Key::Key()
{

}

QRectF Key::boundingRect() const
{
    return QRectF(0, 0, 100, 100);
}

void Key::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rect = boundingRect();

    if(isPressed)
    {
        painter->fillRect(rect, pressedColor);
    }
    else
    {
        painter->fillRect(rect, standardColor);
    }

}

void Key::pressKey()
{

}

void Key::releaseKey()
{

}

bool Key::getIsPressed() const
{
    return isPressed;
}

void Key::setIsPressed(bool value)
{
    isPressed = value;
}

QBrush Key::getStandardColor() const
{
    return standardColor;
}

void Key::setStandardColor(const QBrush &value)
{
    standardColor = value;
}

QBrush Key::getPressedColor() const
{
    return pressedColor;
}

void Key::setPressedColor(const QBrush &value)
{
    pressedColor = value;
}

int Key::getMidiID() const
{
    return midiID;
}

void Key::setMidiID(int value)
{
    midiID = value;
}
