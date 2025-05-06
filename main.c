#include "include.h"
#include "gameInit.h"

//main that will call different fonction to create the game
int main(){
    printf("\033[0m");
    FILE* file = cards_atribution();
    check_error(file);
    Card* pile=NULL;

    int size_main_pile;
    int highest_card;
    int nb_player;
    int nb_card_user;
    int row, col;

    printf("The main pile will have 140 cards");
    printf("You will have the chance to save at the beginning of each turn by printing S");
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
    
    initiatePlayerboard(game, nb_player, nb_card_user, &pile, &size_main_pile, row, col, highest_card);
    

    int index=0, turn_number=1;
    numberTurn(turn_number);
    //take turns untill the fonction gets 0, which means someone finished his board
    while (takeTurn(game, game[index], &pile, &size_main_pile, highest_card, row, col, nb_player, nb_card_user, 0)){
        index++;
        if (index==nb_player){
            turn_number++;
            index-=nb_player;
            numberTurn(turn_number);
        }
    }
    //check if every player played the same number of times and if not make them play
    if (index+1!=nb_player){
        printf("\nA player has revealed every card, this is the final turn for players who haven't played yet");
        pressToContinue();
    }
    else{
        printf("\nThe player revealing every card of his board is the last player of the turn. No other players get another turn after this.");
        pressToContinue();
    }
    while (index+1!=nb_player){
        index++;
        takeTurn(game, game[index], &pile, &size_main_pile, highest_card, row, col, nb_player, nb_card_user, 1);
    }
    endgame(game, nb_player, row, col, highest_card);
    
    for (int i = 0; i < nb_player; i++) {
        free(game[i]);
    }
    free(game);

    free(pile);

    fclose(file);

    return 0;
}
