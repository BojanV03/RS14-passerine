#include <include/Key.h>

Key::Key(int midiID, QRect _rect)
{
    int note = midiID % 12;

    if(note == 0 || note == 2 || note == 4 || note == 5 || note == 7 || note == 9 || note == 11)
        standardColor.setColor(Qt::white);
    else
        standardColor.setColor(Qt::black);

    pressedColor.setColor(Qt::gray);

    pressedColor.setStyle(Qt::SolidPattern);
    standardColor.setStyle(Qt::SolidPattern);

    rect = _rect;
}

QRectF Key::boundingRect() const
{
    return rect;
}

void Key::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    if(painter == nullptr)
        return;
    if(isPressed)
    {
        painter->setBrush(pressedColor);
        painter->setBackground(pressedColor);
        painter->fillRect(rect, pressedColor);
 //       qDebug() << "Filled with Pressed";
    }
    else
    {
        painter->setBrush(standardColor);
        painter->setBackground(standardColor);
        painter->fillRect(rect, standardColor);
 //       qDebug() << "Filled with Standard";
    }
    painter->drawRect(rect);
}

void Key::pressKey()
{
    isPressed = true;
    update();
}

void Key::releaseKey()
{
    isPressed = false;
    update();
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

QRect Key::getRect() const
{
    return rect;
}

void Key::setRect(const QRect &value)
{
    rect = value;
}

void Key::setRect(float x, float y, float width, float height)
{
    rect = QRect(x, y, width, height);
}

void Key::mousePressEvent(QGraphicsSceneMouseEvent *)
{
    isPressed = true;
    vector<unsigned char> message;
    message.push_back( 0xCF );
    message.push_back( 0 );
    outputPort->sendMessage(&message);

    message[0] = 0xF1;  // System common- undefined?
    message[1] = 60;
    outputPort->sendMessage( &message );

    message[0] = 0xBF;
    message[1] = 0x07;
    message.push_back(100);
    outputPort->sendMessage(&message);

    message[0] = 0x9F;
    message[1] = midiID;
    message[2] = 60;
    outputPort->sendMessage(&message);

    update();
}

void Key::mouseReleaseEvent(QGraphicsSceneMouseEvent *)
{
    isPressed = false;
    vector<unsigned char> message;
    message.push_back(0x8F);
    message.push_back(midiID);
    message.push_back(60);
    outputPort->sendMessage(&message);

    update();
}

RtMidiOut *Key::getOutputPort() const
{
    return outputPort;
}

void Key::setOutputPort(RtMidiOut *value)
{
    outputPort = value;
}
