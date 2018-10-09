#include "resources.h"
#include <cstdlib>
#include <stdio.h>
#include <time.h>
#include <unordered_set>


Game::Game(int blank)
{
    startSolvedGame();
    this->sentinela = blank;
    this->movements = 0;

    shuffle();
    while(isSolvable() == 0)
        shuffle();
    //semiSolved();
}

void Game::startSolvedGame(){
    this->posicoes = new int*[4];
    for(int i = 0;i < 4;i++)
        posicoes[i] = new int[4];

    int n = 1;
    for(int i = 0;i < 4;i++){
        for(int j = 0;j < 4;j++){
            this->posicoes[i][j] = n;
            n++;
        }
    }
}
void Game::semiSolved(){
    this->posicoes[0][3] = 3;
    this->posicoes[0][2] = 4;
}

char const *Game::canMove(int number){
    coords r = findPosition(number);
    int linha = r.x;
    int coluna = r.y;
    int n = sentinela; // tratar n como see a matriz fosse transformada em uma linha so

    if(coluna > 0) if (posicoes[linha][coluna-1] == sentinela){
        return "left";
    }
    if(coluna < 3) if (posicoes[linha][coluna+1] == sentinela){
       return "right";
    }
    if(linha > 0) if (posicoes[linha-1][coluna] == sentinela){
       return "up";
    }
    if(linha < 3) if (posicoes[linha+1][coluna] == sentinela){
       return "down";
    }

    return "none";
}

void Game::swapTiles(int tile){
    coords gap = findPosition(this->sentinela);
    coords piece = findPosition(tile);

    this->posicoes[gap.x][gap.y] = tile;
    this->posicoes[piece.x][piece.y] = this->sentinela;
}


void Game::shuffle(){
    srand(time(NULL));
    std::unordered_set<int> numbers;
    int aux_vec[15];

    while(numbers.size() <= 15){
        numbers.insert(rand() % 16 + 1);
    }

    int i = 0;
    for (const int &number : numbers){
        aux_vec[i] = number;
        i++;
    }

    int k = 0;
    for(int i = 0; i < 4;i++){
        for(int j = 0;j < 4; j++){
            posicoes[i][j] = aux_vec[k];
            k++;
        }
    }
}

bool Game::isComplete (){
    int pecaSequencial = 1;
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            if(this->posicoes[i][j] != pecaSequencial)
                return false;
            pecaSequencial++;
        }
    }
    emit gameCompleted(this->movements);
    return true;
}

bool Game::isSolvable(){
    int *help_vec = new int[15];
        int n = 0;
        for(int i = 0;i < 4;i++)
            for(int j = 0;j < 4;j++){
                help_vec[n] = posicoes[i][j];
                n++;
            }

    int inv_count = 0;
    for (int i = 0; i < 16 - 1; i++)
        for (int j = i + 1; j < 16; j++)
            if (help_vec[j] != 4 && help_vec[i] != 4 && help_vec[i] > help_vec[j])
                inv_count++;
    printf("%i\n", inv_count);
    return(inv_count % 2 == 0);
}

coords Game::findPosition(int number){
    struct coords r;
    for(int i = 0;i < 4;i++)
        for(int j = 0;j < 4;j++)
            if (posicoes[i][j] == number){
                r.x = i;
                r.y = j;
                return  r;
            }
}

int Game::getSentinel() {
   return this->sentinela;
}

int** Game::getMatrix() {
  return this->posicoes;
}

int Game::getMovements() {
  return this->movements;
}

void Game::IncrementMovement(){
    this->movements = this->movements + 1;
}

void Game::updateTime(QTime time){
    this->finalTime = time;
}

QTime Game::getFinalTime(){
    return this->finalTime;
}
