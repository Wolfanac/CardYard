#include "include.h"

//create a file to store, create, and position randomely the cards in it
FILE* cards_atribution(){
    FILE* usedcards = NULL;
    usedcards = fopen("cards.txt", "w+");

    //check if there is an error
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
        card=rand()%15;
    }
    usedcards=change_cards(usedcards);
    return usedcards;
}

//Fonction that will change values of card in the deck if wanted
 FILE* change_cards(FILE* usedcards){ 
    check_error(usedcards);
    rewind(usedcards);

    //make the player change the values in the pile of cards
    int a=0;
    char  value[10];
    int i=0, number=0, v=0, fileupdate[140], originalnumber;
    printf("\n do you wish to change some cards ? ");
    scanf("%s", value);
    while (strcmp(value, "no") != 0){

        while (strcmp(value, "yes") == 0) {

            i = 0;
            v = 0;
            number = 0;
            originalnumber = 0; 

            printf("\n what numbers do you wish to change ? ");
            int see;
            do {
            see=scanf("%d", &originalnumber);
            empty_buffer();
            if (see!=1){
                printf("You need to enter a number. Try again ");
            }
            }while(see!=1);
            int changenumber=originalnumber;
            printf("\n to what number ? ");
            do {
            see=scanf("%d", &changenumber);
            if (see!=1){
                printf("You need to enter a number. Try again ");
            }
            }while(see!=1);
            if (changenumber==originalnumber){
            printf("\n please enter a number different from the original number ");
            while (getchar() != '\n');
            }
            else{
                printf("\n you change the number %d to %d ", originalnumber, changenumber);
            
                rewind(usedcards);
                while (fscanf(usedcards, "%d", &a)==1){
                    fileupdate[i]=a;
                    i++;
                }
            
                while (v<i){
                    if (fileupdate[v]==originalnumber){
                        fileupdate[v]=changenumber;
                        number++;
                    }
                    v++;
                }

                
                if (number==0){
                    printf("\n no %d number found ", originalnumber);
                }else{
                    printf("\n done ");
                }
                rewind(usedcards);
                v=0;

                while (v<i){
                    fprintf(usedcards, "%d", fileupdate[v]);
                    fputs(" ", usedcards);
                    v++;
                }
                while (getchar() != '\n');

                printf("\n do you wish to change some cards ? ");
                scanf("%s", value);
                
            }
        }

        if (strcmp(value, "no") != 0 && strcmp(value, "yes") != 0) {
            printf("\n Please enter either 'yes' or 'no': ");
            scanf("%s", value);
        }

    }

    
return usedcards;
    
}
