#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int cards_atribution(){
    //create a file to store, create, and position randomely the cards in it
    FILE* usedcards = NULL;
    usedcards = fopen("cards.txt", "w+");

    //check if the file have been open
    if (usedcards == NULL) {
        printf("ouverture impossible");
        exit(1);
    }
    srand(time(NULL));

    //create the cards order in the file
    int values[15] = {0};
    int maxes[15] = {5, 10, 15, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10};
    char* labels[15] = {"-2", "-1", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12"};
    int card=rand()%15;
    int i=0;
    while (i<140){
        if (values[card] < maxes[card]) {
            fputs(labels[card], usedcards);
            fputs(" ", usedcards);
            values[card]++;
            i++;
        }
        else{
            card=rand()%15;
        }
        card=rand()%15;
    }
    fclose(usedcards);
    return(0);
}

int main(){
    cards_atribution();

    return 0;
}