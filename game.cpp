#include "resources.h"
#include <cstdlib>
#include <stdio.h>
#include <time.h>
#include <unordered_set>


game::game(int blank)
{
    sentinela = blank;
    shuffle();
}

char* game::canMove(int number){
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


void game::trocarDois(int matriz [4][4], int linA, int colA, int linB, int colB){
    int temp = matriz [linA][colA];
    matriz [linA][colA] = matriz [linB][colB];
    matriz [linB][colB] = temp;
}


void game::shuffle(){
    srand(time(NULL));
    std::unordered_set<int> numbers;
    int aux_vec[15];

    while(numbers.size() <= 15){
        numbers.insert(rand() % 16 + 1);
    }

    int i = 0;
    for (const int &number : numbers){
        printf("%i\n", number);
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

bool game::estaCompleto (int matriz [4][4]){
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

coords game::findPosition(int number){
    struct coords r;
    for(int i = 0;i < 4;i++)
        for(int j = 0;j < 4;j++)
            if (posicoes[i][j] == number){
                r.x = i;
                r.y = j;
                return  r;
            }
}

int game::getSentinel() {
   return this->sentinela;
}

void game::printMatrix() {
   for (int i=0; i<4; i++){
        for (int j=0; j<4; j++){
            printf("%i ",this->posicoes [i][j]);
        }
        printf("\n");
    }
}
