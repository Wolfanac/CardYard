#include "include.h"
#include "player.h"

//Priting main informations of the player, name, position, state of discard pile and current progression of cards and point
int printPlayer(Player *p, int begining){
    if (p==NULL){
        printf("- Error trying to print the player ");
        exit(1);
    }
    int sum=0;
    for (int i=0; i<(p->nb_card_user); i++){
        if (p->card[i].visibility==1){
            sum+=p->card[i].value;
        }
    }
    printf("\n\n");
    printf("Player name: %s\n", p->nickname);
    printf("Player number: %d\n", p->position);
    if (begining!=1){
        printTopDiscardPile(p);
        printf("\nThe sum of visible cards is %d\n\n", sum);
    }
    
    return sum;
}

//Fonction that prints the value of the top card from a player's discard pile
void printTopDiscardPile(Player* p){
    if (p==NULL){
        printf("- Error trying to print a player's discard pile ");
        exit(1);
    }
    int size=p->discard_size;
    if (size!=0){
        printf("\nTop Discard card: %d", p->discard_pile[size-1].value);
    }
    else {
        printf("\nTop Discard card: None");
    }
}

//Fonction that prints the card given. The color of each card will be according to the highest value in the deck
void printCard(Card card, int max){
    printf("\n\n");
    int height=15;
    int width=15;
    char* color;
    if (card.visibility==1){
        color = colorChoice(card, max);

    }
    else {
        color="\033[0m";
    }
    int size;
    char unknown[4]="???";
    if (card.visibility==1){
        size = sizeNumber(card.value);
    }
    else{
        size=strlen(unknown);
    }
    printf("\n");
    printf("%s", color);
    for (int i=0; i<width; i++){
        for (int j=0; j<height; j++){
            if (i==0||i==width-1){
                printf("-");
            }
            else if (j==0 || j==height-1){
                printf("|");
            }
            else if (i == (height / 2) && j == (width / 2) - (size/2)) {
                printf("\033[0m");
                if (card.visibility == 1) {
                    printf("%d", card.value);
                    j += size - 1;
                } else {
                    printf("%s", unknown);
                    j += size-1;
                }
                printf("%s", color); 
            }
            else {
                printf(" ");
            }
        }
        printf("\n");
    }
    printf("\033[0m");
}

//Fonction that prints every card of the board of the player given
void printBoard(Player* p, int row, int col, int max) {
    if (p==NULL){
        printf("- Error trying to print the player's board ");
        exit(1);
    }
    printf("\n\n");
    int height = 15;
    int width = 15;
    for (int r = 0; r < row; r++) {               
        for (int i = 0; i < height; i++) {        
            for (int c = 0; c < col; c++) {       
                Card card = p->card[r * col + c]; 
                char* print1;
                char* print2;
                //check if the card is destroyed so I don't print it
                if (strcmp(card.exist, "destroyed")==0){
                    print1=" ";
                    print2=" ";
                }
                else {
                    print1="-";
                    print2="|";
                }
                char* color;
                int size;
                char unknown[4]="???";
                if (card.visibility==1){
                    color = colorChoice(card, max);
            
                }
                else {
                    color="\033[0m";
                }
                //Size usefull for putting the value right in the middle of the card
                if (card.visibility==1){
                    size = sizeNumber(card.value);
                }
                else{
                    size=strlen(unknown);
                }
                printf("%s", color);
                for (int j = 0; j < width; j++) { 
                    if (i == 0 || i == height - 1) {
                        printf("%s", print1);
                    }
                    else if (j == 0 || j == width - 1) {
                        printf("%s", print2);
                    }
                    else if (i == (height / 2) && j == (width / 2) - (size/2)) {
                        printf("\033[0m");
                        if (strcmp(card.exist, "destroyed")==0){
                            printf(" ");
                        }
                        else if (card.visibility == 1) {
                            printf("%d", card.value);
                            j += size-1 ;
                        } else {
                            printf("%s", unknown);
                            j += size-1;
                        }
                        printf("%s", color); 
                    }
                    else {
                        printf(" ");
                    }
                }
                printf("\033[0m "); 
            }
            printf("\n"); 
        }
    }
}


void numberTurn(int turn_number){
    printf("\nThis is the turn number %d", turn_number);
}
