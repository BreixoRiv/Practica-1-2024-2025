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

void assignItem(tItemL *i, char *param1, char *param2, char *param3, char *param4) {
    strcpy(i -> consoleId, param1);
    strcpy(i -> seller, param2);

    if (strcmp(param3, "sega") == 0) {
        i -> consoleBrand = 1;
    }
    else {
        i -> consoleBrand = 0;
    }
    i -> consolePrice = atof(param4);
}

//______________________________________________________________________________________________________________________

void new (char *param1, char *param2, char *param3, char *param4, tList *L) {
    tItemL i;
    assignItem(&i, param1, param2, param3, param4); //Asigna los valores a los campos del ítem
    char brand[10];

    i.bidCounter = 0; //Ajusta el contador de pujas a 0

    if (findItem(i.consoleId, *L) == LNULL && insertItem(i, LNULL, L) == true) { //Si no existe el ítem y se pudo insertar, se imprime lo que se insertó
        if (i.consoleBrand == 0) {
            strcpy(brand, "nintendo");
        }
        else {
            strcpy(brand, "sega");
        }
        printf("* New: console %s seller %s brand %s price %.2f\n", i.consoleId, i.seller, brand, i.consolePrice);
    }
    else { //Si no fue posible, se imprime un error;
        printf("+ Error: New not possible\n");
    }
}

//______________________________________________________________________________________________________________________

void delete (char *consoleId, tList *L) {
    char brandC[10];
    tPosL p = findItem(consoleId, *L);
    tItemL i;
    if (p != LNULL) {
        i = getItem(p, *L);
        if (i.consoleBrand == 0) {
            strcpy(brandC, "nintendo");
        }
        else {
            strcpy(brandC, "sega");
        }
        printf("* Delete: console %s seller %s brand %s price %.2f bids %d\n", consoleId, i.seller, brandC, i.consolePrice, i.bidCounter);
        deleteAtPosition(p, L);
    }
    else {
        printf("+ Error: Delete not possible\n");
    }
}

//______________________________________________________________________________________________________________________

void bid (char *consoleId, char *bidder, char *price, tList *L) {
    tPosL p = findItem(consoleId, *L);
    tItemL i = getItem(p, *L);
    char brand[10];

    if (findItem(consoleId, *L) != LNULL && strcmp(i.seller, bidder) != 0 && i.consolePrice < atof(price)) {
        i.consolePrice = atof(price);
        i.bidCounter++;
        updateItem(i, findItem(i.consoleId, *L), L);
        if (i.consoleBrand == 0) {
            strcpy(brand, "nintendo");
        }
        else {
            strcpy(brand, "sega");
        }

        printf("* Bid: console %s seller %s brand %s price %.2f bids %d\n", i.consoleId, i.seller, brand, i.consolePrice, i.bidCounter);
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
        char brand[10];

        int nintendo = 0;
        int sega = 0;
        float pNintendo = 0;
        float pSega = 0;
        float medNintendo = 0;
        float medSega = 0;

        while (p != LNULL) {
            i = getItem(p, L);
            if (i.consoleBrand == 0) {
                strcpy(brand, "nintendo");
            }
            else {
                strcpy(brand, "sega");
            }
            printf("Console %s seller %s brand %s price %.2f bids %d\n", i.consoleId, i.seller, brand, i.consolePrice, i.bidCounter);
            if (i.consoleBrand == 0) {
                nintendo++;
                pNintendo += i.consolePrice;
            }
            else if (i.consoleBrand == 1) {
                sega++;
                pSega += i.consolePrice;
            }
            p = next(p, L);
        }

        if (nintendo != 0) {
            medNintendo = pNintendo / nintendo;
        }

        if (sega != 0) {
            medSega = pSega / sega;
        }
        printf("\nBrand     Consoles    Price  Average\n");
        printf("Nintendo  %8d %8.2f %8.2f\n", nintendo, pNintendo, medNintendo);
        printf("Sega      %8d %8.2f %8.2f\n", sega, pSega, medSega);
    }
    else {
        printf("+ Error: Stats not possible\n");
    }
}

//______________________________________________________________________________________________________________________

void processCommand(char *commandNumber, char command, char *param1, char *param2, char *param3, char *param4, tList *L) {

    switch (command) {
        case 'N':
            printf("********************\n");
            printf("%s %c: console %s seller %s brand %s price %s\n", commandNumber, command, param1, param2, param3, param4);
            new(param1, param2, param3, param4, L);
        break;
        case 'D':
            printf("********************\n");
            printf("%s %c: console %s\n", commandNumber, command, param1);
            delete(param1, L);
            break;
        case 'B':
            printf("********************\n");
            printf("%s %c: console %s bidder %s price %.2f\n", commandNumber, command, param1, param2, atof(param3));
            bid(param1, param2, param3, L);
            break;
        case 'S':
            printf("********************\n");
            printf("%s %c\n", commandNumber, command);
            stats(*L);
            break;
        default:
            break;
    }
}

//______________________________________________________________________________________________________________________

void readTasks(char *filename, tList *L) {
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

            processCommand(commandNumber, command[0], param1, param2, param3, param4, L);

        }

        fclose(f);

    } else {
        printf("Cannot open file %s.\n", filename);
    }
}

//______________________________________________________________________________________________________________________

int main(int nargs, char **args) {
    tList L;
    createEmptyList(&L);

    char *file_name = "delete.txt";

    if (nargs > 1) {
        file_name = args[1];
    } else {
#ifdef INPUT_FILE
        file_name = INPUT_FILE;
#endif
    }

    readTasks(file_name, &L);

    return 0;
}