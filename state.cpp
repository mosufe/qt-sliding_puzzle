#include "resources.h"

State::State(Game *game, QState *rootstate) : QState(rootstate){
    this->btn = btn;
    this->game = game;
    this->assignProperty(btn, "pos", QPointF(x_coord, y_coord));
}

State::State(Game *game, QState *rootstate, Button *btn, int x_coord, int y_coord, int pos) : QState(rootstate){
    this->pos = pos;
    this->x_coord = x_coord;
    this->y_coord = y_coord;
    this->btn = btn;
    this->game = game;
    this->assignProperty(btn, "pos", QPointF(x_coord, y_coord));
}

void State::set_x(int new_x){
    this->x_coord = new_x;
}

void State::set_y(int new_y){
    this->y_coord = new_y;
}

void State::set_btn(Button *new_btn){
    this->btn = new_btn;
}

void State::set_pos(int new_pos){
    this->pos = new_pos;
}

int State::get_x(){
    return this->x_coord;
}

int State::get_y(){
    return this->x_coord;
}

int State::get_pos(){
    return this->pos;
}

void State::TileMoved(){


    int** temp = game->getMatrix();

     printf("\n%i ", temp[0][0]);
     printf("%i ", temp[0][1]);
     printf("%i ", temp[0][2]);
     printf("%i\n", temp[0][3]);

     printf("%i ", temp[1][0]);
     printf("%i ", temp[1][1]);
     printf("%i ", temp[1][2]);
     printf("%i\n", temp[1][3]);

     printf("%i ", temp[2][0]);
     printf("%i ", temp[2][1]);
     printf("%i ", temp[2][2]);
     printf("%i\n", temp[2][3]);

     printf("%i ", temp[3][0]);
     printf("%i ", temp[3][1]);
     printf("%i ", temp[3][2]);
     printf("%i\n", temp[3][3]);


    const char* direction = game->canMove(this->pos);
    printf("====%i=====", this->pos);
    printf("%s\n",direction);

    if (strcmp(direction, "up")){
        printf("ENTREI");
        this->y_coord = this->y_coord +130;
        this->assignProperty(this->btn, "pos" ,QPointF(this->x_coord, this->y_coord));
     }

    /*
    else if (strcmp(direction,"down"))
        this->y_coord = this->y_coord +130;
    else if (strcmp(direction,"left"))
        this->x_coord = this->x_coord -130;
    else if (strcmp(direction,"right"))
        this->x_coord = this->x_coord +130;

    printf("%s\n",direction);
    this->assignProperty(this->btn, "pos" ,QPointF(this->x_coord, this->y_coord));
    */
}
