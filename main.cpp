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
    //Define a imagem de background
    QPixmap bgPix(":/images/Time-For-Lunch-2.jpg");
    //Define localizacao e tamanho da tela
    QGraphicsScene scene(-350, -350, 700, 750);

    //Define view e inicializa cena
    View *view = new View(&scene);
    //Define Titulo e regras de translate
    view->setWindowTitle(QT_TRANSLATE_NOOP(QGraphicsView, "Sliding Puzzle"));
    view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    //Adiciona imagem de background à view
    view->setBackgroundBrush(bgPix);
    view->setCacheMode(QGraphicsView::CacheBackground);
    view->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    view->show();

    //Cria label de jogadas e o insere em cena
    //=============================================================================
    QLabel *movementsLabel = new QLabel("Jogadas");
    movementsLabel->resize(60,20);
    movementsLabel->move(-150, 300);
    movementsLabel->setAlignment(Qt::AlignCenter);
    scene.addWidget(movementsLabel);
    //=============================================================================

    //Cria o display LCD de jogadas e o insere em tela
    //=============================================================================
    QLCDNumber *score;
    score = new QLCDNumber(3);
    score->display(0);
    score->setSegmentStyle(QLCDNumber::Filled);
    score->move(-160,320);
    score->resize(80,50);
    score->show();
    scene.addWidget(score);
    //=============================================================================

    //Cria o label de tempo e o insere em cena
    //=============================================================================
    QLabel *timeLabel = new QLabel("Tempo");
    timeLabel->resize(60,20);
    timeLabel->move(85, 300);
    timeLabel->setAlignment(Qt::AlignCenter);
    scene.addWidget(timeLabel);
    //=============================================================================

    //Inicializa o timer de jogo e define o estilo de apresentação do LCD
    //=============================================================================
    DigitalTimer *t;
    t = new DigitalTimer(5);
    t->move(40,320);
    t->resize(160,50);
    t->show();
    scene.addWidget(t);
    //=============================================================================

    //Instancia todos os botões
    //=============================================================================
    //Define botão pai
    QGraphicsItem *buttonParent = new QGraphicsRectItem;
    //Inicializa lista de botões
    QList<Button*> buttons;
    //Adiciona todos os botões a uma lista ja inicializados com sua respectiva imagem
    for(int i = 1;i <= 17;i++){
        std::stringstream ss;
        ss << ":/images/" << i << ".jpg";
        std::string s = ss.str();
        const char* file = s.c_str();
        Button* button =  new Button(QPixmap(file), buttonParent);
        buttons << button;
    }
    scene.addItem(buttonParent);
    //=============================================================================

    //Inicializa jogo
    Game *game = new Game(4);
    //Recupera a matriz que define o jogo
    int** pos = game->getMatrix();

    QWidget recordWindow;
    RecordWindow *records;
    records = new RecordWindow();
    QObject::connect(game, SIGNAL(gameCompleted(int)), records, SLOT(createWindow(int)));


    //Inicializa possiveis estados e os associa a cada botão
    //=============================================================================
    //Inicializa estado pai
    QState *rootState = new QState;
    //Inicializa listade estados
    QList<State*> statesList;
    for(int i = 0;i < 16;i++){
        State *s = new State(game, rootState, buttons.at(16),0, 0, 0);
        statesList << s;
    }
    //=============================================================================


    //Define posições iniciais de cada botão e de cada estado a ele associado de acordo com a matriz de jogo definida
    //=============================================================================
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
    //Inicializa maquina de estados e define estado inicial
    //=============================================================================
    QStateMachine states;
    states.addState(rootState);
    states.setInitialState(rootState);
    rootState->setInitialState(statesList.at(0));
    //=============================================================================

    //Esconde botão relativo à peça solta
    buttons.at(3)->hide();
    buttons.at(16)->hide();

    //Seta propriedade do botão pai e consequentemente de todos os seus filhos
    //=============================================================================
    buttonParent->setTransform(QTransform::fromScale(1.2, 1.2), true);
    buttonParent->setPos(200, 200);
    buttonParent->setZValue(1);
    //=============================================================================


    //Inicializa grupo de animação e associa animação de posicao a todos os botoes
    //=============================================================================
    QParallelAnimationGroup *group = new QParallelAnimationGroup;
    for (int i = 0; i < 16; ++i) {
        QPropertyAnimation *anim = new QPropertyAnimation(buttons.at(i), "pos");
        anim->setDuration(200 + 1 * 25);
        anim->setEasingCurve(QEasingCurve::InOutBack);
        group->addAnimation(anim);
    }
    //=============================================================================

    //Conecta o sinal de jogo completo e para a contagem do temporizador
    QObject::connect(game, SIGNAL(gameCompleted(int)), t, SLOT(stopTimer()));

    //=============================================================================
    QList<QAbstractTransition*> transformationList;
    for(int i = 0;i < 16;i++){
        //Conecta todas as mudanças de estado de cada botão e atualiza o display LCD
        QObject::connect(statesList.at(i), SIGNAL(movementCountChanged(int)), score, SLOT(display(int)));
        //Conecta todas as mudanças de estado de cada botão e incrementa 1 ao contador de jogadas do game
        QObject::connect(statesList.at(i), SIGNAL(movementCountChanged(int)),game, SLOT(IncrementMovement()));
        //Conecta o pressionamento do botão à movimentação de seu estado correspondente
        QObject::connect(buttons.at(i), SIGNAL(pressed()),statesList.at(i), SLOT(TileMoved()));
        //Adiciona animação de transição para cada botão
        transformationList << rootState->addTransition(buttons.at(i), &Button::pressed, statesList.at(i));
        //Adiciona cada transformação ao grupo de animações
        transformationList.at(i)->addAnimation(group);
    }
    //=============================================================================

    states.start();
    return app.exec();
}
