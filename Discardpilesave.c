#include "inclu.h"

void SaveDisardPile(Player* p,int nb_players){
    File* f
    int DiscardPileNumber=1;
    f=fopen("discardsave.txt","w+");
    int taille=p->discard_size;

    for(int k=0;k<nb_players;k++){
    fprintf(f,"\n DiscardPileNumber %d :",DiscardPileNumber);
    for (int i=0;i<taille;i++){
        fprintf(f,"%d",discardpile.value[i]);
    }
    DiscardPileNumber++;
    }
    fclose(f);
}

