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

    //Seta posicoes iniciais dos tiles
    int count = 0;
    for(int i = 1; i <= 4; i++){
        int y_pos = -390 + (i-1)*130;
        for(int k = 1; k <= 4; k++){
            int x_pos = -310 + (k-1)*130;
            buttons.at(count)->setPos(x_pos, y_pos);
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
    QState *rootState = new QState;
    QList<QState*> statesList;
    for(int i = 0;i < 16;i++){
        QState *state = new QState(rootState);
        statesList << state;
    }
    State *st = new State(rootState, buttons.at(2), -50, -390);

    //StateChange
    //Botao a ser movido, Parametro a ser modificado, Posicao final do botao
    QStateMachine states;
    states.addState(rootState);
    states.setInitialState(rootState);
    rootState->setInitialState(st);

    QParallelAnimationGroup *group = new QParallelAnimationGroup;

    for (int i = 0; i < 3; ++i) {
        QPropertyAnimation *anim = new QPropertyAnimation(buttons.at(i), "pos");
        anim->setDuration(200 + 1 * 25);
        anim->setEasingCurve(QEasingCurve::InOutBack);
        group->addAnimation(anim);
    }

    //Define a animacao
    QObject::connect(buttons.at(2), SIGNAL(pressed(int,int)),st, SLOT(TileMoved(int,int)));
    QAbstractTransition *trans = rootState->addTransition(buttons.at(2), &Button::pressed, st);
    trans->addAnimation(group);
    
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
