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


Player* create_player(int nb_card_user, int pos, int redoing);

void createPile(FILE* file, Card* pile, int size);

int CheckPlayer(Player *p, int a);

char* AskNickname();

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

int checkEnd(Player* p);

void checkCol(Player* p, int row, int col);

void destroyCol(Player* p, int row, int col, int index);

void endgame(Player** game, int nb_player, int row, int col, int max);

void LoadDiscardPile(Player** game, int nb_players);

void SaveDiscardPile(Player** game, int nb_players);

int* principale_deck_load(int number_of_cards);

void principale_deck_save(int number_of_cards, Card* main_pile);

void demandeur_sauvegarde(Player** game, int nb_cards_pile, int nb_players, Card** main_pile);

void PlayerStatsave(Player** game, int nb_players);

void PlayerStatLoad(Player** game, int nb_players);

void saving_input_warden(Player** game, int nb_cards_pile, int nb_players, Card* main_pile);