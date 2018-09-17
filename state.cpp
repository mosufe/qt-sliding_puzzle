#include "resources.h"

State::State(QState *rootstate, Button *btn, int x_coord, int y_coord) : QState(rootstate){
    this->x_coord = x_coord;
    this->y_coord = y_coord;
    this->btn = btn;
    this->assignProperty(btn, "pos", QPointF(x_coord, y_coord));
}

int State::get_x(){
    return this->x_coord;
}

int State::get_y(){
    return this->x_coord;
}

void State::TileMoved(int new_x, int new_y){
    if (this->pos == 1){
        this->pos = 0;
        this->x_coord = new_x -130;
        this->y_coord = new_y;
        this->assignProperty(this->btn, "pos" ,QPointF(this->x_coord, this->y_coord));
        printf("Pos é 1");
        printf("%i, %i\n",this->x_coord, this->y_coord);
    }
    else{
        this->pos = 1;
        this->x_coord = new_x;
        this->y_coord = new_y;
        this->assignProperty(this->btn, "pos" ,QPointF(this->x_coord, this->y_coord));
        printf("Pos é 0");
        printf("%i, %i\n",this->x_coord, this->y_coord);
    }

}
