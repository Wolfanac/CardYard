#include "include.h"
#include "player.h"

int IsPrimeNumber(int nombre){
    int i;
    for (i=2; i*i<=nombre; i++){
        if (nombre%i==0){
            return 0;
        }
    }
    
    return 1;
}


int findHighestCard(Card* pile, int *size_main_pile){
    int max=pile[0].value;
    for (int i=1; i< *size_main_pile; i++){
        if (pile[i].value>max){
            max=pile[i].value;
        }
    }
    return max;
}

int sizeNumber(int number){
    int taille=1;
    if (number==0){
        return 1;
    }
    if (number<0){
        taille++;
    }
    while (number/10!=0){
        number/=10;
        taille++;
    }
    return taille;
}