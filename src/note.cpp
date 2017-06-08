#include <include/note.h>

Note::Note(char n, double tb, double te, int ch)
    :_id(n), _timeBegin(tb), _timeEnd(te), _channelId(ch)
{
    setFlag(ItemIsMovable);
    setFlag(ItemSendsGeometryChanges);
}

Note::~Note()
{
    this->hide();
}

Note::Note(char n, double tb, double te)
    :_id(n), _timeBegin(tb), _timeEnd(te)
{
    setFlag(ItemIsMovable);
    setFlag(ItemSendsGeometryChanges);
}

QRectF Note::boundingRect() const
{
    return rect;
}

// Dragovanje nota
QVariant Note::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == ItemPositionChange)
    {
        float difference = pos().x() - value.toPointF().x();

        onEvent->seconds = onEvent->seconds - difference/200;   // postavljanje vremena za ON/OFF signale
        onEvent->tick = song->getAbsoluteTickTime(onEvent->seconds);
        offEvent->seconds= offEvent->seconds- difference/200;
        offEvent->tick = song->getAbsoluteTickTime(offEvent->seconds);
        _timeBegin = onEvent->seconds;
        _timeEnd = offEvent->seconds;

        qDebug() << "OffEvent->tick = " << offEvent->tick;
        return QPointF(value.toPointF().x(), pos().y());
    }
    return QGraphicsItem::itemChange( change, value );
}

void Note::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    vector<QColor> colors = {"#800000", "#000080", "#000000", "#0000ff",
                             "#00ffff", "#008080", "#808080", "#008000",
                             "#800080", "#808000", "#a0a0a4", "#00ff00",
                             "#c0c0c0", "#ff00ff", "#ff0000", "#ffff00"};

    QPen p = QPen(Qt::black);
    p.setWidth(1);
    painter->setPen(p);
    standardBrush.setColor(colors[_channelId]);
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
// Brisanje nota
void Note::mousePressEvent(QGraphicsSceneMouseEvent *e)
{
    if(e->button() == Qt::RightButton)
    {
        onEvent->seconds = -1;
        offEvent->seconds = 0;
        offEvent->tick = song->getAbsoluteTickTime(offEvent->seconds);
        onEvent->tick = song->getAbsoluteTickTime(offEvent->seconds);
        _timeBegin = offEvent->seconds;
        _timeEnd = offEvent->seconds;
        song->sortTracks();
        setRect(QRect(-100, -100, 0.01, 0.01));
    }
}

void Note::mouseReleaseEvent(QGraphicsSceneMouseEvent *)
{
    song->sortTracks();
}
int Note::getChannelId() const
{
    return _channelId;
}

void Note::setChannelId(int channelId)
{
    _channelId = channelId;
}


MidiFile *Note::getSong()
{
    return song;
}

void Note::setSong(MidiFile *value)
{
    song = value;
}

MidiEvent *Note::getOffEvent() const
{
    return offEvent;
}

void Note::setOffEvent(MidiEvent *value)
{
    offEvent = value;
}

// Resizeovanje nota
void Note::wheelEvent(QGraphicsSceneWheelEvent *event)
{
    if(offEvent->seconds + (event->delta()/12)/200.0 < onEvent->seconds) // Ako skrolom dovedemo notu do negativne duzine
    {
        offEvent->seconds = onEvent->seconds + 0.05;                    // stavimo joj duzinu na 0.01s
        setRect(QRect(rect.left(), rect.top(), 0.05*200, rect.height()));
        offEvent->tick = song->getAbsoluteTickTime(offEvent->seconds);
        _timeEnd = offEvent->seconds;
    }
    else
    {
        offEvent->seconds = offEvent->seconds + (event->delta()/12)/200.0;
        setRect(QRect(rect.left(), rect.top(), rect.width()+event->delta()/12, rect.height()));
        offEvent->tick = song->getAbsoluteTickTime(offEvent->seconds);
        _timeEnd = offEvent->seconds;
    }
    song->sortTracks();
}
MidiEvent *Note::getOnEvent() const
{
    return onEvent;
}

void Note::setOnEvent(MidiEvent *value)
{
    onEvent = value;
}

