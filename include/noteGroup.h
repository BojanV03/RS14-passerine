#ifndef NOTEGROUP_H
#define NOTEGROUP_H

#include <QGraphicsItem>
#include <include/note.h>
#include <include/SongPlayer.h>
#include <QGraphicsSceneMouseEvent>

class noteGroup : public QGraphicsItem {
public:
    noteGroup();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;

    QRect getRect() const;
    void setRect(const QRect &value);
    void addToGroup(Note *n);

    SongPlayer *getPlayerRef() const;
    void setPlayerRef(SongPlayer *value);

    int getPianoTopKey() const;
    void setPianoTopKey(int value);

    int getPianoBottomKey() const;
    void setPianoBottomKey(int value);

    int getNumOfWhiteNotes() const;
    void setNumOfWhiteNotes(int value);

    int calculateNoteIdFromLocation(QPointF location);
    float getWidthCoef() const;
    void setWidthCoef(float value);

    bool isWhiteNote(int i);
    int countNumberOfWhiteNotesInRange(int _startNote, int _endNote);

    float getStartX() const;
    void setStartX(float value);


    float getSceneWidth() const;
    void setSceneWidth(float value);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    QRect rect;
    int pianoTopKey;
    int pianoBottomKey;
    int numOfWhiteNotes;
    float widthCoef;
    SongPlayer *playerRef;
    float sceneWidth;

    float startX;
    float startY = 0;
};

#endif // NOTEGROUP_H
