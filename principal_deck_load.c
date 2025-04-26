#include "include.h"

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
