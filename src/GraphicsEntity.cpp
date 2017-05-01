#include <include/GraphicsEntity.h>

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

QColor GraphicsEntity::getColor() const
{
    return color;
}

float GraphicsEntity::getY() const
{
    return y;
}

void GraphicsEntity::setY(float value)
{
    y = value;
}

float GraphicsEntity::getX() const
{
    return x;
}

void GraphicsEntity::setX(float value)
{
    x = value;
}
