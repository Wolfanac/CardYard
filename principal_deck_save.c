#include <stdio.h>
#include <stdlib.h>

void principale_deck_save(FILE *fichier, FILE *register_zone, int number_of_cards) {
    int *principal_deck = calloc(number_of_cards, sizeof(int));
    if (principal_deck == NULL) {
        printf("Memory allocation error\n");
        return;
    }
    int i = 0, a;
    rewind(fichier);
    while (fscanf(fichier, "%d", &a) == 1 && i < number_of_cards) {
        principal_deck[i] = a;
        fprintf(register_zone, "%d\n", principal_deck[i]);
        i++;
    }

    free(principal_deck);
}
