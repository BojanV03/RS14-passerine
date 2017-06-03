#include <include/noteGroup.h>

NoteGroup::NoteGroup()
{
    NoteGroup::setZValue(-1000);
}

QRect NoteGroup::getRect() const
{
    return rect;
}

void NoteGroup::setRect(const QRect &value)
{
    rect = value;
    update();
}

void NoteGroup::addToGroup(Note * n)
{
    n->setParentItem(this);
    n->show();
}

void NoteGroup::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF clickLocation = event->pos();
    qreal x = clickLocation.rx() + this->x() - startX;    // podesavamo X tako da uvek pocetak bude na kraju dirki klavira

    int i = calculateNoteIdFromLocation(QPointF(x, clickLocation.ry()));
    Note * n = playerRef->addNote(i + 12, playerRef->getCurrentTime() + x/widthCoef, 1);

    float height = 1.0 * rect.height()/numOfWhiteNotes;
    float width = 1.0 * widthCoef;

    if(isWhiteNote(n->getId()))
    {
        addToGroup(n);
        n->setRect(n->getTimeBegin() * widthCoef, countNumberOfWhiteNotesInRange(0, n->getId()-12) * height, width, height);
    }
    else
    {
        addToGroup(n);
        n->setRect(n->getTimeBegin() * widthCoef, countNumberOfWhiteNotesInRange(0, n->getId()-12) * height -  (height/1.5)/2, width, height/1.5);
    }

    qDebug() << playerRef->getSong()->getTotalTimeInSeconds();
}

//void NoteGroup::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
//{

//}

float NoteGroup::getSceneWidth() const
{
    return sceneWidth;
}

void NoteGroup::setSceneWidth(float value)
{
    sceneWidth = value;
}

float NoteGroup::getStartX() const
{
    return startX;
}

void NoteGroup::setStartX(float value)
{
    startX = value;
}

float NoteGroup::getWidthCoef() const
{
    return widthCoef;
}

void NoteGroup::setWidthCoef(float value)
{
    widthCoef = value;
}

bool NoteGroup::isWhiteNote(int i)
{
    int note = i % 12;
    if(note == 0 || note == 2 || note == 4 || note == 5 || note == 7 || note == 9 || note == 11)
        return true;
    return false;
}

int NoteGroup::countNumberOfWhiteNotesInRange(int _startNote, int _endNote)
{
    int _whiteNotesInRange = 0;
    for(int i = _startNote; i < _endNote; i++)
    {
        int note = i % 12;
        if(isWhiteNote(note))
            _whiteNotesInRange++;
    }
    return _whiteNotesInRange;
}

int NoteGroup::getNumOfWhiteNotes() const
{
    return numOfWhiteNotes;
}

void NoteGroup::setNumOfWhiteNotes(int value)
{
    numOfWhiteNotes = value;
}


int NoteGroup::getPianoBottomKey() const
{
    return pianoBottomKey;
}

void NoteGroup::setPianoBottomKey(int value)
{
    pianoBottomKey = value;
}

int NoteGroup::getPianoTopKey() const
{
    return pianoTopKey;
}

void NoteGroup::setPianoTopKey(int value)
{
    pianoTopKey = value;
}

SongPlayer *NoteGroup::getPlayerRef() const
{
    return playerRef;
}

void NoteGroup::setPlayerRef(SongPlayer *value)
{
    playerRef = value;
}

QRectF NoteGroup::boundingRect() const
{
    return rect;
}

void NoteGroup::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    QPen p = QPen(Qt::black);
    QBrush standardBrush = QBrush();
    p.setWidth(1);
    painter->setPen(p);
    standardBrush.setColor("#dddddd");
    standardBrush.setStyle(Qt::SolidPattern);
    painter->fillRect(rect, standardBrush);
    painter->drawRect(rect);

    float whiteNoteHeight = 1.0*rect.height()/numOfWhiteNotes;
    float y = 0;
    for(int i = 0; i <= pianoBottomKey-pianoTopKey; i++)
    {
        int note = i % 12;
        if(note == 0 || note == 4)  // Crtamo samo za C i F bele note
        {
            painter->drawLine(QPointF(0, y), QPointF(rect.width(), y));
            y += whiteNoteHeight;
        }
        else if(note == 1 || note == 3 || note == 6 || note == 8 || note == 10)
        {
            float height = whiteNoteHeight / 1.5;
            painter->drawLine(QPointF(0, y - height/2), QPointF(rect.width(), y - height/2));
            painter->drawLine(QPointF(0, y + height/2), QPointF(rect.width(), y + height/2));
            y += whiteNoteHeight;
        }
    }
    rect.setWidth(playerRef->getSong()->getTotalTimeInSeconds()*widthCoef + 5*sceneWidth/6);

    update();
//    qDebug() << "Rect is: " << rect.topLeft() << ": " << rect.bottomRight();
}

/*
 * Vraca id pritisnute note na izracunatu na osnovu lokacije klika
 * Radi to tako sto prolazi kroz Ymin i Ymax koordinate svake dirke dok ne udje u opseg kome pripada kliknuta koordinata
 * Crne dirke moraju da imaju prioritet da bi uopste bile kliktave pa ukoliko nadjeni opseg pripada crnoj dirki, odma vracamo tu vrednost
 * Ako pripada beloj dirki, setujemo privremeni rezultat na vrednost dirke i nastavimo da prolazimo kroz niz jer postoji sansa
 * da postoji preklapanje sa crnom dirkom.
 */
int NoteGroup::calculateNoteIdFromLocation(QPointF location)
{
    float targetY = location.ry();

    float whiteNoteHeight = 1.0*rect.height()/numOfWhiteNotes;
    float y = 0;
    int result = 0;
    for(int i = 0; i <= pianoBottomKey-pianoTopKey; i++)
    {
        int note = i % 12;
        if(note == 1 || note == 3 || note == 6 || note == 8 || note == 10)
        {
            float height = whiteNoteHeight / 1.5;

            if(targetY >= y-height/2 && targetY <= y+height/2)    //naisli smo na crnu dirku, strava, vracamo rezultat
            {
                qDebug() << i;
                result = i;
                return result;
            }
        }
        else
        {
            if(targetY >= y && targetY <= y + whiteNoteHeight) // naisli smo na belu, setujemo privremeni rezultat i idemo dalje.
            {
                qDebug() << i;
                result = i;
            }
            y += whiteNoteHeight;

        }
    }
    return result;
}


