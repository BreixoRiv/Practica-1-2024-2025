/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: ***************************** LOGIN 1: **********
 * AUTHOR 2: ***************************** LOGIN 2: **********
 * GROUP: *.*
 * DATE: ** / ** / **
 */

#include "static_list.h"

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
        return p++; //La posición insertada +1 en cualquier otro caso
    }
}

//______________________________________________________________________________________________________________________

tPosL previous (tPosL p, tList L) { //Devuelve la posición anterior
    if (p == 0) {
        return LNULL; //LNULL en caso de que la posición indicada sea la primera
    }
    else {
        return p--; //La posición insertada -1 en cualquier otro caso
    }
}

//______________________________________________________________________________________________________________________

bool insertItem (tItemL i, tPosL p, tList *L) { //Añade un item a la lista en la posición indicada
    if (L -> lastPos == MAX - 1) {
        return false;
    }
    else {
        L -> lastPos++;
        if (p == LNULL) {
            L -> data[L -> lastPos] = i;
        }
        else {
            for (tPosL q = L -> lastPos; q > p; q--) {
                L -> data[q] = L -> data[q - 1];
            }
            L -> data[p] = i;
        }
        return true;
    }
}

//______________________________________________________________________________________________________________________

void deleteAtPosition (tPosL p, tList *L) {
    for (tPosL q = p; q < L -> lastPos; q++) {
        L -> data[q] = L -> data[q + 1];
    }

    L -> lastPos--;
}

//______________________________________________________________________________________________________________________

tItemL getItem (tPosL p, tList L) {
    return L.data[p];
}

//______________________________________________________________________________________________________________________

void updateItem (tItemL i, tPosL p, tList *L) {
    L -> data[p] = i;
}

//______________________________________________________________________________________________________________________

tPosL findItem (tConsoleId c, tList L) {
    tPosL q = 0;
    if (L.lastPos == LNULL) {
        return LNULL;
    }
    else {
        while (L.data[q].seller != c) {
            q++;
        }
        return q;
    }
}