typedef struct {
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

int CheckPlayer(Player *p, int a);

char* AskNickname();

void printPlayer(Player *p);

void printTopDiscardPile(Player* p);

void printTotalDiscardPile(Player* p);

void addDiscardPile(Player* p, Card addCard);

Card DrawCard(Card** pile, int* size, int max);

void printCard(Card card, int max);

void printBoard(Player* p, int row, int col, int max);

char* colorChoice(Card card, int max);

int findHighestCard(Card* pile, int* size_main_pile);
