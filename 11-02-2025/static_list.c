/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: ***************************** LOGIN 1: **********
 * AUTHOR 2: ***************************** LOGIN 2: **********
 * GROUP: *.*
 * DATE: ** / ** / **
 */

#include "static_list.h"
#include <string.h>
#include <stdio.h>


//______________________________________________________________________________________________________________________

void createEmptyList (tList *L) { //Crea una lista vacía L
    L -> lastPos = LNULL;
}

//______________________________________________________________________________________________________________________

bool isEmptyList (tList L) { //Comprueba si la lista está vacía o no, y devuelve TRUE si lo está y FALSE si no
    return (L.lastPos == LNULL);
}

//______________________________________________________________________________________________________________________

tPosL first (tList L) { //Devuelve la primera posición de la lista, que siempre es 0
    return 0;
}

//______________________________________________________________________________________________________________________

tPosL last (tList L) { //Devuelve la última posición de la lista, que siempre está almacenada en L.lastPos
    return L.lastPos;
}

//______________________________________________________________________________________________________________________

tPosL next (tPosL p, tList L) { //Devuelve la siguinte posición
    if (p == L.lastPos) {
        return LNULL; //LNULL en caso de que la posición indicada sea la última
    }
    else {
        return ++p; //La posición insertada +1 en cualquier otro caso
    }
}

//______________________________________________________________________________________________________________________

tPosL previous (tPosL p, tList L) { //Devuelve la posición anterior
    if (p == 0) {
        return LNULL; //LNULL en caso de que la posición indicada sea la primera
    }
    else {
        return --p; //La posición insertada -1 en cualquier otro caso
    }
}

//______________________________________________________________________________________________________________________

bool insertItem (tItemL i, tPosL p, tList *L) { //Añade un item a la lista en la posición indicada
    if (L -> lastPos == MAX - 1) { //Si la lista ya contiene el máximo número de entradas devuelve FALSE
        return false;
    }
    else { //En caso contrario, añadirá el nuevo ítem en uno de los casos siguientes, aumentando la última posicíon en 1:
        L -> lastPos++;
        if (p == LNULL) { //Si se introduce LNULL como valor de la posición se añadirá como último ítem de la lista
            L -> data[L -> lastPos] = i;
        }
        else { //En caso contrario se buscará la posición indicada, se moverán todos los ítems siguientes una posición más y se añadirá el ítem en la posición indicada, devolviendo TRUE al final
            for (tPosL q = L -> lastPos; q > p; q--) {
                L -> data[q] = L -> data[q - 1];
            }
            L -> data[p] = i;
        }
        return true;
    }
}

//______________________________________________________________________________________________________________________

void deleteAtPosition (tPosL p, tList *L) { //Se elimina el ítem de la posición indicada, moviendo todos los ítems que lo siguieran una casilla menos y se reduce en 1 unidad el valor de la última posición
    for (tPosL q = p; q < L -> lastPos; q++) {
        L -> data[q] = L -> data[q + 1];
    }

    L -> lastPos--;
}

//______________________________________________________________________________________________________________________

tItemL getItem (tPosL p, tList L) { //Devuelve el ítem que ocupa la posición indicada
    return L.data[p];
}

//______________________________________________________________________________________________________________________

void updateItem (tItemL i, tPosL p, tList *L) { //Cambia los datos del ítem en la posición indicada por los indicados
    L -> data[p] = i;
}

//______________________________________________________________________________________________________________________

tPosL findItem (tConsoleId c, tList L) { //Busca la posición en la que se encuentra el ítem deseado
    tPosL q = 0;
    if (L.lastPos == LNULL) { //Si la última posición es LNULL la lista está vacía, por lo que se devuelve LNULL
        return LNULL;
    }
    else { //Si la lista no está vacía, se busca el ítem
        while (q < L.lastPos + 1 && strcmp(L.data[q].consoleId, c) != 0) {
            q++;
        }
        if (q == L.lastPos + 1) { //Si no se encuentra ningún ítem como el indicado, el valor de q será 1 más que la última posición, entonces se devolverá LNULL para indicar que no existe dicho ítem
            return LNULL;
        }
        else { //Si se encuentra el ítem en el while, se devuelve la posición
            return q;
        }
    }
}