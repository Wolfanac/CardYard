typedef struct {
    char* exist;
    int value;
    int visibility;
} Card;

typedef struct{
    Card* card;
    Card* discard_pile;
    int discard_size;
    char* nickname;
    int position;
    int nb_card_user;
} Player;


Player* create_player(int nb_card_user, int pos, int redoing, int* nb_char);

void createPile(FILE* file, Card* pile, int size);

int CheckPlayer(Player *p, int a, int* nb_char);

char* AskNickname(int* nb_char);

int printPlayer(Player *p, int begining);

void printTopDiscardPile(Player* p);

void addDiscardPile(Player* p, Card addCard);

Card DrawCard(Card** pile, int* size);

void printCard(Card card, int max);

void printBoard(Player* p, int row, int col, int max);

char* colorChoice(Card card, int max);

int findHighestCard(Card* pile, int* size_main_pile);

void replaceCard(Player* p, Card replacingCard, int index, int max);

Card takeDiscardPile(Player* p);

int checkEnd(Player* p, int size_pile);

void checkCol(Player* p, int row, int col);

void destroyCol(Player* p, int row, int col, int index);

void endgame(Player** game, int nb_player, int row, int col, int max);

void saving_input_warden(Player** game, int nb_cards_pile, int nb_players, int nb_char, int row, int col, int max, int turn, Card* main_pile);

void ask_save(Player** game, int nb_cards_pile, int nb_players, int nb_char, int row, int col, int max, int turn, Card** main_pile);

void beginingsave(int nb_player, int nb_char, int nb_cards_pile, int row, int col, int turn, int max);

void principale_deck_save(int number_of_cards, Card* main_pile);

void saveDiscardPile(Player** game, int nb_players);

void playerStatsave(Player** game, int nb_players);

void savingBoard(Player** game, int nb_player);

int loadingEverything(Player** game, Card* pile, int* size_main_pile, int* nb_player, int* nb_card_user, int* nb_char, int* row, int* col, int* max, int* turn);

void beginingLoad(int* nb_pile, int* nb_char, int* nb_player, int* row, int* col, int* max, int* turn);

void main_deck_load(Card* pile, int number_of_cards);

void playerStatLoad(Player** game, int nb_players, int nb_char);

void loadingBoards(Player** game, int nb_player);

void loadDiscardPile(Player** game, int nb_players);