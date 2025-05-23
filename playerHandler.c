#include "include.h"
#include "player.h"


//Creation of the character, giving him his nickanme, his position in the game, the number of cards he has as well as creating his discard pile
Player* create_player(int card_user, int pos, int redoing) {
    if (redoing == 0){
        printf("\nCreating a new player...");
    }
    else {
        printf("\nRedoing the player...");
    }
    printf("...");
  
    Player* j1 = malloc(sizeof(Player));
    if (j1 == NULL) {
        printf("\n- Error allocating player ");
        exit(1);
    }

    j1->card = malloc(card_user * sizeof(Card));
    if (j1->card == NULL) {
        printf("- Error allocating cards ");
        exit(1);
    }
    for (int i=0; i<card_user; i++){
        j1->card[i].value=0;
        j1->card[i].visibility=0;
        j1->card[i].exist = strdup("exist");
        if (j1->card[i].exist == NULL) {
            printf("- Error allocating 'exist' string for card %d\n", i);
            exit(1);
        }    
}
    int nb_char;

    j1->nickname=AskNickname(&nb_char);

    j1->nb_char=nb_char;

    j1->position=pos;

    j1->nb_card_user=card_user;

    j1->discard_pile=NULL;

    j1->discard_size=0;

    return j1;
}


// Recursive fonction that allows the user to confirm, redo or destroy the player
int CheckPlayer(Player *p, int a) {
    if (p==NULL){
        printf("- Error trying to find the player ");
        exit(1);
    }
    char changing[10];
    char* confirm;
    if (a == 0) {
        printf("\nI will print what you've written. Confirm afterward by typing 'yes' or 'no' ");
        printPlayer(p, 1);
        confirm=YesNoFonction();

        if (strcmp(confirm, "yes") == 0) {
            free(confirm);
            return 1;
        } else {
            a = 1;
        }
    }

    printf("\nDo you want to redo your player or to erase it?\nType 'redo' or 'erase': ");
    do {
        scanf("%s", changing);
        if (strcmp(changing, "redo") != 0 && strcmp(changing, "erase") != 0) {
            printf("Invalid input. Please type 'redo' or 'erase'.\n");
        }
    } while (strcmp(changing, "redo") != 0 && strcmp(changing, "erase") != 0);

    if (strcmp(changing, "redo") == 0) {
        *p = *create_player(p->nb_card_user, p->position, 1);
        printf("\nThis will be the new player:\n");
        printPlayer(p, 1);
        printf("\nDoes it correspond to what you wanted? (yes/no): ");
        confirm=YesNoFonction();

        if (strcmp(confirm, "yes") == 0) {
            free(confirm);
            return 1;
        } else {
            free(confirm);
            return CheckPlayer(p, 1);
        }
    } else {
        printf("Are you sure you want to delete it? (yes/no): ");
        confirm=YesNoFonction();

        if (strcmp(confirm, "yes") == 0) {
            printf("Player will be erased.\n");
            free(confirm);
            return 0; 
        } else {
            free(confirm);
            return CheckPlayer(p, 0);
        }
    }
}


//Fonction that create a name and return it by allocating the exact memory it should have
char* AskNickname(int* nb_char_end){
    char* name = NULL;
    char* temp = NULL;
    int ch;
    int nb_char;
    size_t len;
    int see;
    do {
        printf("\nHow many characters in your nickname? ");
        see=scanf("%d", &nb_char);
        empty_buffer();
        if (see!=1){
            printf("You need to enter a number. Type again: ");
            continue;
        }
        if (nb_char>=100){
            printf("Too many characters. Enter a number below 100");
            continue;
        }
        if (nb_char<=0){
            printf("You need to enter a number greater than 0");
            continue;
        }
        
        //I create another char* that can take a bit more than the real one so i can check if the number of char entered is the correct before putting in the main string
        temp = realloc(temp, (nb_char + 2) * sizeof(char)); 
        if (temp == NULL) {
            printf("\n- Error allocating temp");
            exit(1);
        }
    
        printf("\nWrite the name of your player. It can have numbers and spaces if wanted: ");
        fgets(temp, nb_char + 2, stdin); 
    
        //I need to reduce the len by one because the last char of the string isn't a real one
        len = strlen(temp);
        if (temp[len - 1] != '\n') {
            while ((ch = getchar()) != '\n' && ch != EOF);
        } else {
            temp[len - 1] = '\0';
            len--;
        }
        
    
        if (len != nb_char) {
            printf("\nYou didn't enter exactly %d characters. Enter the number of characters you want once again.", nb_char);
        }
    
    } while (len != nb_char||see!=1);
    
    name = realloc(name, (nb_char + 1) * sizeof(char));
    if (name == NULL) {
        printf("\n- Error allocating nickname");
        exit(1);
    }
    strcpy(name, temp);
    free(temp);

    *nb_char_end=nb_char;

    return name;
}

//Fonction that will check if a column is composed of the same card, if it is, calls another function 'destroyCol' which will destroy this column
void checkCol(Player* p, int row, int col){
    if (p==NULL){
        printf("- Error trying to check the player's column ");
        exit(1);
    }
    int colToDestroy;
    int cardValue;
    for (int i=0; i<(p->nb_card_user)/row; i++){
        colToDestroy=0;
        cardValue=p->card[i].value;
        //check each row to see if the card is the same of the first one, and if this card is already destroyed or not
        for (int r=0; r<row; r++){
            if (strcmp(p->card[i + r * col].exist, "destroyed")!=0 && p->card[i+r*col].visibility==1 && p->card[i+r*col].value==cardValue){
                colToDestroy++;
            }
            if (r==row-1 && colToDestroy==row){
                printf("\nYou have a column of same cards, it will be removed");
                destroyCol(p, row, col, i);
            }
        }
    }

}

//Destroy the column starting from the card 'index+1'
void destroyCol(Player* p, int row, int col, int index){
    if (p==NULL){
        printf("- Error trying to destroy the player's column ");
        exit(1);
    }
    printf("\nThe column is being removed...");
    int* tabIndice=malloc(row*sizeof(int));
    if (tabIndice==NULL){
        printf("\n- Error when destroying column");
        exit(1);
    }
    for (int i=0; i<row; i++){
        tabIndice[i]=index+i*col;
    }

    index=0;
    //Checking for every card of the board if this card is the column
    for (int i=0; i<p->nb_card_user; i++){
        for (int j=0; j<row; j++){
            if (i==tabIndice[j]){
                p->card[i].value=0;
                p->card[i].visibility=1;
                p->card[i].exist="destroyed";
            }
        }
    }

    free(tabIndice);
}