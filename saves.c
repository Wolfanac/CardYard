#include "include.h"
#include "player.h"

void LoadDiscardPile(Player* p, int nb_players) {
    FILE* f = fopen("discardsave.txt", "r");  // Open the file in read mode
    if (f == NULL) {
        printf("Error opening discardsave.txt\n");
        return;
    }

    char line[256];              // Buffer to store each line from the file
    int player_index = 0;        // Keep track of which player value is loaded

    // Read each line until end of file and until all players are processed
    while (fgets(line, sizeof(line), f) && player_index < nb_players) {
        // Look for the ':' character which separates the header from the card values
        char* ptr = strchr(line, ':');
        if (ptr != NULL) {
            ptr++;  // Move past the ':' so ptr now points to the card values
            
            int len = strlen(ptr);  
            // Set the number of cards in the discard pile based on the amount of cards saved previously
            p[player_index].discard_size = len;
            p[player_index].discard_pile = malloc(len * sizeof(Card));

            // Convert each character (digit) to an int and store it in the player's discard pile while skipping every blank spaces
            for (int i = 0; i < len; i++) {
                if (ptr[i] >= '0' && ptr[i] <= '9' && ptr[i]!=(' ')) {
                    p[player_index].discard_pile[i].value = ptr[i] - '0';  
                    p[player_index].discard_pile[i].visibility = 0;       // Default visibility
                }
                else{
                    i=i+1;
                }
            }

            player_index++;  // Move to the next player
        }
    }

    fclose(f);  
}


void SaveDiscardPile(Player* p,int nb_players){
    FILE* f;
    int DiscardPileNumber=1;
    f=fopen("discardsave.txt","w+");
    if (f == NULL) {
        printf("Error opening discardsave.txt\n");
        return;
    }

    for(int k=0;k<nb_players;k++){
        fprintf(f,"\n DiscardPileNumber %d :",DiscardPileNumber);
        for (int i=0;i<p[k].discard_size;i++){
            fprintf(f," %d",p[k].discard_pile[i].value);
        }
        DiscardPileNumber++;
    }
    fclose(f);
}

int* principale_deck_load(int number_of_cards) {
    FILE* f = fopen("MainDeckSave.txt", "r");  
    if (f == NULL) {
        printf("Error opening MainDeckSave.txt\n");
        return NULL;
    }

    int* principal_deck = calloc(number_of_cards, sizeof(int));
    if (principal_deck == NULL) {
        printf("Memory allocation error\n");
        fclose(f);
        return NULL;
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

void principale_deck_save(FILE *fichier, int number_of_cards) {
    FILE* register_zone = fopen("MainDeckSave.txt", "w+");  
    if (register_zone == NULL) {
        printf("Error opening MainDeckSave.txt\n");
        return;
    }

    int *principal_deck = calloc(number_of_cards, sizeof(int));
    if (principal_deck == NULL) {
        printf("Memory allocation error\n");
        fclose(register_zone);
        return;
    }
    int a;
    int i = 0;
    rewind(fichier);
    while (fscanf(fichier, "%d", &a) == 1 && i < number_of_cards) {
        principal_deck[i] = a;
        fprintf(register_zone, "%d\n", principal_deck[i]);
        i++;
    }

    free(principal_deck);
    fclose(register_zone);
}

void demandeur_sauvegarde(FILE* f, int nb_cards, Player* players, int nb_players) {
    char a;
    do {
        printf("Do you wish to save? (Y for yes, N for no): ");
        scanf(" %c", &a);
    } while (a != 'Y' && a != 'y' && a != 'N' && a != 'n');

    if (a == 'N' || a == 'n') {
        printf("Save cancelled.\n");
        return;
    }

    printf("Beginning of the saving process...\n");
  principale_deck_save(f, nb_cards);
    	printf("Deck saved successfully! Proceeding with the discard piles...\n");
    	SaveDiscardPile(players, nb_players);
	printf("Discard piles saved! Dealing with the player stats...\n");
	PlayerStatLoad(players,nb_players)
	printf("Saving complete.\n");
	exit(1);
}

void PlayerStatsave(Player*p, int nb_players){
		FILE* f = fopen("playerstats.txt","w+");
		if (f == NULL){
			printf("Error opening playerstats.txt \n");
			return;
		}
		
		for(int i=0; i < nb_players; i++){
		fprintf(f,"Name: %s",p[i]->nickname);
		fprintf(f,"|| Nb_card: %d",p[i]->nb_card_user);
		fprintf(f,"|| Position: %d \n",p[i]->position);
		}
		fclose(f);
	}

void PlayerStatLoad(Player *p, int nb_players){
FILE* f= fopen("playerstats.txt", "r");
if (f == NULL) {
	printf("Error trying to open playerstats.txt");
	return;
}

char line[256];
int i= 0;
while (fgets(line, sizeof(line), f) && i< nb_players){
	char name[100];
	int nb_cards, position;
	
	if (sscanf(line, "Name: %[^|]|| Nb_card: %d|| Position: %d", name, &nb_cards, &position) == 3) {
		    strcpy(p[i].nickname, name);
		    p[i].nb_card_user = nb_cards;
		    p[i].position = position;
		    i++;
		} else {
		    printf("Corrupted data,unable to read the line);
		}
	    }

	    fclose(f);
	}

void saving_input_warden(FILE * f, int nb_cards, Player* p, int nb_players){
	char c;
	scanf("%c",&c);
	if (c == 'S' || c== 's'){
	printf("Beginning the saving process");
	demandeur_sauvegarde(f, nb_cards, p, nb_players);
	break;
	}
	else if((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')){
	break;
	}
	else{
	break;
	}
}
