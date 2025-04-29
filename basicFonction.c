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

void check_error(FILE * file){
    if (file == NULL) {
        printf("Issue with the opening of the file\n");
        exit(1);
    }
}

char* YesNoFonction(){
    char* confirm = malloc(4 * sizeof(char)); 
    if (confirm == NULL) {
        printf("\n- Error allocating answer");
        exit(1);  
    }
    printf("\nAnswer: ");
    do {
        scanf("%3s", confirm); 
        if (strcmp(confirm, "yes") != 0 && strcmp(confirm, "no") != 0) {
            printf("Invalid input. Please type 'yes' or 'no'.\n");
        }
    } while (strcmp(confirm, "yes") != 0 && strcmp(confirm, "no") != 0);

    return confirm;

}

void pressToContinue(){
    printf("\nPress any key to continue: ");
    
}