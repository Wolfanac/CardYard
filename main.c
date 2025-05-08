#include "include.h"
#include "gameInit.h"

//main that will call different fonction to create the game
int main(){
    printf("\033[0m");
    printf("\nCardYard - Games Rules\nObjective\nEnd the game with the lowest total score. The game ends when a player reveal all of his cards. The player with the lowest score at that time wins.");
    printf("\n\nCards and Setup\nUse a deck of cards numbered -2 to 12 (140 cards total)\nEach player gets x cards, where x is the number you will enter\nEvery player flips over 2 cards of their choice at the start\nThe rest of the cards form the draw pile, and each player starts the game with an empty discard pile");
    printf("\n\nTurn\nOn your turn you draw the top card from the main pile and then have two choices:\n    Swap it with one card from your board, revealed or not, that you will discard\n    Take the top card of any player's discard Pile and same thing as above\nAll cards swaped go face up");
    printf("\n\nWhen you have a column full of same cards, it will be destroyed");
    printf("\n\nWhen a player has revealed every card, we still finish the turn. Then every card from each board is revealed and each player counts their score according to the values on the cards and the player with the lowest total wins\n");

    FILE* file = cards_atribution();
    check_error(file);
    Card* pile=NULL;

    int size_main_pile;
    int highest_card;
    int nb_player;
    int nb_card_user;
    int row, col;

    printf("The main pile will have 140 cards");
    printf("You will have the chance to save at the beginning of each turn by pressing S");
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
    while (takeTurn(game, game[index], pile, &size_main_pile, highest_card, row, col, nb_player, nb_card_user, 0)){
        index++;
        if (index==nb_player){
            saving_input_warden(game, size_main_pile, nb_player, pile);
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
        takeTurn(game, game[index], pile, &size_main_pile, highest_card, row, col, nb_player, nb_card_user, 1);
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
