typedef struct {
    int value;
    int visibility;
    int color;
} Card;

typedef struct{
    Card* card;
    int* discard_pile;
    char* nickname;
    // int pioche;
    int position;
    int nb_card_user;
} Player;


Player* create_player(int nb_card_user, int pos, int redoing);

int CheckPlayer(Player *p, int a);

void printPlayer(Player *p);

char* AskNickname();