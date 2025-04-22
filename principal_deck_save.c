void principale_deck_save(FILE *fichier, FILE *register_zone, int number_of_cards) {
    int *principal_deck = calloc(n, sizeof(int));
    int i = 0, a;
    while (fscanf(fichier, "%d", &a) == 1 && i < n) {
        pioche_principale[i] = a;
        fprintf(zone_enregistrement, "%d\n", pioche_principale[i]);
        i++;
    }

    free(pioche_principale);
}
