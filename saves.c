#include "include.h"
#include "player.h"

void saving_input_warden(Player** game, int nb_cards_pile, int nb_players, int row, int col, int max, int turn, Card* main_pile) {
    char c;
    printf("\nDo you want to save the game? Put 'S' or 's' as the first letter of you answer to save ");
    scanf(" %c", &c);
    if (c == 'S' || c == 's') {
        printf("\nBeginning the saving process");
        ask_save(game, nb_cards_pile, nb_players, row, col, max, turn, &main_pile);
        return;
    } else if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
        return;
    } else {
        return;
    }
}

void ask_save(Player** game, int nb_cards_pile, int nb_players, int row, int col, int max, int turn, Card** main_pile) {
    printf("\nAre you sure you want to save the game? Type 'yes' or 'no': ");
    char* confirm=YesNoFonction();

    if (strcmp(confirm, "yes") == 0) {
        free(confirm);
    } 
    else {
        printf("\nSave cancelled.\n");
        return;
    }

    printf("\nBeginning of the saving process...\n");
    beginingsave(nb_players, nb_cards_pile, row, col, max, turn);
    principale_deck_save(nb_cards_pile, *main_pile);
    printf("\nDeck saved successfully! Proceeding with the discard players stats...\n");
    playerStatsave(game, nb_players);
    printf("\nStats saved, now turn of the discard pile");
    saveDiscardPile(game, nb_players);
    printf("\nDiscard piles saved! Dealing with the boards...\n");
    savingBoard(game, nb_players);
    printf("\nSaving complete. Restart the game and load you game if you want to resume it\n");

    exit(0);
}

void beginingsave(int nb_player, int nb_cards_pile, int row, int col, int max, int turn){
    FILE* f=fopen("beginingSave.txt", "w+");
    if (f==NULL){
        printf("- Error saving begining values ");
        exit(1);
    }
    fprintf(f, "%d %d %d %d %d %d", nb_player, nb_cards_pile, row, col, max, turn);

    fclose(f);
}

void principale_deck_save(int number_of_cards, Card* main_pile) {
    FILE* register_zone = fopen("MainDeckSave.txt", "w+");
    if (register_zone == NULL) {
        printf("Error opening MainDeckSave.txt for writing\n");
        return;
    }

    if (main_pile==NULL){
        printf("- Error saving main pile ");
        exit(1);
    }

    for (int i=0; i<number_of_cards; i++){
        fprintf(register_zone, "%d ", main_pile[i].value);
    }

    fclose(register_zone);
}

void saveDiscardPile(Player** game, int nb_players) {
    FILE* f = fopen("DiscardSave.txt", "w+");
    if (f == NULL) {
        printf("Error opening DiscardSave.txt\n");
        exit(1);
    }

    for (int k = 0; k < nb_players; k++) {
        fprintf(f, "%d DiscardPileNumber %d :", game[k]->discard_size, k + 1);  
        if (game[k]->discard_size == 0 || game[k]->discard_pile == NULL) {
            fprintf(f, "NULL\n"); 
            printf("The player %d does not have any discard pile.\n", k + 1);
            continue;
        }
        for (int i = 0; i < game[k]->discard_size; i++) {
            fprintf(f, " %d", game[k]->discard_pile[i].value);
        }
        fprintf(f, "\n");
    }

    fclose(f);
}

void playerStatsave(Player** game, int nb_players) {
    FILE* f = fopen("playerstats.txt", "w+");
    if (f == NULL) {
        printf("Error opening playerstats.txt \n");
        exit(1);
    }
 
    for (int i=0; i<nb_players; i++){
        fprintf(f, " %d ", game[i]->nb_char);
        fprintf(f, "Name: %s", game[i]->nickname);
        fprintf(f, " Position: %d ", game[i]->position);
        fprintf(f, " %d", game[i]->nb_card_user);

        fprintf(f, "\n");
    }

    fclose(f);
}

void savingBoard(Player** game, int nb_player){
    FILE* f=fopen("playersboard.txt", "w+");
    if (f==NULL){
        printf("\n- Error saving boards");
        exit(1);
    }
    for (int i=0; i<nb_player; i++){
        if (game[i] == NULL || game[i]->card == NULL) {
            printf("\n- Error while loading player ");
            exit(1);
        }
        for (int j=0; j<game[i]->nb_card_user; j++){
            fprintf(f,"%d %d %s ",  game[i]->card[j].value, game[i]->card[j].visibility,  game[i]->card[j].exist);
        }
        fprintf(f, "\n");
    }
    fclose(f);
}

int loadingEverything(Player*** game, Card** pile, int* size_main_pile, int* nb_player, int* nb_card_user, int* row, int* col, int* max, int* turn){
    if (fopen("MainDeckSave.txt", "r")==NULL){
        printf("\nNo game to load, you will start a new game: ");
        pressToContinue();
        return 0;
    }
    printf("Do you want to load the previous game ? ");
    char* confirm;
    confirm=YesNoFonction();
    if (strcmp(confirm, "yes") == 0) {
        free(confirm);
        beginingLoad(size_main_pile, nb_player, row, col, max, turn);
        *game=malloc(*(nb_player) * sizeof(Player*));
        for (int i = 0; i < *nb_player; i++) {
            (*game)[i] = malloc(sizeof(Player));
            if ((*game)[i] == NULL) {
                printf("- Error allocating memory for player %d\n", i);
                exit(1);
            }
        }        
        *pile=malloc(*(size_main_pile)*sizeof(Card));
        main_deck_load(*pile, *size_main_pile);
        playerStatLoad(*game, *nb_player);
        loadingBoards(*game, *nb_player);
        loadDiscardPile(*game, *nb_player);
        printf("game sucessfully loaded, boards will be printed");
        for (int i=0; i<*nb_player; i++){
            printf("\nBoard number %d: ", i+1);
            printBoard((*game)[i], *row, *col, *max);
            pressToContinue();
        }
        return 1;
    } 
    else {
        free(confirm);
        printf("\nYou will start a new game ");
        return 0;

    }
}

void beginingLoad(int* nb_pile, int* nb_player, int* row, int* col, int* max, int* turn){
    FILE* f=fopen("beginingSave.txt", "r");
    if (f==NULL){
        printf("- Error loading begining values");
        exit(1);
    }
    rewind(f);
    if (fscanf(f, "%d %d %d %d %d %d", nb_player, nb_pile, row, col, max, turn) != 6){
        printf("- Error loading begining values ");
        exit(1);
    }
    
    fclose(f);
}


void main_deck_load(Card* pile, int number_of_cards) {
    if (pile==NULL){
        printf("- Error loeading main deck ");
        exit(1);
    }
    FILE* f = fopen("MainDeckSave.txt", "r");
    if (f == NULL) {
        printf("Error opening MainDeckSave.txt\n");
        exit(1);
    }
    rewind(f);

    for (int i=0; i<number_of_cards; i++){
        fscanf(f, "%d", &pile[i].value);
        pile[i].visibility=1;
    }

    fclose(f);
}

void playerStatLoad(Player** game, int nb_players) {
    FILE* f = fopen("playerstats.txt", "r");
    if (f == NULL) {
        printf("Empty file or error opening playerstats.txt\n");
        exit(50);
    }
    rewind(f);

    for (int i = 0; i < nb_players; i++) {
        if (game[i]==NULL){
            printf("\n- Error loading player's stats ");
            exit(1);
        }
        fscanf(f, "%d", &game[i]->nb_char);
        char temp1[10], temp2[10];
        char* name=malloc((game[i]->nb_char+1)*sizeof(char));
        if (name==NULL){
            printf("- Error loading nickname ");
            exit(1);
        }
        int pos, nb_card_user;
        
        if (fscanf(f, "%s %s %s %d %d", temp1, name, temp2, &pos, &nb_card_user)==5){
            game[i]->nickname=malloc((game[i]->nb_char+1)*sizeof(char));
            if (game[i]->nickname== NULL){
                printf("- Error loading nickname ");
                exit(1);
            }
            strcpy(game[i]->nickname, name);
            game[i]->position=pos;
            game[i]->nb_card_user=nb_card_user;
            game[i]->card = malloc(nb_card_user * sizeof(Card));
            if (game[i]->card == NULL) {
                printf("- Error allocating card for player %d", i);
                exit(1);
            }
            free(name);
        }
        else{
            printf("- Error loading saved stats ");
            free(name);
            exit(1);
        }
    }

    fclose(f);
}

void loadingBoards(Player** game, int nb_player){
    FILE* f = fopen("playersboard.txt", "r");
    if (f == NULL) {
        printf("\n- Error loading boards");
        exit(1);
    }
    rewind(f);

    for (int i = 0; i < nb_player; i++) {
        if (game[i] == NULL || game[i]->card == NULL) {
            printf("\n- Error while loading boards ");
            exit(1);
        }
        for (int j = 0; j < game[i]->nb_card_user; j++) {
            int value, visibility;
            char exist[10];
            if (fscanf(f, "%d %d %s", &value, &visibility, exist) == 3) {
                game[i]->card[j].value = value;
                game[i]->card[j].visibility = visibility;
                game[i]->card[j].exist = strdup(exist);
                if (game[i]->card[j].exist == NULL) {
                    printf("- Error allocating memory for card.exist during loading\n");
                    exit(1);
                }           
            } 
            else {
                printf("\n- Error reading cards for player %d, card %d", i + 1, j + 1);
                exit(1);
            }
        }
    }
    fclose(f);
}

void loadDiscardPile(Player** game, int nb_players) {
    FILE* f = fopen("discardsave.txt", "r");
    if (f == NULL) {
        printf("Error opening discardsave.txt\n");
        return;
    }

    rewind(f);

    for (int i = 0; i < nb_players; i++) {
        if (fscanf(f, "%d", &game[i]->discard_size) != 1) {
            printf("Error reading discard size for player %d\n", i);
            fclose(f);
            exit(1);
        }

        if (game[i]->discard_size > 0) {
            game[i]->discard_pile = malloc(game[i]->discard_size * sizeof(Card));
            if (game[i]->discard_pile == NULL) {
                printf("Memory allocation failed for discard_pile (player %d)\n", i);
                fclose(f);
                exit(1);
            }
        } else {
            game[i]->discard_pile = NULL;
        }

        char temp[20], temp2[2];
        if (fscanf(f, "%s %d %s", temp, &game[i]->position, temp2) != 3) {
            printf("Error reading metadata for player %d\n", i);
            fclose(f);
            exit(1);
        }

        for (int j = 0; j < game[i]->discard_size; j++) {
            if (fscanf(f, "%d", &game[i]->discard_pile[j].value) != 1) {
                printf("Error reading discard card %d for player %d\n", j, i);
                fclose(f);
                exit(1);
            }
            game[i]->discard_pile[j].visibility = 1;
        }
    }

    fclose(f);
}

