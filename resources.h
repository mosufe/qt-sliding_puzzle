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
class Button : public QGraphicsWidget
{
    Q_OBJECT

public:
    Button(const QPixmap &pixmap, QGraphicsItem *parent);
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *) override;

signals:
    void pressed();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *) override;

private:
    QPixmap _pix;
};
#endif // RESOURCES_H
