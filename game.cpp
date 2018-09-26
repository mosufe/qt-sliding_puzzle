#include "resources.h"
#include <cstdlib>
#include <stdio.h>
#include <time.h>
#include <unordered_set>


Game::Game(int blank)
{
    this->posicoes = new int*[4];
    for(int i =0;i < 4;i++)
        posicoes[i] = new int[4];

    this->sentinela = blank;
    shuffle();
}

char const *Game::canMove(int number){
    coords r = findPosition(number);
    int linha = r.x;
    int coluna = r.y;
    int n = sentinela; // tratar n como see a matriz fosse transformada em uma linha so

    printf("%i %i", linha, coluna);

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

bool Game::estaCompleto (int matriz [4][4]){
    //adaptar ao espaco vazio na quarta posicao
    //trocarDois(matriz, 0, 3, 3, 3);

    int pecaSequencial = 1;
    for (int i=0; i<4; i++){
        for (int j=0; j<4; j++){
            if(matriz[i][j] != pecaSequencial) {
                //retornar matriz ao estado original
                //trocarDois(matriz, 0, 3, 3, 3);
                return false;
            }
        }
    }
    //retornar matriz ao estado original
    //trocarDois(matriz, 0, 3, 3, 3);
    return true;
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
