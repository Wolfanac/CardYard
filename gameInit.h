#include "player.h"

Player** InitGame(FILE* file, int* nb_player, int* nb_card_user);

void choseRowCol(int* row, int* col, int nb_card_user);
    
void createPile(FILE* file, Card* pile, int size);

void initiatePlayerboard(Player** game, int nb_player, int nb_card, Card** pile, int* size_main_pile);