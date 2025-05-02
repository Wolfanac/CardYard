#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#if defined(_WIN32) || defined(_WIN64)
    #include <conio.h>
    #include <windows.h>
#else
    #include <termios.h>
    #include <unistd.h>
#endif

int IsPrimeNumber(int nombre);

int sizeNumber(int number);

FILE* cards_atribution();

FILE* change_cards(FILE* usedcards);

char* YesNoFonction();

void empty_buffer();

void numberTurn(int turn_number);