#include <QtWidgets/QtWidgets>
#include <QtCore/qmath.h>
#include <QtCore/qrandom.h>
#include <QtCore/qstate.h>
#include <QObject>

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
    void pressed();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *) override;

private:
    int state = 1;
    QPixmap _pix;
};

//Game
//============================================================
struct coords{
    int x;
    int y;
};

class Game{

private:
    int** posicoes;
    int sentinela; //posicao relativa ao espaco em branco no quebra cabeca

public:
    Game(int blank);
    char const *canMove(int number);
    void shuffle();
    bool estaCompleto (int matriz [4][4]);
    void trocarDois(int matriz [4][4], int linA, int colA, int linB, int colB);
    void houveTroca(int peca1, int peca2);
    int getSentinel();
    int** getMatrix();
    coords findPosition(int number);
};

//State
//============================================================

class State : public QState{
    Q_OBJECT

private:
    int pos;
    int position;
    int x_coord;
    int y_coord;
    Button *btn;
    Game *game;

public:
    State(Game *game, QState *rootstate);
    State(Game *game, QState *rootstate, Button *btn, int x_coord, int y_coord, int pos);
    int get_x();
    int get_y();
    int get_pos();
    void set_x(int new_x);
    void set_y(int new_y);
    void set_btn(Button *new_btn);
    void set_pos(int new_pos);

public slots:
    void TileMoved();

};

#endif // RESOURCES_H
