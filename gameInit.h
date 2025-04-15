#include "player.h"

Player** InitGame(FILE* file, int* nb_player, int* nb_card_user);

void Board(int* row, int* col, int nb_card_user);
    
void createPile(FILE* file, Card* pile, int size);
