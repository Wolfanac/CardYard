typedef struct {
    int value;
    int visibility;
    int color;
} Card;

typedef struct{
    Card* card;
    Card* discard_pile;
    int discard_size;
    char* nickname;
    // int pioche;
    int position;
    int nb_card_user;
} Player;


Player* create_player(int nb_card_user, int pos, int redoing);

int CheckPlayer(Player *p, int a);

char* AskNickname();

void printPlayer(Player *p);

void printTopDiscardPile(Player* p);

void printTotalDiscardPile(Player* p);