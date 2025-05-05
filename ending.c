#include "include.h"
#include "player.h"

//Fonction that looks if every card got revealed and if so return 1
int checkEnd(Player* p){
    for (int i=0; i<p->nb_card_user; i++){
        if (p->card[i].visibility==0){
            return 0;
        }
    }
    return 1;
}

//Fonction that print each board, count each board total values, print the winner afterward
void endgame(Player** game, int nb_player, int row, int col, int max){
    int* result=malloc(nb_player*sizeof(int));
    printf("\nEnd of the game");
    printf("\nThe board of each player will be printed");
    for (int i=0; i<nb_player; i++){
        printf("\nBoard of %s", game[i]->nickname);
        for (int j=0; j<game[i]->nb_card_user; j++){
            if (strcmp(game[i]->card[j].exist, "destroyed")!=0){
                game[i]->card[j].visibility=1;
            }
        }   
        printBoard(game[i], row, col, max);
        printf("\n\n");
    }
    printf("\nThe score of each player will be print");
    for (int i=0; i<nb_player; i++){
        result[i]=printPlayer(game[i], 0);
    }

    int min=result[0];
    int minIndex=0;
    for (int i=1; i<nb_player; i++){
        if (result[i]<min){
            min=result[i];
            minIndex=i;
        }
    }
    printf("\nThe winner of the game is the player number %d, with %d points, which means %s won!", minIndex+1, min, game[minIndex]->nickname);
    free(result);
}