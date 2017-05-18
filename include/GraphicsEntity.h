#ifndef OCTAVE_H
#define OCTAVE_H


class GraphicsEntity: public QGraphicsItem
{
public:
    GraphicsEntity(float x, float y, const QColor color);

    void drawAt(float x, float y);
    void setColor(const QColor newColor);

    QColor getColor() const;

    float getY() const;
    void setY(float value);

    float getX() const;
    void setX(float value);

protected:
    float x;
    float y;
    QColor color;
};

#endif // OCTAVE_H
