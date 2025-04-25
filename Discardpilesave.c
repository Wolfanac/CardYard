#include "include.h"

void SaveDiscardPile(Player* p,int nb_players){
    FILE* f;
    int DiscardPileNumber=1;
    f=fopen("discardsave.txt","w+");
    if (f == NULL) {
        printf("Error opening discardsave.txt\n");
        return;
    }

    for(int k=0;k<nb_players;k++){
        fprintf(f,"\n DiscardPileNumber %d :",DiscardPileNumber);
        for (int i=0;i<p[k].discard_size;i++){
            fprintf(f," %d",p[k].discard_pile[i].value);
        }
        DiscardPileNumber++;
    }
    fclose(f);
}
