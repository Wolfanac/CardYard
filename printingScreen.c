#include "include.h"
#include "player.h"

//Priting main informations of the player, name, position, state of discard pile and current progression of cards and point
void printPlayer(Player *p, int begining){
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
        printf("Discard pile: %s\n", p->discard_pile==NULL ? "None" : "Not empty");
        printf("You have %d cards left to deal with\n", p->nb_card_user);
        printf("The sum of visible cards is %d\n\n", sum);
    }
    
}


void printTopDiscardPile(Player* p){
    int size=p->discard_size;
    if (size!=0){
        printf("\nTop Discard card: %d", p->discard_pile[size-1].value);
    }
    else {
        printf("\nTop Discard card: None");
    }
}

void printTotalDiscardPile(Player* p){
//     int size=p->discard_size;
//     if (size!=0){
//         printf("\nCards in your discard pile are: ");
//         for (int i=0; i<size; i++){
//             printf("%d ", p->discard_pile[i].value);
//         }
//     }
//     else{
//         printf("You don't have any card in you discard pile");
//     }
}

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

void printBoard(Player* p, int row, int col, int max) {
    printf("\n\n");
    int height = 15;
    int width = 15;

    for (int r = 0; r < row; r++) {               
        for (int i = 0; i < height; i++) {        
            for (int c = 0; c < col; c++) {       
                Card card = p->card[r * col + c]; 
                char* color;
                int size;
                char unknown[4]="???";
                if (card.visibility==1){
                    color = colorChoice(card, max);
            
                }
                else {
                    color="\033[0m";
                }
                if (card.visibility==1){
                    size = sizeNumber(card.value);
                }
                else{
                    size=strlen(unknown);
                }
                printf("%s", color);
                for (int j = 0; j < width; j++) { 
                    if (i == 0 || i == height - 1) {
                        printf("-");
                    }
                    else if (j == 0 || j == width - 1) {
                        printf("|");
                    }
                    else if (i == (height / 2) && j == (width / 2) - (size/2)) {
                        printf("\033[0m");
                        if (card.visibility == 1) {
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



char* colorChoice(Card card, int max){
    if (card.value < 0){
        return "\033[34m"; // blue
    }
    else if (card.value == 0){
        return "\033[36m"; // Cyan
    }
    else if (card.value <= max / 3){
        return "\033[33m"; // Yelllow
    }
    else if (card.value <= (2 * max) / 3){
        return "\033[32m"; // green
    }
    else {
        return "\033[31m"; // red
    }
}