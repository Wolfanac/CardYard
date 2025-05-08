#include "include.h"
#include "player.h"

void LoadDiscardPile(Player** game, int nb_players) {
    FILE* f = fopen("discardsave.txt", "r");
    if (f == NULL) {
        printf("Error opening discardsave.txt\n");
        return;
    }

    char line[256];
    int player_index = 0;

    while (fgets(line, sizeof(line), f) && player_index < nb_players) {
        char* ptr = strchr(line, ':');
        if (ptr != NULL) {
            ptr++;
            int count = 0;
            int val;
            char* temp = ptr;
            while (sscanf(temp, "%d", &val) == 1) {
                count++;
                while (*temp != ' ' && *temp != '\0') temp++;
                while (*temp == ' ') temp++;
            }
            if (count > 0) {
                game[player_index]->discard_size = count;
                game[player_index]->discard_pile = malloc(count * sizeof(Card));
                temp = ptr;
                int i = 0;
                while (sscanf(temp, "%d", &val) == 1 && i < count) {
                    game[player_index]->discard_pile[i].value = val;
                    game[player_index]->discard_pile[i].visibility = 0;
                    i++;
                    while (*temp != ' ' && *temp != '\0') temp++;
                    while (*temp == ' ') temp++;
                }
            } else {
                game[player_index]->discard_size = 0;
                game[player_index]->discard_pile = NULL;
            }
            player_index++;
        }
    }
    fclose(f);
}

void SaveDiscardPile(Player** game, int nb_players) {
    FILE* f = fopen("DiscardSave.txt", "w+");
    if (f == NULL) {
        printf("Error opening DiscardSave.txt\n");
        exit(1);
    }

    for (int k = 0; k < nb_players; k++) {
        fprintf(f, "DiscardPileNumber %d :", k + 1);  
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
int* principale_deck_load(int number_of_cards) {
    FILE* f = fopen("MainDeckSave.txt", "r");
    if (f == NULL) {
        printf("Error opening MainDeckSave.txt\n");
        return NULL ;
        exit(1);
    }

    int* principal_deck = calloc(number_of_cards, sizeof(int));
    if (principal_deck == NULL) {
        printf("Memory allocation error\n");
        fclose(f);
        return NULL;
        exit(1);
    }

    int i = 0;
    while (i < number_of_cards && fscanf(f, "%d", &principal_deck[i]) == 1) {
        i++;

    }

    if (i != number_of_cards) {
        printf("Warning: Only %d cards loaded out of %d expected.\n", i, number_of_cards);
    }

    fclose(f);
    return principal_deck;
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

void demandeur_sauvegarde(Player** game, int nb_cards_pile, int nb_players, Card** main_pile) {
    char a;
    do {
        printf("\nAre you sure about saving the game? (Y for yes, N for no): ");
        scanf(" %c", &a);
    } while (a != 'Y' && a != 'y' && a != 'N' && a != 'n');

    if (a == 'N' || a == 'n') {
        printf("\nSave cancelled.\n");
        return;
    }

    printf("\nBeginning of the saving process...\n");
    principale_deck_save(nb_cards_pile, *main_pile);
    printf("\nDeck saved successfully! Proceeding with the discard piles...\n");
    SaveDiscardPile(game, nb_players);
    printf("\nDiscard piles saved! Dealing with the player stats...\n");
    PlayerStatsave(game, nb_players);
    printf("\nSaving complete. Restart the game and load you game if you want to resume it\n");
    exit(0);
}

void PlayerStatsave(Player** game, int nb_players) {
    FILE* f = fopen("playerstats.txt", "w+");
    if (f == NULL) {
        printf("Error opening playerstats.txt \n");
        exit(1);
    }

 
    for (int i=0; i<nb_players; i++){
        fprintf(f, "Name: %s", game[i]->nickname);
        fprintf(f, " Position: %d \n", game[i]->position);
    
    }

    fclose(f);
}

void PlayerStatLoad(Player** game, int nb_players) {
    FILE* f = fopen("playerstats.txt", "r");
    if (f == NULL) {
        printf("Empty file or error opening playerstats.txt\n");
        exit(50);
    }

    for (int i = 0; i < nb_players; i++) {
        fscanf(f, "%s", game[i]->nickname);
        fscanf(f, "%d", &game[i]->nb_card_user);
        fscanf(f, "%d", &game[i]->position);
    }

    fclose(f);
}

void saving_input_warden(Player** game, int nb_cards_pile, int nb_players, Card* main_pile) {
    char c;
    printf("\nSaving now, then press 's' or 'S'? You can skip this by pressing any key and Enter: ");
    scanf("%c", &c);
    if (c == 'S' || c == 's') {
        printf("\nBeginning the saving process");
        demandeur_sauvegarde(game, nb_cards_pile, nb_players, &main_pile);
        return;
    } else if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
        return;
    } else {
        return;
    }
}