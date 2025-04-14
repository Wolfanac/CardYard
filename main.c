#include "include.h"
#include "gameInit.h"

//main that will call different fonction to create the game
int main(){
    // int* pile;
    // int nb_card_pile;
    int nb_player;
    int nb_card_user;
    int row, col;

    Player** game=InitGame(&nb_player, &nb_card_user, &row, &col);
    if (game==NULL){
        printf("Error: Game could not be initialized.\n");
        exit(1);
    }
    
    for (int i = 0; i < nb_player; i++) {
        free(game[i]);
    }
    free(game);


    return 0;
}