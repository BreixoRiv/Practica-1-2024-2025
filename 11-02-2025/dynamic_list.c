/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: González Monné, Marcos LOGIN 1: marcos.gonzalez.monne
 * AUTHOR 2: Riveiro Primoy, Breixo LOGIN 2: breixo.riveirop
 * GROUP: 1.4
 * DATE: 06 / 03 / 25
 */

#include "dynamic_list.h"
#include <stdbool.h>

//______________________________________________________________________________________________________________________

void createEemptyList (tList *L) {
    *L = LNULL;
}

//______________________________________________________________________________________________________________________

bool isEmptyList (tList L) {
    return (L == LNULL);
}

//______________________________________________________________________________________________________________________

tPosL first (tList L) {
    return L;
}

//______________________________________________________________________________________________________________________

tPosL last (tList L) {
    tPosL q = L;

    while (L -> next != LNULL) {
        q = q -> next;
    }
    return q;
}

//______________________________________________________________________________________________________________________

tPosL next (tPosL p, tList L) {
    return L -> next;
}

//______________________________________________________________________________________________________________________

tPosL previous (tPosL p, tList L) {
    if (p == L) {
        return LNULL;
    }
    else {
        tPosL q = L;

        while (q -> next != p) {
            q = q -> next;
        }

        return q;
    }
}

//______________________________________________________________________________________________________________________

bool insertItem (tItemL i, tPosL p, tList *L) {
