int* principale_deck_load(FILE *fichier, int n) {
    int *pioche_principale = calloc(n, sizeof(int));
    if (pioche_principale == NULL) {
        printf("Erreur d'allocation mémoire.\n");
        return NULL;
    }

    int i = 0;
    while (fscanf(fichier, "%d", &pioche_principale[i]) == 1 && i < n) {
        i++;
    }

    return pioche_principale;
}
