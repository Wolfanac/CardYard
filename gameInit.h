#include "player.h"

Player** InitGame(FILE* file, int* nb_player, int* nb_card_user);

void choseRowCol(int* row, int* col, int nb_card_user);

void initiatePlayerboard(Player** game, int nb_player, int nb_card, Card** pile, int* size_main_pile, int row, int col, int highest_card);

int takeTurn(Player** game, Player* p, Card** main_pile, int* size_main_pile, int max, int row, int col, int nb_player, int nb_card);
