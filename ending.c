#include "include.h"
#include "player.h"

int checkEnd(Player* p){
    for (int i=0; i<p->nb_card_user; i++){
        if (p->card[i].visibility==0){
            return 0;
        }
    }
    return 1;
}