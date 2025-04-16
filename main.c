#include "include.h"
#include "gameInit.h"

//main that will call different fonction to create the game
int main(){
    FILE* file = cards_atribution();
    if (file==NULL){
        printf("- Error creating cards");
    }
    Card* pile=NULL;

    int size_main_pile;
    int highest_card;
    int nb_player;
    int nb_card_user;
    int row, col;

    printf("The main pile will have 140 cards");
    size_main_pile=140;
    pile=malloc(size_main_pile*sizeof(Card));
    createPile(file, pile, size_main_pile);

    Player** game=InitGame(file, &nb_player, &nb_card_user);
    if (game==NULL){
        printf("- Error - Game could not be initialized.\n");
        exit(1);
    }
    
    highest_card=findHighestCard(pile, &size_main_pile);
    
    choseRowCol(&row, &col, nb_card_user);
    
    initiatePlayerboard(game, nb_player, nb_card_user, &pile, &size_main_pile);
    
    takeTurn(game, game[0], &pile, &size_main_pile, highest_card, row, col, nb_player, nb_card_user);

    for (int i = 0; i < nb_player; i++) {
        free(game[i]);
    }
    free(game);

    free(pile);

    fclose(file);

    return 0;
}