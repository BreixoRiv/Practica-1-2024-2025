/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: González Monné, Marcos LOGIN 1: marcos.gonzalez.monne
 * AUTHOR 2: Riveiro Primoy, Breixo LOGIN 2: breixo.riveirop
 * GROUP: 1.4
 * DATE: 06 / 03 / 25
 */

#include "static_list.h"
#include <string.h>

//______________________________________________________________________________________________________________________
/* Objetivo: Inicializar una lista vacía
 * Entradas: La lista a inicializar
 * Salidas: La lista inicializada
 * Postcondiciones: La lista queda inicializada y vacía
 */

void createEmptyList (tList *L) {
    L -> lastPos = LNULL;
}

//______________________________________________________________________________________________________________________
/* Objetivo: Comprobar si la lista está vacía
 * Entrada: La lista a comprobar
 * Salida: Devuelve TRUE si la lista está vacía y FALSE si no lo está
 * Precondición: La lista debe estar inicializada por el createEmptyList
 */

bool isEmptyList (tList L) {
    return (L.lastPos == LNULL);
}

//______________________________________________________________________________________________________________________
/* Objetivo: Obtener la primera posición de la lista
 * Entrada: La lista de la que se obtendrá la primera posición
 * Salida: La primera posición de la lista (que siempre es 0 en una lista estática)
 * Precondiciones: La lista debe estar inicializada por el createEmptyList y no puede estar vacía
 */

tPosL first (tList L) {
    return 0;
}

//______________________________________________________________________________________________________________________
/* Objetivo: Obtener la última posición de la lista
 * Entrada: La lista de la que se obtendrá la última posición
 * Salida: La última posición de la lista (la cual se almacena en lastPos en una lista estática)
 * Precondiciones: La lista debe estar inicializada por el createEmptyList y no puede estar vacía
 */

tPosL last (tList L) {
    return L.lastPos;
}

//______________________________________________________________________________________________________________________
/* Objetivo: Obtener la posición siguiente a la indicada
 * Entrada: La lista y la posición en la lista de la que se quiere obtener la siguiente
 * Salida: La siguiente posición a la indicada o LNULL si la posición indicada es la última
 * Precondiciones: La lista debe estar inicializada por el createEmptyList y la posición indicada tiene que ser válida
 */

tPosL next (tPosL p, tList L) {
    if (p == L.lastPos) {
        return LNULL;
    }
    else {
        return ++p;
    }
}

//______________________________________________________________________________________________________________________
/* Objetivo: Obtener la posición anterior a la indicada
 * Entrada: La lista y la posición en la lista de la que se quiere obtener la anterior
 * Salida: La posición anterior a la indicada o LNULL si la posición indicada es la primera
 * Precondiciones: La lista debe estar inicializada por el createEmptyList y la posición indicada tiene que ser válida
 */

tPosL previous (tPosL p, tList L) {
    if (p == 0) {
        return LNULL;
    }
    else {
        return --p;
    }
}

//______________________________________________________________________________________________________________________
/* Objetivo: Añadir un item a la lista en la posición indicada
 * Entrada: El ítem a añadir, la posición en la que se añadirá y la lista en la que se añadirá
 * Salida: Devuelve TRUE junto con la lista con el ítem añadido en la posición indicada si se pudo añadir correctamente y false si no
 * Precondición: La lista debe estar inicializada por el createEmptyList y la posición indicada ser válida o nula
 * Postcondición: Las posiciones de los ítems posteriores al insertado pueden variar
 */

bool insertItem (tItemL i, tPosL p, tList *L) {
    if (L -> lastPos == MAX - 1) {
        return false;
    }
    else {
        L -> lastPos++;
        if (p == LNULL) { //Si la posición es nula añade el ítem al final
            L -> data[L -> lastPos] = i;
        }
        else { //Si no lo es, lo añade en la posición indicada y desplaza los ítems que se encuentren después
            for (tPosL q = L -> lastPos; q > p; q--) {
                L -> data[q] = L -> data[q - 1];
            }
            L -> data[p] = i;
        }
        return true;
    }
}

//______________________________________________________________________________________________________________________
/* Objetivo: Eliminar el ítem correspondiente a la posición indicada de la lista
 * Entrada: La posición del ítem que se va a eliminar y la lista de la que se va a eliminar
 * Salida: La lista con el ítem eliminado
 * Precondición: La lista debe estar inicializada por el createEmptyList y la posición indicada ser válida
 * Postcondición: Las posiciones de los ítems anteriores al eliminado pueden variar
 */

void deleteAtPosition (tPosL p, tList *L) {
    for (tPosL q = p; q < L -> lastPos; q++) { //Recorre la lista hasta llegar al ítem indicado y lo elimina moviendo el resto de ítems
        L -> data[q] = L -> data[q + 1];
    }

    L -> lastPos--;
}

//______________________________________________________________________________________________________________________
/* Objetivo: Obtener el ítem correspondiente a una posición
 * Entrada: La posición del ítem que se quiere obtener y la lista de la que se va a obtener el ítem
 * Salida: El ítem correspondiente a la posición indicada en la lista
 * Precondición: La lista debe estar inicializada por el createEmptyList y la posición indicada ser válida
 */

tItemL getItem (tPosL p, tList L) {
    return L.data[p];
}

//______________________________________________________________________________________________________________________
/* Objetivo: Editar el contenido de un ítem
 * Entrada: Un ítem con los valores modificados, la posición del ítem que se va a editar y la lista en la que se va a editar
 * Salida: La lista con el ítem modificado
 * Precondición: La lista debe estar inicializada por el createEmptyList y la posición indicada es válida
 * Postcondición: El orden de los elementos de la lista no se puede modificar
 */

void updateItem (tItemL i, tPosL p, tList *L) {
    L -> data[p] = i;
}

//______________________________________________________________________________________________________________________
/* Objetivo: Obtener la posición de un ítem
 * Entrada: El ítem que se quiere encontrar y la lista en la que se buscará
 * Salida: La posición del ítem buscado, en caso de que exista, o LNULL en caso de no existir
 * Precondición: La lista debe estar inicializada por el createEmptyList y la posición indicada es válida
 */

tPosL findItem (tConsoleId c, tList L) {
    tPosL q = 0;

    if (L.lastPos == LNULL) {
        return LNULL;
    }
    else { //Recorre la lista hasta encontrar el ítem con el id indicado
        while (q < L.lastPos + 1 && strcmp(L.data[q].consoleId, c) != 0) {
            q++;
        }
        if (q == L.lastPos + 1) { //Si no lo encuentra devuelve LNULL
            return LNULL;
        }
        else { //Si lo encuentra devuelve la posición
            return q;
        }
    }
}