#include "include.h"
#include "player.h"

//Fonction that check if the number is a prime one
int IsPrimeNumber(int nombre){
    int i;
    for (i=2; i*i<=nombre; i++){
        if (nombre%i==0){
            return 0;
        }
    }
    
    return 1;
}

//Fonction that return the max value of the pile
int findHighestCard(Card* pile, int *size_main_pile){
    if (pile==NULL || size_main_pile==NULL){
        printf("- Error finding pile or its size ");
        exit(1);
    }
    int max=pile[0].value;
    for (int i=1; i< *size_main_pile; i++){
        if (pile[i].value>max){
            max=pile[i].value;
        }
    }
    return max;
}

//Fontion that chek the size of the number
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

//Fonction to see if there is an error in the file
void check_error(FILE * file){
    if (file == NULL) {
        printf("Issue with the opening of the file\n");
        exit(1);
    }
}

//Fonction which returns 'yes' or 'no' according to what the player typed
char* YesNoFonction(){
    char* confirm = malloc(4 * sizeof(char)); 
    if (confirm == NULL) {
        printf("\n- Error allocating answer");
        exit(1);  
    }
    printf("\nAnswer: ");
    int see=0;
    do {
        see=scanf("%3s", confirm); 
        empty_buffer();
        if (strcmp(confirm, "yes") != 0 && strcmp(confirm, "no") != 0) {
            printf("Invalid input. Please type 'yes' or 'no'.\n");
        }
    } while ((strcmp(confirm, "yes") != 0 && strcmp(confirm, "no") != 0)||see!=1 );

    return confirm;

}

//Fonction that stop the program momently so we can see what happened
void pressToContinue() {
    char pass[100];
    do{
        printf("\nPress Enter to continue: ");
        fgets(pass, sizeof(pass), stdin); 
        if (strcmp(pass, "\n")!=0){
            printf("You didn't press Enter. Try again: ");
        }
    }while (strcmp(pass, "\n")!=0);
}


//Fonction that makes the buffer empty
void empty_buffer(){
    while (getchar()!='\n'){}
}

//Fonction which return the color according to the max value of the pile
char* colorChoice(Card card, int max){
    if (card.value < 0){
        return "\033[34m"; // blue
    }
    else if (card.value == 0){
        return "\033[36m"; // Cyan
    }
    else if (card.value <= max / 3){
        return "\033[32m"; // green
    }
    else if (card.value <= (2 * max) / 3){
        return "\033[33m"; // yellow
    }
    else {
        return "\033[31m"; // red
    }
}