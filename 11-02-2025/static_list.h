/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: ***************************** LOGIN 1: **********
 * AUTHOR 2: ***************************** LOGIN 2: **********
 * GROUP: *.*
 * DATE: ** / ** / **
 */

//______________________________________________________________________________________________________________________

#ifndef STATIC_LIST_H
#define STATIC_LIST_H

//______________________________________________________________________________________________________________________

#include "types.h"
#include <stdbool.h>

//______________________________________________________________________________________________________________________

#define tList tItemL
#define tPosL int
#define LNULL -1

//______________________________________________________________________________________________________________________

void createEmptyList (tList* L);

//______________________________________________________________________________________________________________________

bool isEmptyList (tList L);

//______________________________________________________________________________________________________________________

tPosL first (tList L);

//______________________________________________________________________________________________________________________

tPosL last (tList L);

//______________________________________________________________________________________________________________________

tPosL next (tPosL p, tList L);

//______________________________________________________________________________________________________________________

tPosL previous (tPosL p, tList L);

//______________________________________________________________________________________________________________________

bool insertItem (tItemL i, tPosL p, tList* L);

//______________________________________________________________________________________________________________________

bool deleteAtPosition (tPosL p, tList* L);

//______________________________________________________________________________________________________________________

tItemL getItem (tPosL p, tList* L);

//______________________________________________________________________________________________________________________

bool updateItem (tItemL i, tPosL p, tList* L);

//______________________________________________________________________________________________________________________

tPosL findItem (tConsoleId c, tList* L);

//______________________________________________________________________________________________________________________

#endif
