#include "resources.h"

//State::State(Game *game, QState *rootstate) : QState(rootstate){
//    this->btn = btn;
//    this->game = game;
//    this->assignProperty(btn, "pos", QPointF(x_coord, y_coord));
//}


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
    this->assignProperty(btn, "pos", QPointF(this->x_coord, this->y_coord));
}

void State::set_y(int new_y){
    this->y_coord = new_y;
    this->assignProperty(btn, "pos", QPointF(this->x_coord, this->y_coord));
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

/*
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
*/

    const char* direction = game->canMove(this->pos);

    if (strcmp(direction, "up") == 0){
        this->y_coord = this->y_coord -130;
        game->swapTiles(this->pos);
        this->assignProperty(this->btn, "pos" ,QPointF(this->x_coord, this->y_coord));
    }
    else if (strcmp(direction,"down") == 0){
        this->y_coord = this->y_coord +130;
        game->swapTiles(this->pos);
        this->assignProperty(this->btn, "pos" ,QPointF(this->x_coord, this->y_coord));
    }
    else if (strcmp(direction,"left") == 0){
        this->x_coord = this->x_coord -130;
        game->swapTiles(this->pos);
        this->assignProperty(this->btn, "pos" ,QPointF(this->x_coord, this->y_coord));
    }
    else if (strcmp(direction,"right") == 0){
        this->x_coord = this->x_coord +130;
        game->swapTiles(this->pos);
        this->assignProperty(this->btn, "pos" ,QPointF(this->x_coord, this->y_coord));
    }
}
