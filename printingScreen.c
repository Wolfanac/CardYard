#include "include.h"
#include "player.h"

//Priting main informations of the player, name, position, state of discard pile and current progression of cards and point
void printPlayer(Player *p){
    int sum=0;
    for (int i=0; i<(p->nb_card_user); i++){
        if (p->card[i].visibility==1){
            sum+=p->card[i].value;
        }
    }
    printf("\n\n");
    printf("Player name: %s\n", p->nickname);
    printf("Player number %d\n", 1+p->position);
    printf("Discard pile: %s\n", p->discard_pile==NULL ? "None" : "Not empty");
    printf("You have %d cards left to deal with\n", p->nb_card_user);
    printf("The sum of visible cards is %d\n\n", sum);
    
}


void printTopDiscardPile(Player* p){
    int taille=p->discard_size;
    if (taille!=0){
        printf("\nTop Discard card: %d", p->discard_pile[taille-1].value);
    }
    else {
        printf("\nTop Discard card: None");
    }
}

void printTotalDiscardPile(Player* p){
    int taille=p->discard_size;
    if (taille!=0){
        printf("\nCards in your discard pile are: ");
        for (int i=0; i<taille; i++){
            printf("%d ", p->discard_pile[i].value);
        }
    }
    else{
        printf("You don't have any card in you discard pile");
    }
}