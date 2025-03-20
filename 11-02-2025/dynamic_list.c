/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: González Monné, Marcos LOGIN 1: marcos.gonzalez.monne
 * AUTHOR 2: Riveiro Primoy, Breixo LOGIN 2: breixo.riveirop
 * GROUP: 1.4
 * DATE: 13 / 03 / 25
 */

#include "dynamic_list.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

//______________________________________________________________________________________________________________________
/* Tipo: Generadora
 * Objetivo: Inicializar una lista vacía
 * Entradas: La dirección de memoria de la lista a inicializar
 * Salidas: La lista inicializada
 * Postcondiciones: La lista queda inicializada y vacía
 */

void createEmptyList (tList *L) {
    *L = LNULL;
}

//______________________________________________________________________________________________________________________
/* Tipo: Observadora
 * Objetivo: Comprobar si la lista está vacía
 * Entrada: La lista a comprobar
 * Salida: Devuelve TRUE si la lista está vacía y FALSE si no lo está
 * Precondición: La lista debe estar inicializada por el createEmptyList
 */

bool isEmptyList (tList L) {
    return (L == LNULL);
}

//______________________________________________________________________________________________________________________
/* Tipo: Observadora
 * Objetivo: Obtener la primera posición de la lista
 * Entrada: La lista de la que se obtendrá la primera posición
 * Salida: La primera posición de la lista (que siempre es 0 en una lista estática)
 * Precondiciones: La lista debe estar inicializada por el createEmptyList y no puede estar vacía
 */

tPosL first (tList L) {
    return L;
}

//______________________________________________________________________________________________________________________
/* Tipo: Observadora
 * Objetivo: Obtener la última posición de la lista
 * Entrada: La lista de la que se obtendrá la última posición
 * Salida: La última posición de la lista (la cual se almacena en lastPos en una lista estática)
 * Precondiciones: La lista debe estar inicializada por el createEmptyList y no puede estar vacía
 */

tPosL last (tList L) {
    tPosL q = L;

    while (q -> next != LNULL) { //Recorre la lista hasta llegar a la última posición (la anterior a una posición nula)
        q = q -> next;
    }
    return q;
}

//______________________________________________________________________________________________________________________
/* Tipo: Observadora
 * Objetivo: Obtener la posición siguiente a la indicada
 * Entrada: La lista y la posición en la lista de la que se quiere obtener la siguiente
 * Salida: La siguiente posición a la indicada o LNULL si la posición indicada es la última
 * Precondiciones: La lista debe estar inicializada por el createEmptyList y la posición indicada tiene que ser válida
 */

tPosL next (tPosL p, tList L) {
    return p -> next;
}

//______________________________________________________________________________________________________________________
/* Tipo: Observadora
 * Objetivo: Obtener la posición anterior a la indicada
 * Entrada: La lista y la posición en la lista de la que se quiere obtener la anterior
 * Salida: La posición anterior a la indicada o LNULL si la posición indicada es la primera
 * Precondiciones: La lista debe estar inicializada por el createEmptyList y la posición indicada tiene que ser válida
 */

tPosL previous (tPosL p, tList L) {
    if (p == L) {
        return LNULL;
    }
    else { //Si la posición no es la primera, recorre la lista hasta llegar a la posición anterior (en la que el valor de next es la posición indicada)
        tPosL q = L;

        while (q -> next != p) {
            q = q -> next;
        }

        return q;
    }
}

//______________________________________________________________________________________________________________________
/* Tipo: Generadora
 * Objetivo : Crear un nodo
 * Entrada : La dirección de memoria de la posición en la que se creará el nodo
 * Salida : Devuelve TRUE si se ha podido crear el nodo y FALSE si no
 * Precondición : La posición debe ser válida
 */

bool createNode (tPosL* p) {
    *p = malloc(sizeof(**p)); //Reserva memoria para un nodo
    return *p != LNULL;
}

//______________________________________________________________________________________________________________________
/* Tipo: Modificadora
 * Objetivo: Añadir un item a la lista en la posición indicada
 * Entrada: El ítem a añadir, la posición en la que se añadirá y la dirección de memoria de la lista en la que se añadirá
 * Salida: Devuelve TRUE junto con la lista con el ítem añadido en la posición indicada si se pudo añadir correctamente y false si no
 * Precondición: La lista debe estar inicializada por el createEmptyList y la posición indicada ser válida o nula
 * Postcondición: Las posiciones de los ítems posteriores al insertado pueden variar
 */

bool insertItem (tItemL i, tPosL p, tList *L) {
    tPosL q, r;

    if (!createNode(&q)) {
        return false;
    }
    else {
        q -> data = i;
        q -> next = LNULL;
        r = *L;

        if (*L == LNULL) { //Si la lista está vacía, se inserta en la primera posición
            *L = q;
        }
        else if (p == LNULL) { //Si la posición indicada es nula, se añade a la última posición
            while (r -> next != LNULL) {
                r = r -> next;
            }
            r -> next = q;
        }
        else { //En cualquier otro caso, se añade en la posición indicada y se mueven los ítems siguientes
            q -> data = p -> data;
            p -> data = i;
            q -> next = p -> next;
            p -> next = q;
        }
        return true;
    }
}

//______________________________________________________________________________________________________________________
/* Tipo: Destructora
 * Objetivo: Eliminar el ítem correspondiente a la posición indicada de la lista
 * Entrada: La posición del ítem que se va a eliminar y la dirección de memoria de la lista de la que se va a eliminar
 * Salida: La lista con el ítem eliminado
 * Precondición: La lista debe estar inicializada por el createEmptyList y la posición indicada ser válida
 * Postcondición: Las posiciones de los ítems posteriores al eliminado pueden variar
 */

void deleteAtPosition (tPosL p, tList *L) {
    tPosL q;

    if (p == first(*L)) { //Si la posición es la primera, se sobreescribe el primer ítem con el segundo
        *L = (*L) -> next;
    }
    else if (p -> next == LNULL) { //Si la posición es la última, se elimina el último ítem
        q = *L;

        while (q -> next != p) { //Recorre la lista para encontrar el penúltimo ítem
            q = q -> next;
        }
        q -> next = LNULL;
    }
    else { //En cualquier otro caso, se sobreescribe el ítem con el siguiente
        q = p -> next;
        p -> data = q -> data;
        p -> next = q -> next;
        p = q;
    }
    free(p); //Libera la memoria del ítem eliminado
}

//______________________________________________________________________________________________________________________
/* Tipo: Observadora
 * Objetivo: Obtener el ítem correspondiente a una posición
 * Entrada: La posición del ítem que se quiere obtener y la lista de la que se va a obtener el ítem
 * Salida: El ítem correspondiente a la posición indicada en la lista
 * Precondición: La lista debe estar inicializada por el createEmptyList y la posición indicada ser válida
 */

tItemL getItem (tPosL p, tList L) {
    return (p -> data);
}

//______________________________________________________________________________________________________________________
/* Tipo: Modificadora
 * Objetivo: Editar el contenido de un ítem
 * Entrada: Un ítem con los valores modificados, la posición del ítem que se va a editar y la dirección de memoria de la lista en la que se va a editar
 * Salida: La lista con el ítem modificado
 * Precondición: La lista debe estar inicializada por el createEmptyList y la posición indicada es válida
 * Postcondición: El orden de los elementos de la lista no se puede modificar
 */

void updateItem (tItemL i, tPosL p, tList *L) {
    p -> data = i;
}

//______________________________________________________________________________________________________________________
/* Tipo: Observadora
 * Objetivo: Obtener la posición de un ítem
 * Entrada: El ítem que se quiere encontrar y la lista en la que se buscará
 * Salida: La posición del ítem buscado, en caso de que exista, o LNULL en caso de no existir
 * Precondición: La lista debe estar inicializada por el createEmptyList y la posición indicada es válida
 */

tPosL findItem (tConsoleId c, tList L) {
    tPosL q = L;

    while (q != LNULL && strcmp(q -> data.consoleId, c) != 0) { //Recorre la lista hasta encontrar un ítem igual al indicado
        q = q -> next;
    }

    return q;
}