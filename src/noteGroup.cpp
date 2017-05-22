#include <include/noteGroup.h>

noteGroup::noteGroup()
{

}

QRect noteGroup::getRect() const
{
    return rect;
}

void noteGroup::setRect(const QRect &value)
{
    rect = value;
}

QRectF noteGroup::boundingRect() const
{
    return rect;
}

void noteGroup::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

}

