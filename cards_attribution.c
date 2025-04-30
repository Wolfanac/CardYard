#include "include.h"

FILE* change_cards(FILE* usedcards);


FILE* cards_atribution(){
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
        card=rand()%15;
    }
    usedcards=change_cards(usedcards);
    return usedcards;
}


 FILE* change_cards(FILE* usedcards){ 

     rewind(usedcards);

     //make the player change the values in the pile of cards
     int a=0;
     char  value[10];
     int i=0, number=0, v=0, fileupdate[140], originalnumber, testvalue=0;
     printf("\n do you wish to change some cards ? ");
     scanf("%s", value);

     while (strcmp(value, "no") != 0){

         while (strcmp(value, "yes") == 0) {

             i = 0;
             v = 0;
             testvalue=0;
             number = 0;
             originalnumber = 0; 

             printf("\n what numbers do you wish to change ? ");
             scanf("%d", &originalnumber);
             int changenumber=originalnumber;
             printf("\n to what number ? ");
             scanf("%d", &changenumber);
             if (changenumber==originalnumber){
                 printf("\n please enter a number different from the original number, or a proper number ");
                 // clear input buffer
                 while (getchar() != '\n');
             }
             else{
                  printf("\n you change the number %d to %d ", originalnumber, changenumber);
                
                 //put all values in a list
                 rewind(usedcards);
                 while (fscanf(usedcards, "%d", &a)==1){
                     fileupdate[i]=a;
                     i++;
                 }
                
                 //change the values in the list
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

                 //print the list in the file
                 while (v<i){
                     fprintf(usedcards, "%d", fileupdate[v]);
                     fputs(" ", usedcards);
                     v++;
                 }
                 // clear input buffer
                 while (getchar() != '\n');

                 //ask to continue
                 printf("\n do you wish to change some cards ? ");
                 scanf("%s", value);
                 
                 

             }
         }

         //mistypes
         if (strcmp(value, "no") != 0 && strcmp(value, "yes") != 0) {
             printf("\n Please enter either 'yes' or 'no': ");
             scanf("%s", value);
         }

     }

     
     return usedcards;
     
 }
