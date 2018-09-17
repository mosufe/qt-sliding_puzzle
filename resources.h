#include <QtWidgets/QtWidgets>
#include <QtCore/qmath.h>
#include <QtCore/qrandom.h>
#include <QtCore/qstate.h>

#ifndef RESOURCES_H
#define RESOURCES_H

//Pixmap
//============================================================
class Pixmap : public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
    Q_PROPERTY(QPointF pos READ pos WRITE setPos)

public:
    Pixmap(const QPixmap &pix);
};

//View
//============================================================
class View : public QGraphicsView{

public:
    View(QGraphicsScene *scene);

protected:
    void resizeEvent(QResizeEvent *event) override;
};

//Button
//============================================================
class Button : public QGraphicsWidget{
    Q_OBJECT

public:
    Button(const QPixmap &pixmap, QGraphicsItem *parent);
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *) override;

signals:
    void pressed(int x, int y);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *) override;

private:
    int state = 1;
    QPixmap _pix;
};
//Button
//============================================================

class State : public QState{
    Q_OBJECT
    int pos = 0;
    int position;
    int x_coord;
    int y_coord;
    Button *btn;

public:
    State(QState *rootstate, Button *btn,int x_coord, int y_coord);
    int get_x();
    int get_y();

public slots:
    void TileMoved(int new_x, int new_y);

};

#endif // RESOURCES_H
