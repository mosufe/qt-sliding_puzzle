#include "resources.h"

Button::Button(const QPixmap &pixmap, QGraphicsItem *parent = 0): QGraphicsWidget(parent), _pix(pixmap){
    setAcceptHoverEvents(true);
    setCacheMode(DeviceCoordinateCache);
}

QRectF Button::boundingRect() const{
    //Posicao da foto do botao
    return QRectF(-115, -65, 130, 130);
}

QPainterPath Button::shape() const{
    QPainterPath path;
    path.addRect(boundingRect());
    return path;
}

void Button::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *){
    bool down = option->state & QStyle::State_Sunken;
    QRectF r = boundingRect();

    //Tipo de desenho
    painter->drawRect(r);
    if (down)
        painter->translate(2, 2);
    painter->drawPixmap(-115, -65, 130, 130, _pix);
}

void Button::mousePressEvent(QGraphicsSceneMouseEvent *){
    //Aqui deve ser emitido o sinal para a nova pos
    emit pressed();
    update();
}

void Button::mouseReleaseEvent(QGraphicsSceneMouseEvent *){
    update();
}
