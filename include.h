#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>

int IsPrimeNumber(int nombre);

int sizeNumber(int number);

FILE* cards_atribution();

void principale_deck_save(FILE* f, int nb_cards);
void SaveDiscardPile(Player* p, int nb_players);
void demandeur_sauvegarde(FILE* f, int nb_cards, Player* players, int nb_players);

