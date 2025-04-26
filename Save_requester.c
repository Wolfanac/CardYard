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
    Sleep(1500);
  principale_deck_save(f, nb_cards);
   	 Sleep(500);
    	printf("Deck saved successfully! Proceeding with the discard piles...\n");
    	SaveDiscardPile(players, nb_players);
	printf("Saving complete.\n");
	exit(1);
}
