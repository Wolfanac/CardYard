#include "include.h"

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
