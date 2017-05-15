#ifndef ANIMATIONGROUP_H
#define ANIMATIONGROUP_H

#include <QGraphicsItemGroup>
#include <QObject>

class AnimationGroup : public QObject, public QGraphicsItemGroup
{
    Q_OBJECT
    Q_PROPERTY(QPointF pos READ pos WRITE setPos)

public:
    AnimationGroup();
};

#endif // ANIMATIONGROUP_H
