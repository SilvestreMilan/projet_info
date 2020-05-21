#ifndef _ELEMENT
#define _ELEMENT
#include <stdio.h>
#include <stdlib.h>
#include "e_sommet.h"

typedef vertex_t element_t;

void element_print (element_t e);
/*element_t element_empty();
int element_is_empty(element_t e);
*/

/* ne prend pas en compte les pcc
 */
int element_equal(element_t* e0_pt, element_t* e1_pt);

/* element_compare retourne 1 si e0_pt->0 > e1->pcc
 * 							-1 si e1_pt->1 > e0->pcc
 * 							0 sinon
 */
int element_compare(element_t* e0_pt, element_t* e1_pt);

#endif
