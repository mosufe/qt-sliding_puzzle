#include <QtWidgets/QtWidgets>
#include <QtCore/qmath.h>
#include <QtCore/qrandom.h>
#include <QtCore/qstate.h>

class Pixmap : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(QPointF pos READ pos WRITE setPos)
public:
    Pixmap(const QPixmap &pix)
        : QObject(), QGraphicsPixmapItem(pix)
    {
        setCacheMode(DeviceCoordinateCache);
    }
};

class Button : public QGraphicsWidget
{
    Q_OBJECT
public:
    Button(const QPixmap &pixmap, QGraphicsItem *parent = 0): QGraphicsWidget(parent), _pix(pixmap)
    {
        setAcceptHoverEvents(true);
        setCacheMode(DeviceCoordinateCache);
    }

    QRectF boundingRect() const override
    {
        //Posicao da foto do botao
        return QRectF(-115, -65, 130, 130);
    }

    QPainterPath shape() const override
    {
        QPainterPath path;
        path.addRect(boundingRect());
        return path;
    }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *) override
    {
        bool down = option->state & QStyle::State_Sunken;
        QRectF r = boundingRect();

        //Tipo de desenho
        painter->drawRect(r);
        if (down)
            painter->translate(2, 2);
        painter->drawPixmap(-115, -65, 130, 130, _pix);
    }

signals:
    void pressed();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *) override
    {
        emit pressed();
        update();
    }

    void mouseReleaseEvent(QGraphicsSceneMouseEvent *) override
    {
        update();
    }

private:
    QPixmap _pix;
};

class View : public QGraphicsView
{
public:
    View(QGraphicsScene *scene) : QGraphicsView(scene) { }

protected:
    void resizeEvent(QResizeEvent *event) override
    {
        QGraphicsView::resizeEvent(event);
        fitInView(sceneRect(), Qt::KeepAspectRatio);
    }
};

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


    Button *one = new Button(QPixmap(":/images/1.jpg"), buttonParent);
    Button *two = new Button(QPixmap(":/images/2.jpg"), buttonParent);
    Button *three = new Button(QPixmap(":/images/3.jpg"), buttonParent);
    //Button *four = new Button(QPixmap(":/images/4.jpg"), buttonParent);

    Button *five = new Button(QPixmap(":/images/5.jpg"), buttonParent);
    Button *six = new Button(QPixmap(":/images/6.jpg"), buttonParent);
    Button *seven = new Button(QPixmap(":/images/7.jpg"), buttonParent);
    Button *eight = new Button(QPixmap(":/images/8.jpg"), buttonParent);

    Button *nine = new Button(QPixmap(":/images/9.jpg"), buttonParent);
    Button *ten = new Button(QPixmap(":/images/10.jpg"), buttonParent);
    Button *eleven = new Button(QPixmap(":/images/11.jpg"), buttonParent);
    Button *twelve = new Button(QPixmap(":/images/12.jpg"), buttonParent);

    Button *thirteen = new Button(QPixmap(":/images/13.jpg"), buttonParent);
    Button *fourteen = new Button(QPixmap(":/images/14.jpg"), buttonParent);
    Button *fifteen = new Button(QPixmap(":/images/15.jpg"), buttonParent);
    Button *sixteen = new Button(QPixmap(":/images/16.jpg"), buttonParent);

    //First row
    one->setPos(-310, -390);
    two->setPos(-180, -390);
    three->setPos(-50, -390);
    //four->setPos(80, -390);

    //Second row
    five->setPos(-310, -260);
    six->setPos(-180, -260);
    seven->setPos(-50, -260);
    eight->setPos(80, -260);

    //Third row
    nine->setPos(-310, -130);
    ten->setPos(-180, -130);
    eleven->setPos(-50, -130);
    twelve->setPos(80, -130);

    //Fourth row
    thirteen->setPos(-310, 0);
    fourteen->setPos(-180, 0);
    fifteen->setPos(-50, 0);
    sixteen->setPos(80, 0);

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

    oneState->assignProperty(one, "pos", QPointF(-310,-390));
    twoState->assignProperty(one, "pos", QPointF(-400,-300));

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
    view->setWindowTitle(QT_TRANSLATE_NOOP(QGraphicsView, "Animated Tiles"));
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

    QPropertyAnimation *anim = new QPropertyAnimation(one, "pos");
    anim->setDuration(200 + 1 * 25);
    anim->setEasingCurve(QEasingCurve::InOutBack);
    group->addAnimation(anim);

    //Define a animacao
    QAbstractTransition *trans = rootState->addTransition(one, &Button::pressed, oneState);
    trans->addAnimation(group);

    //
    trans = rootState->addTransition(two, &Button::pressed, twoState);
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
