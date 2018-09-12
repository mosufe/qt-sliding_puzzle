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

    //setar background
    QPixmap bgPix(":/images/Time-For-Lunch-2.jpg");

    //localizacao da tela
    QGraphicsScene scene(-350, -350, 700, 700);

    // Buttons
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

    int count = 0;
    for(int i = 1; i <= 4; i++){
        int y_pos = -390 + (i-1)*130;
        for(int k = 1; k <= 4; k++){
            int x_pos = -310 + (k-1)*130;
            buttons[count]->setPos(x_pos, y_pos);
            count++;
        }
    }

    scene.addItem(buttonParent);
    //Tamanho dos botoes
    buttonParent->setTransform(QTransform::fromScale(1.2, 1.2), true);
    buttonParent->setPos(200, 200);
    buttonParent->setZValue(1);

    // States
    QState *rootState = new QState;
    QState *oneState = new QState(rootState);
    QState *twoState = new QState(rootState);
    QState *threeState = new QState(rootState);
    QState *fourState = new QState(rootState);

    oneState->assignProperty(buttons[0], "pos", QPointF(-310,-390));
    twoState->assignProperty(buttons[0], "pos", QPointF(-400,-300));

    // Values
    /*
    for (int i = 0; i < items.count(); ++i) {
        Pixmap *item = items.at(i);
        // Ellipse
        oneState->assignProperty(item, "pos",
                                         QPointF(qCos((i / 63.0) * 6.28) * 250,
                                                 qSin((i / 63.0) * 6.28) * 250));

        // Figure 8
        twoState->assignProperty(item, "pos",
                                         QPointF(qSin((i / 63.0) * 6.28) * 250,
                                                 qSin(((i * 2)/63.0) * 6.28) * 250));

        // Random
        threeState->assignProperty(item, "pos",
                                        QPointF(-250 + QRandomGenerator::global()->bounded(500),
                                                -250 + QRandomGenerator::global()->bounded(500)));

        // Tiled
        fourState->assignProperty(item, "pos",
                                       QPointF(((i % 8) - 4) * kineticPix.width() + kineticPix.width() / 2,
                                               ((i / 8) - 4) * kineticPix.height() + kineticPix.height() / 2));

        // Centered
        centeredState->assignProperty(item, "pos", QPointF());
    }
    */

    // Ui
    View *view = new View(&scene);
    view->setWindowTitle(QT_TRANSLATE_NOOP(QGraphicsView, "Sliding Puzzle"));
    view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    view->setBackgroundBrush(bgPix);
    view->setCacheMode(QGraphicsView::CacheBackground);
    view->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    view->show();

    QStateMachine states;
    states.addState(rootState);
    states.setInitialState(rootState);
    rootState->setInitialState(oneState);

    QParallelAnimationGroup *group = new QParallelAnimationGroup;


    QPropertyAnimation *anim = new QPropertyAnimation(buttons[0], "pos");
    anim->setDuration(200 + 1 * 25);
    anim->setEasingCurve(QEasingCurve::InOutBack);
    group->addAnimation(anim);

    //Define a animacao
    QAbstractTransition *trans = rootState->addTransition(buttons[0], &Button::pressed, oneState);
    trans->addAnimation(group);
    //
    trans = rootState->addTransition(buttons[1], &Button::pressed, twoState);
    trans->addAnimation(group);
    QTimer timer;
    timer.start(125);
    timer.setSingleShot(true);
    trans = rootState->addTransition(&timer, &QTimer::timeout, oneState);
    trans->addAnimation(group);

    states.start();

#ifdef QT_KEYPAD_NAVIGATION
    QApplication::setNavigationMode(Qt::NavigationModeCursorAuto);
#endif
    return app.exec();
}

#include "main.moc"
