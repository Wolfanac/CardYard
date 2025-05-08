#include "include.h"
#include "player.h"

//Fonction that looks if every card got revealed and if so return 1
int checkEnd(Player* p){
    if (p==NULL){
        printf("- Error finding the player");
        exit(1);
    }
    for (int i=0; i<p->nb_card_user; i++){
        if (p->card[i].visibility==0){
            return 0;
        }
    }
    return 1;
}
//sort the results
void sortArray(int scoresresult[], int nb_player) {
    int temp;
    for (int i = 0; i < nb_player - 1; i++) {
        for (int j = 0; j < nb_player - i - 1; j++) {
            if (scoresresult[j] > scoresresult[j + 1]) {
                temp = scoresresult[j];
                scoresresult[j] = scoresresult[j + 1];
                scoresresult[j + 1] = temp;
            }
        }
    }
}

//Fonction that print each board, count each board total values, print the winner afterward
void endgame(Player** game, int nb_player, int row, int col, int max){
    if (game==NULL){
        printf("- Error finding your current game ");
        exit(1);
    }
    int* result=malloc(nb_player*sizeof(int));
    printf("\nEnd of the game");
    printf("\nThe board of each player will be printed");
    pressToContinue();
    for (int i=0; i<nb_player; i++){
        printf("\nBoard of %s", game[i]->nickname);
        for (int j=0; j<game[i]->nb_card_user; j++){
            if (strcmp(game[i]->card[j].exist, "destroyed")!=0){
                game[i]->card[j].visibility=1;
            }
        }   
        printBoard(game[i], row, col, max);
        pressToContinue();
        printf("\n\n");
    }
    printf("\nThe score of each player will be print");
    pressToContinue();
    for (int i=0; i<nb_player; i++){
        result[i]=printPlayer(game[i], 0);
        pressToContinue();
    }

    int min=result[0];
    int scoresresult[nb_player], index[nb_player];
    for (int i=0; i<nb_player; i++){
       sortArray(scoresresult, nb_player);
       }
    int minIndex=0;
    int equal=0, minimum=0, a=0;
    for (int i=1; i<nb_player; i++){
        if (result[i]<min){
            min=result[i];
            minIndex=i;
        }
    }
    for (int i=1; i<nb_player; i++){
      if (scoresresult[i]==scoresresult[1+1]){
        equal=1;
        minimum=scoresresult[i];
        }
      }
      
    for (int i=1; i<nb_player; i++){
      if (scoresresult[i]==minimum){
        index[a]=i;
        a++;
        }
      }
    
    if (equal==1&&min==equal){
      printf("\nthere is an equality for %d points ! the top players are :\n", min);
      for (int b=a; b<=0; b--){
        printf("player numbered %d named %s",index[b]+1, game[index[b]]->nickname);
        }
        
    }
    else{
      printf("\nThe winner of the game is the player number %d, with has    the lowest total of points with %d points, which means %s won!", minIndex+1, min, game[minIndex]->nickname);
    }
    free(result);
}
