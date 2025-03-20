/*
* TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: González Monné, Marcos LOGIN 1: marcos.gonzalez.monne
 * AUTHOR 2: Riveiro Primoy, Breixo LOGIN 2: breixo.riveirop
 * GROUP: 1.4
 * DATE: 20 / 03 / 25
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
/* Tipo: Modificadora
 * Objetivo: Asignar a una variable ítem los valores de los parámetros
 * Entrada: Cada uno de los parámetros a asignar y el ítem vacío
 * Salida: El ítem con los valores asignados
 * Precondiciones: El ítem debe estar inicializado
 * Postcondiciones: El ítem queda con los valores asignados
 */

void assignItem(tItemL *i, char *Id, char *seller, char *brand, char *price, int bidCounter) {
    strcpy(i -> consoleId, Id); //Se le asigna el valor de Id al identificador (consoleId) del ítem
    strcpy(i -> seller, seller); //Se le asigna el valor de seller al vendedor (seller) del ítem

    if (strcmp(brand, "sega") == 0) { //Si la consola es de Sega se le asigna el valor 1 a consoleBrand en el ítem
        i -> consoleBrand = 1;
    }
    else {
        i -> consoleBrand = 0; //En caso contrario, la consola es de Nintendo y se le asigna un 0
    }

    i -> consolePrice = atof(price); //Se le asigna el valor de price convertido a float al precio (consolePrice) del ítem
    i -> bidCounter = bidCounter; //Se le asigna el valor de bidCounter al contador de pujas (bidCounter) del ítem
}

//______________________________________________________________________________________________________________________
/* Tipo: Observadora
 * Objetivo: Obtener el nombre de la marca a partir del número asociado a esta
 * Entrada: La variable donde se almacenará el nombre de la marca y el número asociado a la marca
 * Salida: El nombre de la marca
 * Precondición: El número asociado a la marca debe ser 0 o 1
 */

void brandName(char *brand, tConsoleBrand itemBrand) {
    if (itemBrand == 0) { //Si el número asociado a la marca es 0, la marca es Nintendo
        strcpy(brand, "nintendo");
    }
    else { //Si no, la marca es Sega
        strcpy(brand, "sega");
    }
}

//______________________________________________________________________________________________________________________
/* Tipo: Modificadora
 * Objetivo: Añadir un nuevo ítem a la lista indicada
 * Entrada: Los parámetros del ítem a añadir y la lista en la que se añadirán
 * Salida: La lista con el ítem añadido
 * Precondición: La lista debe estar inicializada por el createEmptyList (se encuentra en la función main)
 * Postcondición: La lista queda con el ítem añadido
 */

void new (char *param1, char *param2, char *param3, char *param4, tList *L) {
    tItemL i;
    char brand[NAME_LENGTH_LIMIT];
    assignItem(&i, param1, param2, param3, param4, 0); //Asigna los valores a los campos del ítem

    if (findItem(i.consoleId, *L) == LNULL && insertItem(i, LNULL, L) == true) { //Si no existe el ítem y se pudo insertar, se imprime el ítem insertado
        brandName(&brand, i.consoleBrand); //Se cambia el valor de consoleBrand (entero) por el nombre de la marca

        printf("* New: console %s seller %s brand %s price %.2f\n", i.consoleId, i.seller, brand, i.consolePrice);
    }
    else { //Si no fue posible, se imprime un error;
        printf("+ Error: New not possible\n");
    }
}

//______________________________________________________________________________________________________________________
/* Tipo: Destructora
 * Objetivo: Eliminar un ítem de la lista indicada
 * Entrada: El identificador del ítem a eliminar y la lista de la que se eliminará
 * Salida: La lista con el ítem eliminado
 * Precondición: La lista debe estar inicializada por el createEmptyList (se encuentra en la función main)
 * Postcondición: La posición de los ítems posteriores puede verse modificada
 */

void delete (char *consoleId, tList *L) {
    char brand[NAME_LENGTH_LIMIT];
    tItemL i;
    tPosL p = findItem(consoleId, *L); //Se busca la posición del ítem a eliminar. En caso de no existir, p será LNULL

    if (p != LNULL) { //Si el ítem se encuentra en la lista, se imprime el ítem a eliminar y se elimina
        i = getItem(p, *L);

        brandName(&brand, i.consoleBrand); //Se cambia el valor de consoleBrand (entero) por el nombre de la marca

        printf("* Delete: console %s seller %s brand %s price %.2f bids %d\n", consoleId, i.seller, brand, i.consolePrice, i.bidCounter);
        deleteAtPosition(p, L);
    }
    else { //En caso de no existir, se imprime un error
        printf("+ Error: Delete not possible\n");
    }
}

//______________________________________________________________________________________________________________________
/* Tipo: Modificadora
 * Objetivo: Añadir una puja a un ítem de la lista indicada
 * Entrada: El identificador del ítem a pujar, el pujador, el precio de la puja y la lista en la que se modificará el ítem
 * Salida: La lista con el ítem modificado
 * Precondición: La lista debe estar inicializada por el createEmptyList (se encuentra en la función main)
 * Postcondición: El ítem queda con el precio y el contador de pujas modificados
 */

void bid (char *consoleId, char *bidder, char *price, tList *L) {
    tPosL p = findItem(consoleId, *L);
    tItemL i = getItem(p, *L);
    char brand[NAME_LENGTH_LIMIT];

    if (p != LNULL && strcmp(i.seller, bidder) != 0 && i.consolePrice < atof(price)) { //Si el item existe, el precio de la puja es mayor que el precio actual de la consola y el vendedor no es la misma persona que el pujador, se modificará el ítem con la nueva puja
        i.consolePrice = atof(price);
        i.bidCounter++;
        updateItem(i, p, L);

        brandName(&brand, i.consoleBrand); //Se cambia el valor de consoleBrand (entero) por el nombre de la marca

        printf("* Bid: console %s seller %s brand %s price %.2f bids %d\n", i.consoleId, i.seller, brand, i.consolePrice, i.bidCounter); //Se imprime el ítem modificado
    }
    else { //En caso de que no se cumpla alguna de las condiciones, se imprime un mensaje de error
        printf("+ Error: Bid not possible\n");
    }
}

//______________________________________________________________________________________________________________________
/* Tipo: Observadora
 * Objetivo: Mostrar las estadísticas de la lista indicada
 * Entrada: La lista de la que se mostrarán las estadísticas
 * Precondición: La lista debe estar inicializada por el createEmptyList (se encuentra en la función main)
 */

void stats (tList L) {
    if (!isEmptyList(L)) { //Si la lista no es nula, se mostrarán las estadísticas
        tPosL p = first(L);
        tItemL i;
        char brand[NAME_LENGTH_LIMIT];

        //Creación de los contadores de las estadísticas
        int nintendo = 0;
        int sega = 0;
        float pNintendo = 0;
        float pSega = 0;
        float medNintendo = 0;
        float medSega = 0;

        while (p != LNULL) { //Se cuentan las distintas variables mientras que la posición no sea nula
            i = getItem(p, L);
            brandName(&brand, i.consoleBrand); //Se cambia el valor de consoleBrand (entero) por el nombre de la marca

            printf("Console %s seller %s brand %s price %.2f bids %d\n", i.consoleId, i.seller, brand, i.consolePrice, i.bidCounter);

            if (i.consoleBrand == 0) { //Si la consola es de Nintendo (0), se sumará 1 al contador de consolas de Nintendo y se le sumará el precio al total
                nintendo++;
                pNintendo += i.consolePrice;
            }
            else if (i.consoleBrand == 1) { //Si la consola es de Sega (1), se sumará 1 al contador de consolas de Sega y se le sumará el precio al total
                sega++;
                pSega += i.consolePrice;
            }

            p = next(p, L); //Avanza a la siguiente posición
        }

        if (nintendo != 0) { //Se calcula la media de los precios de las consolas de Nintendo si hay alguna
            medNintendo = pNintendo / nintendo;
        }

        if (sega != 0) { //Se calcula la media de los precios de las consolas de Sega si hay alguna
            medSega = pSega / sega;
        }

        //Se imprimen los valores de la marca, la cantidad de consolas, el precio de todas y la media de los precios
        printf("\nBrand     Consoles    Price  Average\n");
        printf("Nintendo  %8d %8.2f %8.2f\n", nintendo, pNintendo, medNintendo);
        printf("Sega      %8d %8.2f %8.2f\n", sega, pSega, medSega);
    }
    else { //Si no es posíble, se imprime un mensaje de error
        printf("+ Error: Stats not possible\n");
    }
}

//______________________________________________________________________________________________________________________
/* Tipo: Observadora
 * Objetivo: Procesar los comandos leídos del archivo de entrada
 * Entrada: El número de comando, el comando del proceso a realizar, los 4 parámetros que puede tener un comando y la lista en la que se realizarán los comandos
 * Precondición: La lista debe estar inicializada por el createEmptyList (se encuentra en la función main)
 * Postcondición: Todas las funciones de los commandos se realizan correctamente
 */

void processCommand(char *commandNumber, char command, char *param1, char *param2, char *param3, char *param4, tList *L) {
    switch (command) { //Identifica el proceso a realizar
        case 'N': //Añadir un nuevo ítem
            printf("********************\n");
            printf("%s %c: console %s seller %s brand %s price %s\n", commandNumber, command, param1, param2, param3, param4);
            new(param1, param2, param3, param4, L);
        break;
        case 'D': //Eliminar un ítem
            printf("********************\n");
            printf("%s %c: console %s\n", commandNumber, command, param1);
            delete(param1, L);
            break;
        case 'B': //Pujar por un ítem
            printf("********************\n");
            printf("%s %c: console %s bidder %s price %.2f\n", commandNumber, command, param1, param2, atof(param3));
            bid(param1, param2, param3, L);
            break;
        case 'S': //Mostrar las estadísticas
            printf("********************\n");
            printf("%s %c\n", commandNumber, command);
            stats(*L);
            break;
        default:
            break;
    }
}

//______________________________________________________________________________________________________________________
/* Tipo: Observadora
 * Objetivo: Leer los comandos del archivo de entrada
 * Entrada: El nombre del archivo de entrada y la lista en la que se realizarán los comandos
 * Precondición: La lista debe estar inicializada por el createEmptyList (se encuentra en la función main)
 * Postcondición: Todos los comandos del archivo se realizan correctamente
 */

void readTasks(char *filename, tList *L) {
    FILE *f = NULL;
    char *commandNumber, *command, *param1, *param2, *param3, *param4;
    const char delimiters[] = " \n\r"; //Asigna los delimitadores de las palabras (espacio, salto de línea y vuelta al inicio de la línea)
    char buffer[MAX_BUFFER];

    f = fopen(filename, "r");

    if (f != NULL) {

        while (fgets(buffer, MAX_BUFFER, f)) { //Lee cada línea por palabras (hastaa encontrar un delimitador) y realiza el proceso indicado en esa línea
            commandNumber = strtok(buffer, delimiters);
            command = strtok(NULL, delimiters);
            param1 = strtok(NULL, delimiters);
            param2 = strtok(NULL, delimiters);
            param3 = strtok(NULL, delimiters);
            param4 = strtok(NULL, delimiters);

            processCommand(commandNumber, command[0], param1, param2, param3, param4, L);

        }

        fclose(f);

    } else { //Si no se puede abrir el archivo imprime un error
        printf("Cannot open file %s.\n", filename);
    }
}

//______________________________________________________________________________________________________________________

int main(int nargs, char **args) {
    tList L;
    createEmptyList(&L); //Crea una lista vacía

    char *file_name = "delete.txt";

    if (nargs > 1) {
        file_name = args[1];
    } else {
#ifdef INPUT_FILE
        file_name = INPUT_FILE;
#endif
    }

    readTasks(file_name, &L); //Lee los comandos del archivo de entrada y realiza los procesos indicados

    return 0;
}