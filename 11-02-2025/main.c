/*
* TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: González Monné, Marcos LOGIN 1: marcos.gonzalez.monne
 * AUTHOR 2: Riveiro Primoy, Breixo LOGIN 2: breixo.riveirop
 * GROUP: 1.4
 * DATE: 06 / 03 / 25
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"

#define MAX_BUFFER 255

#ifdef DYNAMIC_LIST
#include "dynamic_list.h"
#endif
#ifdef STATIC_LIST
#include "static_list.h"
#endif


//______________________________________________________________________________________________________________________

void new (tItemL i, tList *L) {
    i.bidCounter = 0; //Ajusta el contador de pujas a 0

    if (findItem(i.consoleId, *L) == LNULL && insertItem(i, LNULL, L) == true) { //Si no existe el ítem y se pudo insertar, se imprime lo que se insertó
        printf("* New: console %s seller/bidder %s brand %d price %f\n", i.consoleId, i.seller, i.consoleBrand, i.consolePrice);
    }
    else { //Si no fue posible, se imprime un error;
        printf("+ Error: New not possible\n");
    }
}

//______________________________________________________________________________________________________________________

void delete (tItemL i, tList *L) {
    if (findItem(i.consoleId, *L) != LNULL) {
        printf("* Delete: console %s seller %s brand %d price %f bids %d\n", i.consoleId, i.seller, i.consoleBrand, i.consolePrice, i.bidCounter);
        deleteAtPosition(findItem(i.consoleId, *L), L);
    }
    else {
        printf("+ Error: Delete not possible\n");
    }
}

//______________________________________________________________________________________________________________________

void bid (tItemL i, tList *L) {
    if (findItem(i.consoleId, *L) != LNULL) {
        updateItem(i, findItem(i.consoleId, *L), L);
        printf("* Bid: console %s seller %s brand %d price %f bids %d\n", i.consoleId, i.seller, i.consoleBrand, i.consolePrice, i.bidCounter);
    }
    else {
        printf("+ Error: Bid not possible\n");
    }
}

//______________________________________________________________________________________________________________________

void stats (tList L) {
    if (!isEmptyList(L)) {
        tPosL p = first(L);
        tItemL i;
        int nintendo = 0;
        int sega = 0;
        float pNintendo = 0;
        float pSega = 0;
        while (p != LNULL) {
            i = getItem(p, L);
            printf("Console %s seller %s brand %d, price %f bids %d\n", i.consoleId, i.seller, i.consoleBrand, i.consolePrice, i.bidCounter);
            if (i.consoleBrand == 1) {
                nintendo++;
                pNintendo += i.consolePrice;
            }
            else if (i.consoleBrand == 2) {
                sega++;
                pSega += i.consolePrice;
            }
        }
        printf("Brand     Consoles    Price  Average\n");
        printf("Nintendo  %8d %8.2f %8.2f\n", nintendo, pNintendo, pNintendo/nintendo);
        printf("Sega      %8d %8.2f %8.2f\n", sega, pSega, pSega/sega);
    }
    else {
        printf("+ Error: Stats not possible\n");
    }
}

//______________________________________________________________________________________________________________________

void processCommand(char *commandNumber, char command, char *param1, char *param2, char *param3, char *param4) {
    tItemL i;
    strcpy(i.consoleId, param1);
    strcpy(i.seller, param2);
    i.consoleBrand = atoi(param3);
    i.consolePrice = atof(param4);
    tList L;

    createEmptyList(&L);

    switch (command) {
        case 'N':
            printf("Command: %s %c %s %s %s %s\n", commandNumber, command, param1, param2, param3, param4);
            new(i, &L);
        break;
        case 'D':
            delete(i, &L);
            break;
        case 'B':
            bid(i, &L);
            break;
        case 'S':
            stats(L);
            break;
        default:
            break;
    }
}

//______________________________________________________________________________________________________________________

void readTasks(char *filename) {
    FILE *f = NULL;
    char *commandNumber, *command, *param1, *param2, *param3, *param4;
    const char delimiters[] = " \n\r";
    char buffer[MAX_BUFFER];

    f = fopen(filename, "r");

    if (f != NULL) {

        while (fgets(buffer, MAX_BUFFER, f)) {
            commandNumber = strtok(buffer, delimiters);
            command = strtok(NULL, delimiters);
            param1 = strtok(NULL, delimiters);
            param2 = strtok(NULL, delimiters);
            param3 = strtok(NULL, delimiters);
            param4 = strtok(NULL, delimiters);

            processCommand(commandNumber, command[0], param1, param2, param3, param4);
        }

        fclose(f);

    } else {
        printf("Cannot open file %s.\n", filename);
    }
}

//______________________________________________________________________________________________________________________

int main(int nargs, char **args) {

    char *file_name = "new.txt";

    if (nargs > 1) {
        file_name = args[1];
    } else {
#ifdef INPUT_FILE
        file_name = INPUT_FILE;
#endif
    }

    readTasks(file_name);

    return 0;
}