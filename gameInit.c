#include "include.h"
#include "gameInit.h"


//Fonction that initiates the game
//Creating number of player, number of cards, and the board with all players that are going to be created
Player** InitGame(FILE* file, int* nb_player, int *nb_card_user){  

    printf("\nHow many cards will you start with ? ");
    do{
        scanf("%d", nb_card_user);
        if (*nb_card_user<0){
            printf("It may be difficult to play with a negative number of cards, choose another number ");
        }
        else if (IsPrimeNumber(*nb_card_user) && *nb_card_user<6){
            printf("You must chose a number which isn't a prime one ");
        } 
        else if (*nb_card_user<6 || *nb_card_user>30){
            printf("We think that with this number of cards, the game won't be enjoyable, so you need to choose a new value ");
        }
    }while (*nb_card_user<0 || *nb_card_user<6 || *nb_card_user>30 || IsPrimeNumber(*nb_card_user));


    printf("\nHow many players ? ");
    do {
        scanf("%d", nb_player);
        if (*nb_player<2||*nb_player>8){
            printf("You must choose a number between 2 and 8 (both included) ");
        }
    } while (*nb_player<2||*nb_player>8);

    Player** game = malloc(*(nb_player) * sizeof(Player*));
    if (game==NULL){
        printf("Error: Game could not be initialized.\n");
        exit(1);
    }

    int validPlayer = 0;
    int tempNumberPlayer=*nb_player;
    for (int i = 0; i < *nb_player; i++) {
        Player* new_player = create_player(*nb_card_user, validPlayer+1, 0);
        if (CheckPlayer(new_player, 0) == 1) {
            game[validPlayer++] = new_player;
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
void Board(int* row, int* col, int nb_card_user){
    do{
        printf("\nHow many rows do you want ? ");
        do{
            scanf("%d", row);
            if (*row<1){
                printf("You must chose a number greater than 0 ");
            }
        }while (*row<1);

        printf("How many columns do you want ? ");
        do{
            scanf("%d", col);
            if (*col<1){
                printf("You must chose a number greater than 0 ");
            }
        }while (*col<1);

        if ((*row)*(*col)!=nb_card_user){
            printf("Chose different values for the row and for the column because it doesn't correspond with the number of cards you chose before ");
            printf("\n");
        }

    }while ((*row)*(*col)!=nb_card_user);
    printf("\nThe board you have chosen is composed of %d rows and %d columns\n", *row, *col);
}
