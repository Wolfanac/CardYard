
int* principale_deck_load(FILE *f, int n) {
    FILE* f=fopen("cards.txt","r+");
     if (f == NULL) {
        printf("Error opening cards.txt\n");
        return;
    }
    int *pioche_principale = calloc(n, sizeof(int));
    if (pioche_principale == NULL) {
        printf("Memory allocation issue\n");
        return NULL;
    }

    int i = 0;
    while (fscanf(f, "%d", &pioche_principale[i]) == 1 && i < n) {
        i++;
    }

    return pioche_principale;
}
