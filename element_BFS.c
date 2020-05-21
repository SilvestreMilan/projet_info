#include "element_BFS.h"

void element_print (element_t e) {
	print_sommet(e);
}

int element_equal(element_t* e1_pt, element_t* e2_pt) {
	return egalite_sommet(*e1_pt, *e2_pt);
}

int element_compare(element_t* e0_pt, element_t* e1_pt) {
   if( e0_pt->pcc > e1_pt->pcc) return 1;
   else if( e0_pt->pcc < e1_pt->pcc) return -1;
   else return 0;
 }
