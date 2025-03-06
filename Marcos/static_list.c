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
//______________________________________________________________________________________________________________________
void  createEmptyList(tList *r) {
    r -> lastPos = LNULL;
}
//______________________________________________________________________________________________________________________
bool isEmptyList(tList r) {
    return (r.lastPos==LNULL);
}
//______________________________________________________________________________________________________________________
tPosL first(tList r) {
    return 0;
}
//______________________________________________________________________________________________________________________
tPosL last(tList r) {
return r.lastPos;
}
//______________________________________________________________________________________________________________________
tPosL previous(tPosL a,tList r) {
    if (a==0) {
        return LNULL;
    }
    else {
        return --a;
    }
}
//______________________________________________________________________________________________________________________
tPosL next(tPosL a,tList r) {
    if (a==r.lastPos) {
        return LNULL;
    }
    else {
        return ++a;
    }
}
//______________________________________________________________________________________________________________________
tItemL getItem(tPosL a, tList r) {
    return r.data[a];
}
//______________________________________________________________________________________________________________________
void deleteaPosicion(tPosL a, tList *r) {
    for (int i=a; i < r -> lastPos; i++) {
        r->data[i]=r->data[i+1];
    }
    r -> lastPos--;
}
//______________________________________________________________________________________________________________________
void updateItem (tItemL i, tPosL p, tList *r) {
r->data[p]=i;
}
//______________________________________________________________________________________________________________________
tPosL findItem(tConsoleId c,tList r) {
    tPosL q=0;
    if (r.lastPos==LNULL) {
        return LNULL;
    }
    else {
        while (q<r.lastPos+1 && strcmp(r.data[q].consoleId, c)!=0){
            q++;
        }
        if (q==r.lastPos+1) {
            return LNULL;
        }
        else {
            return q;
        }
    }
}
//______________________________________________________________________________________________________________________
bool insertItem(tItemL i,tPosL p,tList *r) {
    if (r -> lastPos == MAX-1) {
        return false;
    }
    else {
        r->lastPos++;
        if (p==LNULL) {
            r -> data[ r -> lastPos] = i;
        }
        else {
            for (int a=r -> lastPos; a > p; --a) {
                r->data[a] = r->data[a-1];
            }
            r->data[p] = i;
        }
        return true;
    }
}