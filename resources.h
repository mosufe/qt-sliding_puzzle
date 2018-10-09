#include <QtWidgets/QtWidgets>
#include <QtCore/qmath.h>
#include <QtCore/qrandom.h>
#include <QtCore/qstate.h>
#include <QObject>

#ifndef RESOURCES_H
#define RESOURCES_H

//Pixmap
//Define a imagem a ser associada ao botão
//============================================================
class Pixmap : public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
    Q_PROPERTY(QPointF pos READ pos WRITE setPos)

public:
    Pixmap(const QPixmap &pix);
};

//View
//Define a classe de visualização básica do jogo
//============================================================
class View : public QGraphicsView{

public:
    View(QGraphicsScene *scene);

protected:
    void resizeEvent(QResizeEvent *event) override;
};

//Button
//Cria uma classe botão a partir de um QGraphics Widget para facilitar implementação
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
//Classe que define as regras de jogo e suas respectivas funcionalidades
//============================================================
struct coords{
    int x;
    int y;
};

class Game : public QObject{
    Q_OBJECT

private:
    int** posicoes;
    int sentinela; //posicao relativa ao espaco em branco no quebra cabeca
    int movements;
    QTime finalTime;

public:
    Game(int blank);
    int getMovements();
    int getSentinel();
    int** getMatrix();
    bool isComplete();
    bool isSolvable();
    void shuffle();
    void semiSolved();
    void startSolvedGame();
    void swapTiles(int tile);
    coords findPosition(int number);
    char const *canMove(int number);
    QTime getFinalTime();

signals:
    void gameCompleted(int);

public slots:
    void IncrementMovement();
    void updateTime(QTime time);
};

//State
//Classe de estados que define o estado atual de cada botão
//Extende a classe base QState permitindo criação de novos campos e métodos
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
    State(Game *game, QState *rootstate, Button *btn, int x_coord, int y_coord, int pos);
    int get_x();
    int get_y();
    int get_pos();
    void set_x(int new_x);
    void set_y(int new_y);
    void set_btn(Button *new_btn);
    void set_pos(int new_pos);

signals:
    void movementCountChanged(int);
public slots:
    void TileMoved();
};

//Clock
//Define a classe de temporizador
//=================================================================================
class DigitalTimer : public QLCDNumber{
    Q_OBJECT
    QTime time;
    QTimer *timer;

public:
    DigitalTimer(uint digits);
    QTime getFinalTime();

signals:
    void getTime(QTime);

private slots:
    void showTime();
    void stopTimer();
};

//Input
//Define a tela de insercao para o nome da pessoa
//=================================================================================
class Input : public QObject{

   Q_OBJECT
   QString text;
public:
    Input();
};

//RecordWindow
//Define a janela de pontuação
//=================================================================================
class RecordWindow : public QObject{
    Q_OBJECT

public:
    struct score{
        QString name;
        float time;
        int moves;
    };

    score scoreList [20];

    QWidget recordWindow;

    void resetList ();
    void writeFile ();
    void readFile ();

public slots:
    void createWindow(int jogadas);
};
#endif // RESOURCES_H
