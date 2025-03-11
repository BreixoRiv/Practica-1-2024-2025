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
#include <stdlib.h>
#include <string.h>

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

bool createNode (tPosL* p) {
    *p = malloc(sizeof(**p));
    return *p != LNULL;
}

//______________________________________________________________________________________________________________________

bool insertItem (tItemL i, tPosL p, tList *L) {
    tPosL q, r;

    if (!createNode(&q)) {
        return false;
    }
    else {
        q -> data = i;
        q -> next = LNULL;

        if (*L == LNULL) {
            *L = q;
        }
        else if (p == LNULL) {
            r = *L;

            while (r -> next != LNULL) {
                r -> next = q;
                r = r -> next;
            }
        }
        else if (p == *L) {
            q -> next = *L;
            *L = q;
        }
        else {
            q -> data = p -> data;
            p -> data = i;
            q -> next = p -> next;
            p -> next = q;
        }
        return true;
    }
}

//______________________________________________________________________________________________________________________

void deleteAtPosition (tPosL p, tList *L) {
    tPosL q;

    if (p == first(*L)) {
        *L = (*L) -> next;
    }
    else if (p -> next == LNULL) {
        q = *L;

        while (q -> next != p) {
            q = q -> next;
        }
        q -> next = LNULL;
    }
    else {
        q = p -> next;
        p -> data = q -> data;
        p -> next = q -> next;
        p = q;
    }
    free(p);
}

//______________________________________________________________________________________________________________________

tItemL getItem (tPosL p, tList L) {
    return p -> data;
}

//______________________________________________________________________________________________________________________

void updateItem (tItemL i, tPosL p, tList *L) {
    p -> data = i;
}

//______________________________________________________________________________________________________________________

tPosL findItem (tConsoleId c, tList L) {
    tPosL q = L;

    while (q != LNULL && strcmp(q -> data.consoleId, c) != 0) {
        q = q -> next;
    }

    return q;
}