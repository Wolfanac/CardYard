#include "include.h"
#include "gameInit.h"


//Fonction that initiates the game
//Creating number of player, number of cards, and the board with all players that are going to be created
Player** InitGame(FILE* file, int* nb_player, int *nb_card_user){  
    printf("\nCardYard - Games Rules\nObjective\nEnd the game with the lowest total score. The game ends when a player reveal all of his cards. The player with the lowest score at that time wins.");
    printf("\n\nCards and Setup\nUse a deck of cards numbered -2 to 12 (140 cards total)\nEach player gets x cards, where x is the number you will enter\nEvery player flips over 2 cards of their choice at the start\nThe rest of the cards form the draw pile, and each player starts the game with an empty discard pile");
    printf("\n\nTurn\nOn your turn you draw the top card from the main pile and then have two choices:\n    Swap it with one card from your board, revealed or not, that you will discard\n    Take the top card of any player's discard Pile and same thing as above\nAll cards swaped go face up");
    printf("\n\nWhen you have a column full of same cards, it will be destroyed");
    printf("\n\nWhen a player has revealed every card, we still finish the turn. Then every card from each board is revealed and each player counts their score according to the values on the cards and the player with the lowest total wins");

    //Number of cards
    printf("\n\nHow many cards will you start with ? ");
    int see=0;
    do{
        see=scanf("%d", nb_card_user);
        empty_buffer();
        if (see!=1){
            printf("You need to enter a number. Type again: ");
            continue;
        }
        if (*nb_card_user<0){
            printf("It may be difficult to play with a negative number of cards, choose another number ");
        }
        else if (IsPrimeNumber(*nb_card_user)){
            printf("You must chose a number which isn't a prime one ");
        } 
        else if (*nb_card_user<6 || *nb_card_user>30){
            printf("We think that with this number of cards, the game won't be enjoyable, so you need to choose a new value ");
        }
    }while (*nb_card_user<0 || *nb_card_user<6 || *nb_card_user>30 || IsPrimeNumber(*nb_card_user)||see!=1);

    //Number of players
    printf("\nHow many players ? ");
    do {
        see=scanf("%d", nb_player);
        empty_buffer();
        if (see!=1){
            printf("You need to enter a number. Type again: ");
            continue;
        }
        if (*nb_player<2||*nb_player>8){
            printf("You must choose a number between 2 and 8 (both included) ");
        }
    } while (*nb_player<2||*nb_player>8||see!=1);

    //Create the board
    Player** game = malloc(*(nb_player) * sizeof(Player*));
    if (game==NULL){
        printf("Error: Game could not be initialized.\n");
        exit(1);
    }

    //Insert the player 
    int validPlayer = 0;
    int tempNumberPlayer=*nb_player;
    for (int i = 0; i < *nb_player; i++) {
        Player* new_player = create_player(*nb_card_user, validPlayer+1, 0);
        if (CheckPlayer(new_player, 0) == 1) {
            game[validPlayer] = new_player;
            validPlayer++;
            printf("The player has been created with success\n");
        } else {
            printf("The player has been deleted with success\n");
            free(new_player);
            tempNumberPlayer--;
            if (tempNumberPlayer<2){
                printf("\nNot enough players, end of program.\n");
    
                for (int j = 0; j < validPlayer; j++) {
                    free(game[j]);
                }
                free(game);
                exit(1);
            }
        }
    }
    *nb_player=validPlayer;

    
    return game;
}


//creates the number of row and columns
void choseRowCol(int* row, int* col, int nb_card_user){
    int see=0;
    do{
        printf("\nHow many rows do you want ? ");
        do{
            see=scanf("%d", row);
            empty_buffer();
            if (see!=1){
                printf("You need to enter a number. Type again: ");
                continue;
            }
        
            if (*row<1){
                printf("You must chose a number greater than that ");
            }
            if (*row==1){
                printf("One row isn't enough as it would mean completing a column each time you reveal a card");
            }
        }while (*row<=1||see!=1);

        printf("How many columns do you want ? ");
        do{
            see=scanf("%d", col);
            empty_buffer();
            if (see!=1){
                printf("You need to enter a number. Type again: ");
                continue;
            }
            if (*col<1){
                printf("You must chose a number greater than that ");
            }
            if (*col==1){
                printf("One column isn't enough as it would mean having a score of 0 when being the one finishing the game");
            }
        }while (*col<=1||see!=1);

        if ((*row)*(*col)!=nb_card_user){
            printf("Chose different values for the row and for the column because it doesn't correspond with the number of cards you chose before ");
            printf("\n");
        }

    }while ((*row)*(*col)!=nb_card_user);
    printf("\nThe board you have chosen is composed of %d rows and %d columns\n", *row, *col);
}

//Fonction that creates the board of the player and put it in the game
void initiatePlayerboard(Player** game, int nb_player, int nb_card, Card** pile, int* size_deck, int row, int col, int highest_card){
    int temp;
    int index;
    for (int i=0; i<nb_player; i++){
        printf("\nCreating the board for the player number %d...", game[i]->position);
        for (int j=0; j<nb_card; j++){
            Card CardDrawn=DrawCard(pile, size_deck);
            game[i]->card[j].value=CardDrawn.value;
        }
        printf("\nThis is your actual board: ");
        printBoard(game[i], row, col, highest_card);
        pressToContinue();
        printf("\nYou will be able to reveal two cards from the board\n ");
        temp=-1;
        int see=0;
        for (int j=0; j<2; j++){
            do {
                printf("\nChose a card to reveal ");
                see=scanf("%d", &index);
                empty_buffer();
                if (see!=1){
                    printf("You need to enter a number. Type again: ");
                    continue;
                }
                if (index<=0||index>nb_card){
                    printf("- Error - Wrong number - Try again ");
                }
                if (index==temp){
                    printf("- Error - Number already chosen ");
                }
            }while (index<=0||index>nb_card||index==temp||see!=1);
            game[i]->card[index-1].visibility=1;
            temp=index;
        }
        printf("\nThe board of the player number %d is now: ", i+1);
        printBoard(game[i], row, col, highest_card);
        pressToContinue();
    }
}


//Fonction that makes the turn 
int takeTurn(Player** game, Player* p, Card** main_pile, int* size_main_pile, int max, int row, int col, int nb_player, int nb_card){
    int discard_possibility=0;
    printf("\nIt's the turn of the player number %d, named %s", p->position, p->nickname);
    printf("\nYour board is the following one: ");
    printBoard(p, row, col, max);
    printf("\nCards in discard piles are: \n");
    //print each player's top discard pile
    for (int i=0; i<nb_player; i++){
        printf("\nPlayer number%d (%s): ", game[i]->position, game[i]->nickname);
        printTopDiscardPile(game[i]);
        if ((game[i]->discard_size)>0){
            discard_possibility=1;
        }
        printf("\n");
    }
    pressToContinue();
    char takeCard[8];
    int index, temp=-1;
    Card cardDrawn=DrawCard(main_pile, size_main_pile);
    printf("\nThe card drawn is :");
    printCard(cardDrawn, max);
    if (discard_possibility==1){
        printf("\nWould you like to play the drawn card from the main deck or take a card from a discard pile ? Enter 'draw' or 'discard' ");
        do {
            scanf("%s", takeCard);
            empty_buffer();
            if (strcmp(takeCard, "draw") != 0 && strcmp(takeCard, "discard") != 0) {
                printf("\nInvalid input. Please type 'draw' or 'discard'.\n");
            }
        } while (strcmp(takeCard, "draw") != 0 && strcmp(takeCard, "discard") != 0);
    }
    else{
        printf("\nAs no one has any card in their discard pile, you can only play the card drawn");
        strcpy(takeCard, "draw");
    }

    if (strcmp(takeCard, "draw") == 0){
        printf("\nChose the card you want to replace: ");
        int see=0;
        do {
            see=scanf("%d", &index);
            empty_buffer();
            if (see!=1){
                printf("You need to enter a number. Type again: ");
                continue;
            }
            if (index<=0||index>nb_card){
                printf("\n- Error - Wrong number - Try again ");
            }
            if (index==temp){
                printf("\n- Error - Number already chosen ");
            }
        }while (index<=0||index>nb_card||index==temp||see!=1);
        index--;
        replaceCard(p, cardDrawn, index, max);
    }
    else {
        int choix;
        int see=0;
        do {
            printf("\nSelect the number of the player ");
            see=scanf("%d", &choix);
            empty_buffer();
            if (see!=1){
                printf("You need to enter a number. Type again: ");
                continue;
            }
            if (choix<=0||choix>nb_player){
                printf("\n- Error - Player not existing - Try again ");
                continue;
            }
            if (game[choix-1]->discard_pile==0){
                printf("\nThis player has no discard pile ");
            }
        }while(choix<=0||choix>nb_player||game[choix-1]->discard_pile==0||see!=1);
        Card cardStolen=takeDiscardPile(game[choix-1]);
        printf("\nThe card taken is");  
        printCard(cardStolen, max);
        printf("\nChose the card you want to replace: ");
        do {
            see=scanf("%d", &index);
            empty_buffer();
            if (see!=1){
                printf("You need to enter a number. Type again: ");
                continue;
            }
            if (strcmp(p->card[index-1].exist, "destroyed")==0){
                printf("\n- Error - card already destroyed ");
            }
            if (index<=0||index>nb_card){
                printf("\n- Error - Wrong number - Try again ");
            }
            if (index==temp){
                printf("\n- Error - Number already chosen ");
            }
        }while (index<=0||index>nb_card||index==temp||strcmp(p->card[index-1].exist, "destroyed")==0||see!=1);
        index--;
        replaceCard(p, cardStolen, index, max);
        
    }
    checkCol(p, row, col);

    //If end return 0 so the while from main ends, continue the game
    if (checkEnd(p)==1){
        return 0;
    }
    else {
        printf("\nThe current state of you board is: ");
        printBoard(p, row, col, max);
        printPlayer(p, 0);
        printf("\nYou still have at least one card to reveal, the game continues");
        pressToContinue();
        return 1;
    }
}
