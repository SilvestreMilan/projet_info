#ifndef _ELEMENT
#define _ELEMENT
#include <stdio.h>
#include <stdlib.h>
#include "e_sommet.h"

/*
typedef struct{
	int numero;			// numero du sommet de l'etape
	double cout;		// le prix qu'il faut payer pour venir de l'etape precedante a celle-ci
	double pcc;			// le même que pour les sommets (somme de tous les couts)
} cailloux_blanc;

typedef struct etape_chemin{
	cailloux_blanc etape;
	chemin* next;
} *chemin;
*/

typedef vertex_t element_t;

void element_print (element_t e);
/*element_t element_empty();
int element_is_empty(element_t e);
*/

/* element_compare retourne 1 si e0_pt->0 > e1->pcc
 * 							-1 si e1_pt->1 > e0->pcc
 * 							0 sinon
 */
int element_compare(element_t* e0_pt, element_t* e1_pt);

void element_cpy(element_t* dest, element_t* src);

element_t element_new();
#endif

