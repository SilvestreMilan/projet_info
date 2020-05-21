#ifndef _HEAP
#define _HEAP

#include <stdio.h>
#include <stdlib.h>
#include "element_BFS.h"

typedef
  struct {
    element_t* data;
    int max_size;
    int number;
  } heap_t;


heap_t heap_new(int m);				// retourne un tas vide
int heap_is_empty(heap_t tas);			// retourne 1 si le tas ets vide, 0 sinon
int heap_add(element_t valeur, heap_t* ptas);	// ajoute l'element valeur au tas pointe par ptas retourne 1 si c'est fait 0 si cela n'est pas possible
element_t heap_get_max(heap_t tas);
int heap_delete_max(heap_t* ptas);
int heap_verification(heap_t tas) ;
void heap_delete(heap_t* ptas);
void heap_print(heap_t tas) ;

#define HEAP_FATHER(i) ( ((i)-1)/2)
#define HEAP_LEFTSON(i) ( 2*(i)+1)
#define HEAP_RIGHTSON(i) ( 2*((i)+1))


#endif
