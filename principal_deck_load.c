
#include <stdio.h>
#include <stdlib.h>

int* principale_deck_load(FILE *input_file, int n) {
    if (input_file == NULL) {
        printf("Error: input file is NULL\n");
        return NULL;
    }

    int *pioche_principale = calloc(n, sizeof(int));
    if (pioche_principale == NULL) {
        printf("Memory allocation issue\n");
        return NULL;
    }

    int i = 0;
    rewind(input_file);
    while (fscanf(input_file, "%d", &pioche_principale[i]) == 1 && i < n) {
        i++;
    }

    return pioche_principale;
}
