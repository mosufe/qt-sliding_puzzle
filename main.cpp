#include <QtWidgets/QtWidgets>
#include <QtCore/qmath.h>
#include <QtCore/qrandom.h>
#include <QtCore/qstate.h>
#include <sstream>

#include "resources.h"

int main(int argc, char **argv)
{
   Q_INIT_RESOURCE(slidingpuzzle);

    QApplication app(argc, argv);

    QPixmap kineticPix(":/images/centered.png");

    //Setar imagem de background
    QPixmap bgPix(":/images/Time-For-Lunch-2.jpg");

    //Localizacao e tamanho da tela
    QGraphicsScene scene(-350, -350, 700, 750);

    View *view = new View(&scene);
    view->setWindowTitle(QT_TRANSLATE_NOOP(QGraphicsView, "Sliding Puzzle"));
    view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    view->setBackgroundBrush(bgPix);
    view->setCacheMode(QGraphicsView::CacheBackground);
    view->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    view->show();

    QLCDNumber *score;
    score = new QLCDNumber(3);
    score->display(0);
    score->setSegmentStyle(QLCDNumber::Filled);
    score->move(-270,320);
    score->resize(80,50);
    score->show();

    DigitalTimer *t;
    t = new DigitalTimer(5);
    t->move(155,320);
    t->resize(160,50);
    t->show();

    QLabel *movementsLabel = new QLabel("Jogadas");
    movementsLabel->resize(60,20);
    movementsLabel->move(-260, 300);
    movementsLabel->setAlignment(Qt::AlignCenter);

    QLabel *timeLabel = new QLabel("Tempo");
    timeLabel->resize(60,20);
    timeLabel->move(205, 300);
    timeLabel->setAlignment(Qt::AlignCenter);

    //Instancia todos os tiles
    QGraphicsItem *buttonParent = new QGraphicsRectItem;
    QList<Button*> buttons;
    for(int i = 1;i <= 17;i++){
        std::stringstream ss;
        ss << ":/images/" << i << ".jpg";
        std::string s = ss.str();
        const char* file = s.c_str();
        Button* button =  new Button(QPixmap(file), buttonParent);
        buttons << button;
    }

    Game *game = new Game(4);
    int** pos = game->getMatrix();

    QState *rootState = new QState;
    QList<State*> statesList;
    for(int i = 0;i < 16;i++){
        State *s = new State(game, rootState, buttons.at(16),0, 0, 0);
        statesList << s;
    }

    int count = 0;
    for(int i = 1; i <= 4; i++){
        int y_pos = -390 + (i-1)*130;
        for(int k = 1; k <= 4; k++){
            int x_pos = -310 + (k-1)*130;
            buttons.at(pos[i-1][k-1]-1)->setPos(x_pos, y_pos);
            statesList.at(pos[i-1][k-1]-1)->set_x(x_pos);
            statesList.at(pos[i-1][k-1]-1)->set_y(y_pos);
            statesList.at(pos[i-1][k-1]-1)->set_btn(buttons.at(pos[i-1][k-1]-1));
            statesList.at(pos[i-1][k-1]-1)->set_pos(pos[i-1][k-1]);
            count++;
        }
    }

    buttons.at(3)->hide();
    buttons.at(16)->hide();
    
    scene.addItem(buttonParent);
    scene.addWidget(score);
    scene.addWidget(movementsLabel);
    scene.addWidget(timeLabel);
    scene.addWidget(t);

    //Seta propriedade dos tiles
    buttonParent->setTransform(QTransform::fromScale(1.2, 1.2), true);
    buttonParent->setPos(200, 200);
    buttonParent->setZValue(1);

    //StateChange
    //Botao a ser movido, Parametro a ser modificado, Posicao final do botao
    QStateMachine states;
    states.addState(rootState);
    states.setInitialState(rootState);
    rootState->setInitialState(statesList.at(0));

    QParallelAnimationGroup *group = new QParallelAnimationGroup;

    for (int i = 0; i < 16; ++i) {
        QPropertyAnimation *anim = new QPropertyAnimation(buttons.at(i), "pos");
        anim->setDuration(200 + 1 * 25);
        anim->setEasingCurve(QEasingCurve::InOutBack);
        group->addAnimation(anim);
    }


    QList<QAbstractTransition*> transformationList;
    for(int i = 0;i < 16;i++){
        QObject::connect(statesList.at(i), SIGNAL(movementCountChanged(int)), score, SLOT(display(int)));
        QObject::connect(statesList.at(i), SIGNAL(movementCountChanged(int)),game, SLOT(IncrementMovement()));
        QObject::connect(buttons.at(i), SIGNAL(pressed()),statesList.at(i), SLOT(TileMoved()));
        transformationList << rootState->addTransition(buttons.at(i), &Button::pressed, statesList.at(i));
        transformationList.at(i)->addAnimation(group);
    }
    states.start();
    return app.exec();
}
