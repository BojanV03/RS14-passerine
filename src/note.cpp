#include <include/note.h>
#include <include/passerine.h>

Note::Note(char n, double tb, double te)
    :_id(n), _timeBegin(tb), _timeEnd(te)
{
    setFlag(ItemIsMovable);
}

QRectF Note::boundingRect() const
{
    return rect;
}

void Note::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    QPen p = QPen(Qt::white);
    p.setWidth(3);
    painter->setPen(p);
    standardBrush.setColor(Qt::darkGreen);
    standardBrush.setStyle(Qt::SolidPattern);
    painter->fillRect(rect, standardBrush);
    painter->drawRect(rect);
}

char Note::getId() const
{
    return _id;
}

void Note::setId(char n)
{
    _id = n;
}

double Note::getTimeBegin() const
{
    return _timeBegin;
}

void Note::setTimeBegin(double t)
{
    _timeBegin = t;
}

double Note::getTimeEnd() const
{
    return _timeEnd;
}

void Note::setTimeEnd(double t)
{
    _timeEnd = t;
}

QRect Note::getRect() const
{
    return rect;
}

void Note::setRect(const QRect &value)
{
    rect = value;
    update();
}

void Note::setRect(float x, float y, float width, float height)
{
    rect = QRect(x, y, width, height);
    update();
}

QBrush Note::getStandardBrush() const
{
    return standardBrush;
}

void Note::setStandardBrush(const QBrush &value)
{
    standardBrush = value;
}

