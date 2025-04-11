#include "include.h"

int IsPrimeNumber(int nombre){
    int i;
    for (i=2; i*i<=nombre; i++){
        if (nombre%i==0){
            return 0;
        }
    }
    
    return 1;
}