#include "include.h"
#include "player.h"


//Fonction that creates the main pile from which cards will be taken
void createPile(FILE* file, Card* pile, int size) {
    if (file==NULL || pile==NULL){
        printf("- Error creating the pile ");
        exit(1);
    }
    rewind(file);
    for (int i = 0; i < size; i++) {
        if (fscanf(file, "%d", &pile[i].value) != 1) {
            printf("- Error when reading the %d card in the file", i+1);
        }
        pile[i].visibility=1;
    }

    printf("\nCards in the main pile ");
    for (int i = 0; i < size; i++) {
        printf("%d ", pile[i].value);
    }
    printf("\n");
}

//Fonction that adds a card to a discard pile
void addDiscardPile(Player* p, Card addCard) {
    if (p==NULL){
        printf("- Error when looking the discard pile ");
        exit(1);
    }
    Card* temp = realloc(p->discard_pile, (p->discard_size + 1) * sizeof(Card));
    if (temp == NULL) {
        printf("\n- Error allocating new discard pile");
        exit(1);
    }
    addCard.visibility=1;

    p->discard_pile = temp;
    p->discard_pile[p->discard_size] = addCard;
    p->discard_size++;
}

//Fonction that take the top card from the discard pile and reallocate memory
Card takeDiscardPile(Player* p){
    if (p==NULL){
        printf("- Error while trying to take a card from a discard pile");
        exit(1);
    }
    if (p->discard_size == 0) {
        printf("\n- Error, discard pile empty!\n");
        exit(1);
    }

    p->discard_size--;
    Card cardTaken = p->discard_pile[p->discard_size];

    if (p->discard_size == 0) { //if size==0 it could provoke an error (which was the case for me) so we discard (free) the previous discard pile to create a new one
        free(p->discard_pile);
        p->discard_pile = NULL;
    } else {
        Card* temp = realloc(p->discard_pile, p->discard_size * sizeof(Card));
        if (temp == NULL) {
            printf("\n- Error allocating new discard pile");
            exit(1);
        }
        p->discard_pile = temp;
    }

    return cardTaken;
}

//Fonction that draws a card and reallocate the main pile
Card DrawCard(Card** pile, int *size){
    if (pile==NULL || size==NULL){
        printf("- Error when trying to draw a card ");
        exit(1);
    }
    Card drawnCard=(*pile)[0];

    for (int i=1; i<*size; i++){
        (*pile)[i-1]=(*pile)[i];
    }
    if (*size-1==0){
        free(*pile);
    }
    else{
        Card* Newpile=realloc(*pile, (*size-1)*sizeof(Card)); //I didn't have to create a new pile, I could have reallocated the same one, but by doing so it allows us to keep using the main pile even if an error occured, I could, for example, save the current state of the game because the cards in the pile still existed. However if I don't create a new temp, if an error occurs, the pile would be lost so i wouldn't be able to save the game since there would be no card to stock
        if (Newpile==NULL){
            printf("- Error allocating the pile");
            exit(1);
        }
        *pile=Newpile;
        (*size)--;
    }

    return drawnCard;
}

void replaceCard(Player* p, Card replacingCard, int index, int max){
    if (p==NULL){
        printf("- Error while trying to replace a card ");
        exit(1);
    }
    Card temp=p->card[index];
    temp.visibility=1;
    p->card[index].value=replacingCard.value;
    p->card[index].visibility=1;
    printf("\nThe card discarded is:");
    printCard(temp, max);
    addDiscardPile(p, temp);
}
