#include "GraphicsEntity.h"

GraphicsEntity::GraphicsEntity(float _x, float _y, QColor _color):
    x(_x), y(_y), color(_color)
{
}

void GraphicsEntity::drawAt(float _x, float _y)
{
    x = _x;
    y = _y;
    setPos(x, y);
}

float GraphicsEntity::getX() const
{
    return x;
}

void GraphicsEntity::setX(float value)
{
    x = value;
}

float GraphicsEntity::getY() const
{
    return y;
}

void GraphicsEntity::setY(float value)
{
    y = value;
}

QColor GraphicsEntity::getColor() const
{
    return color;
}

void GraphicsEntity::setColor(const QColor &value)
{
    color = value;
}
