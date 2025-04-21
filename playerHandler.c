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
    Sleep(2000);
    printf("...");
    Sleep(2000);
  
    Player* j1 = malloc(sizeof(Player));
    if (j1 == NULL) {
        printf("\n- Error allocating player ");
        exit(1);
    }

    //Il faudra faire une fonction à part pour s'occuper des cartes

    j1->card = malloc(card_user * sizeof(Card));
    if (j1->card == NULL) {
        printf("- Error allocating cards ");
        exit(1);
    }
    for (int i=0; i<card_user; i++){
        j1->card[i].value=0;
        j1->card[i].visibility=0;
        j1->card[i].exist="exist";
    }

    j1->nickname=AskNickname();

    j1->position=pos;

    j1->nb_card_user=card_user;

    j1->discard_pile=NULL;

    j1->discard_size=0;

    return j1;
}


// Recursive fonction that allows the user to confirm, redo or destroy the player
int CheckPlayer(Player *p, int a) {
    char confirm[10];
    char changing[10];

    if (a == 0) {
        printf("\nI will print what you've written. Confirm by saying 'yes' or 'no': ");
        Sleep(2500);
        printPlayer(p, 1);
        printf("Answer: ");

        do {
            scanf("%s", confirm);
            if (strcmp(confirm, "yes") != 0 && strcmp(confirm, "no") != 0) {
                printf("Invalid input. Please type 'yes' or 'no'.\n");
            }
        } while (strcmp(confirm, "yes") != 0 && strcmp(confirm, "no") != 0);

        if (strcmp(confirm, "yes") == 0) {
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
        Sleep(1500);
        printPlayer(p, 1);
        printf("\nDoes it correspond to what you wanted? (yes/no): ");
        do {
            scanf("%s", confirm);
            if (strcmp(confirm, "yes") != 0 && strcmp(confirm, "no") != 0) {
                printf("Invalid input. Please type 'yes' or 'no'.\n");
            }
        } while (strcmp(confirm, "yes") != 0 && strcmp(confirm, "no") != 0);

        if (strcmp(confirm, "yes") == 0) {
            return 1;
        } else {
            return CheckPlayer(p, 1);
        }
    } else {
        printf("Are you sure you want to delete it? (yes/no): ");
        do {
            scanf("%s", confirm);
            if (strcmp(confirm, "yes") != 0 && strcmp(confirm, "no") != 0) {
                printf("Invalid input. Please type 'yes' or 'no'.\n");
            }
        } while (strcmp(confirm, "yes") != 0 && strcmp(confirm, "no") != 0);

        if (strcmp(confirm, "yes") == 0) {
            printf("Player will be erased.\n");
            Sleep(2000);
            return 0; 
        } else {
            return CheckPlayer(p, 0);
        }
    }
}


//Fonction that create a name and return it by allocating the exact memory it should have
char* AskNickname(){
    char* name = NULL;
    char* temp = NULL;
    int nb_char;
    int ch;
    
    do {
        printf("\nHow many characters in your nickname? ");
        scanf("%d", &nb_char);
        if (nb_char > 100) {
            printf("\n- Error - Too many characters - ending the program");
            exit(1);
        }
    
        while ((ch = getchar()) != '\n' && ch != EOF);
    
        name = realloc(name, (nb_char + 1) * sizeof(char));
        if (name == NULL) {
            printf("\n- Error allocating nickname");
            exit(1);
        }
    
        temp = realloc(temp, (nb_char + 2) * sizeof(char)); 
        if (temp == NULL) {
            printf("\n- Error allocating temp");
            exit(1);
        }
    
        printf("\nWrite the name of your player: ");
        fgets(temp, nb_char + 2, stdin); 
    
        size_t len = strlen(temp);
        if (temp[len - 1] != '\n') {
            while ((ch = getchar()) != '\n' && ch != EOF);
        } else {
            temp[len - 1] = '\0';
            len--;
        }
        
    
        if ((int)len != nb_char) {
            printf("\nYou didn't enter exactly %d characters. Enter the number of characters you want once again.", nb_char);
        }
    
    } while (strlen(temp) != nb_char);
    
    strcpy(name, temp);
    free(temp);

    return name;
}

void checkCol(Player* p, int row, int col){
    int colToDestroy;
    int cardValue;
    for (int i=0; i<(p->nb_card_user)/row; i++){
        colToDestroy=0;
        cardValue=p->card[i].value;
        for (int r=0; r<row; r++){
            if (p->card[i+r*col].visibility==1 && p->card[i+r*col].value==cardValue){
                colToDestroy++;
            }
            if (r==row-1 && colToDestroy==row){
                printf("\nYou have a column of same cards, it will be removed");
                destroyCol(p, row, col, i);
            }
        }
    }

}

void destroyCol(Player* p, int row, int col, int index){
    printf("\nThe column is being removed...");
    Sleep(1500);
    printf("...");
    int* tabIndice=malloc(row*sizeof(int));
    if (tabIndice==NULL){
        printf("\n- Error when destroying column");
        exit(1);
    }
    for (int i=0; i<row; i++){
        tabIndice[i]=index+i*col;
    }

    index=0;
    for (int i=0; i<p->nb_card_user; i++){
        for (int j=0; j<row; j++){
            if (i==tabIndice[j]){
                p->card[i].value=0;
                p->card[i].exist="destroyed";
            }
        }
    }

    free(tabIndice);
}