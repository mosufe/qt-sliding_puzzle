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
    QGraphicsScene scene(-350, -350, 700, 700);

    View *view = new View(&scene);
    view->setWindowTitle(QT_TRANSLATE_NOOP(QGraphicsView, "Sliding Puzzle"));
    view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    view->setBackgroundBrush(bgPix);
    view->setCacheMode(QGraphicsView::CacheBackground);
    view->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    view->show();

    //Instancia todos os tiles
    QGraphicsItem *buttonParent = new QGraphicsRectItem;
    QList<Button*> buttons;
    for(int i = 1;i <= 16;i++){
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

    int count = 0;
    for(int i = 1; i <= 4; i++){
        int y_pos = -390 + (i-1)*130;
        for(int k = 1; k <= 4; k++){
            int x_pos = -310 + (k-1)*130;
            buttons.at(pos[i-1][k-1]-1)->setPos(x_pos, y_pos);
            printf("%i", pos[i-1][k-1]-1);
            State *state = new State(game, rootState, buttons.at(pos[i-1][k-1]-1), x_pos, y_pos, pos[i-1][k-1]);
            statesList << state;
            count++;
        }
    }
    buttons.at(3)->hide();
    
    scene.addItem(buttonParent);

    //Seta propriedade dos tiles
    buttonParent->setTransform(QTransform::fromScale(1.2, 1.2), true);
    buttonParent->setPos(200, 200);
    buttonParent->setZValue(1);

    // Cria 16 estados
    /*
    QState *rootState = new QState;
    QList<QState*> statesList;
    for(int i = 0;i < 16;i++){
        QState *state = new QState(rootState);
        statesList << state;
    }*/



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

    //Define a animacao
    QObject::connect(buttons.at(0), SIGNAL(pressed()),statesList.at(0), SLOT(TileMoved()));
    QAbstractTransition *trans = rootState->addTransition(buttons.at(0), &Button::pressed, statesList.at(0));

    QObject::connect(buttons.at(1), SIGNAL(pressed()),statesList.at(1), SLOT(TileMoved()));
    QAbstractTransition *trans2 = rootState->addTransition(buttons.at(1), &Button::pressed, statesList.at(1));

    QObject::connect(buttons.at(2), SIGNAL(pressed()),statesList.at(2), SLOT(TileMoved()));
    QAbstractTransition *trans3 = rootState->addTransition(buttons.at(2), &Button::pressed, statesList.at(2));

    QObject::connect(buttons.at(3), SIGNAL(pressed()),statesList.at(3), SLOT(TileMoved()));
    QAbstractTransition *trans4 = rootState->addTransition(buttons.at(3), &Button::pressed, statesList.at(3));

    QObject::connect(buttons.at(4), SIGNAL(pressed()),statesList.at(4), SLOT(TileMoved()));
    QAbstractTransition *trans5 = rootState->addTransition(buttons.at(4), &Button::pressed, statesList.at(4));

    QObject::connect(buttons.at(5), SIGNAL(pressed()),statesList.at(5), SLOT(TileMoved()));
    QAbstractTransition *trans6 = rootState->addTransition(buttons.at(5), &Button::pressed, statesList.at(5));

    QObject::connect(buttons.at(6), SIGNAL(pressed()),statesList.at(6), SLOT(TileMoved()));
    QAbstractTransition *trans7 = rootState->addTransition(buttons.at(6), &Button::pressed, statesList.at(6));

    QObject::connect(buttons.at(7), SIGNAL(pressed()),statesList.at(7), SLOT(TileMoved()));
    QAbstractTransition *trans8 = rootState->addTransition(buttons.at(7), &Button::pressed, statesList.at(7));

    QObject::connect(buttons.at(8), SIGNAL(pressed()),statesList.at(8), SLOT(TileMoved()));
    QAbstractTransition *trans9 = rootState->addTransition(buttons.at(8), &Button::pressed, statesList.at(8));

    QObject::connect(buttons.at(9), SIGNAL(pressed()),statesList.at(9), SLOT(TileMoved()));
    QAbstractTransition *trans10 = rootState->addTransition(buttons.at(9), &Button::pressed, statesList.at(9));

    QObject::connect(buttons.at(10), SIGNAL(pressed()),statesList.at(10), SLOT(TileMoved()));
    QAbstractTransition *trans11 = rootState->addTransition(buttons.at(10), &Button::pressed, statesList.at(10));

    QObject::connect(buttons.at(11), SIGNAL(pressed()),statesList.at(11), SLOT(TileMoved()));
    QAbstractTransition *trans12 = rootState->addTransition(buttons.at(11), &Button::pressed, statesList.at(11));

    QObject::connect(buttons.at(12), SIGNAL(pressed()),statesList.at(12), SLOT(TileMoved()));
    QAbstractTransition *trans13 = rootState->addTransition(buttons.at(12), &Button::pressed, statesList.at(12));

    QObject::connect(buttons.at(13), SIGNAL(pressed()),statesList.at(13), SLOT(TileMoved()));
    QAbstractTransition *trans14 = rootState->addTransition(buttons.at(13), &Button::pressed, statesList.at(13));

    QObject::connect(buttons.at(14), SIGNAL(pressed()),statesList.at(14), SLOT(TileMoved()));
    QAbstractTransition *trans15 = rootState->addTransition(buttons.at(14), &Button::pressed, statesList.at(14));

    QObject::connect(buttons.at(15), SIGNAL(pressed()),statesList.at(15), SLOT(TileMoved()));
    QAbstractTransition *trans16 = rootState->addTransition(buttons.at(15), &Button::pressed, statesList.at(15));
    trans->addAnimation(group);
    trans2->addAnimation(group);
    trans3->addAnimation(group);
    trans4->addAnimation(group);
    trans5->addAnimation(group);
    trans6->addAnimation(group);
    trans7->addAnimation(group);
    trans8->addAnimation(group);
    trans9->addAnimation(group);
    trans10->addAnimation(group);
    trans11->addAnimation(group);
    trans12->addAnimation(group);
    trans13->addAnimation(group);
    trans14->addAnimation(group);
    trans15->addAnimation(group);
    trans16->addAnimation(group);
    
    QTimer timer;
    timer.start(125);
    timer.setSingleShot(true);
    //trans = rootState->addTransition(&timer, &QTimer::timeout, statesList.at(0));
    //trans->addAnimation(group);

    states.start();

#ifdef QT_KEYPAD_NAVIGATION
    QApplication::setNavigationMode(Qt::NavigationModeCursorAuto);
#endif
    return app.exec();
}
