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
                    p[player_index].discard_pile[i].value = ptr[i] - '0';  // Convert char to int
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