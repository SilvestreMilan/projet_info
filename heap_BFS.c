#include "heap_BFS.h"

heap_t heap_new(int m) {
  heap_t tas;
  tas.data = calloc( m, sizeof(*tas.data) );
  tas.max_size = m;
  tas.number = 0;
  return tas;
}

int heap_is_empty(heap_t tas) {
  if( tas.number == 0 ) return 1;
  else return 0; 
}

/* Ajoute l'element valeur au tas pointe par ptas */
int heap_add(element_t valeur, heap_t* ptas) {
  if( ptas->max_size == ptas->number ) return 0;	// cas liste pleine
  else{
    int current_position = ptas->number;
    ptas->data[current_position] = valeur;		// on place la valeur sur la nouvelle feuille
    element_t* pt_father = &ptas->data[HEAP_FATHER(current_position)];
    element_t* pt_current = &ptas->data[current_position];

    while( element_compare( pt_father ,pt_current) == -1 ){	// tant que le fils est plus grand que le pere, on va echanger les positions pere-fils
	   element_t store = *pt_father;
	   *pt_father = *pt_current;
	   *pt_current = store;

	   current_position = HEAP_FATHER(current_position);
	   pt_father = &ptas->data[HEAP_FATHER(current_position)];
	   pt_current = &ptas->data[current_position];
  							  }
  ptas->number += 1;				        // mise a jour de la taille du tas
  return 1;
      }
}


/* Retourne l'indice du plus grand des deux fils ou -1 si c'est une feuille  ou 0 si on est out of range */
static int heap_largest_son(heap_t tas, int indice) {
  if( indice > tas.number ) return 0;
  else if ( HEAP_LEFTSON(indice) > tas.number ) return -1; 	// si le fils le plus à gauche est plus grand que le nombre d'element deja present dans le tableau alors c'est que le pere etait une feuille
  else if ( HEAP_RIGHTSON(indice) > tas.number ) return HEAP_LEFTSON(indice);	// comme on est sur que le fils gauche n'est pas plus grand que le nb d'element dans le tableau, si le fils droit n'est pas dans le tableau alors on a juste a retourner le fils gauche
  else{
	char i;
	i = element_compare(&tas.data[HEAP_LEFTSON(indice)], &tas.data[HEAP_RIGHTSON(indice)]) + 1; // +1 pour que ca colle avec les char (-1 passe a 0)
	switch(i){
		case '0' : return HEAP_RIGHTSON(indice);	// fils droit plus grand
		case '1' : return HEAP_LEFTSON(indice);		// les 2 fils sont egaux (c'est possible)
		case '2' : return HEAP_LEFTSON(indice);		// le fils gauche est plus grand
		 }
      }
}

/* Supprimer la racine en la remplacant par le dernier element du tas */
int heap_delete_max(heap_t* ptas) {
  if (heap_is_empty(*ptas)) return 0;
  else{
	int current_position = 0;  
  	do{
		int i = heap_largest_son(*ptas, current_position);
		if( i == -1 ) break;
		element_t current_element = ptas->data[current_position];
		element_t largest_son = ptas->data[i];
		if( element_compare(&current_element, &largest_son) == -1 ){
			element_t store = current_element;
		 	ptas->data[current_position] = largest_son;
			ptas->data[i] = store;
		}
		else break;
		current_position = i;
	} while(1);

	return 1;
  }
}


void heap_delete(heap_t* ptas) {
  ptas->max_size = 0;
  ptas->number = 0;
  free(ptas->data);
}

/* Retourne l'element max */
element_t heap_get_max(heap_t tas) {
  return tas.data[0];
}

/* Affiche le tas a l'ecran */
void heap_print(heap_t tas) {
  for (int i=0; i<tas.number; i++)
    element_print(tas.data[i]);
  puts("");
}

/*
  Verifie la propriete des tas sur tous les noeuds :
  le pere est plus grand que les 2 fils
*/

int heap_verification(heap_t tas) {
  int i;
  for (i=0; i< tas.number/2; i++) {
  if (element_compare(tas.data+i,tas.data+HEAP_LEFTSON(i))<0) return i;
    if (HEAP_RIGHTSON(i)<tas.number && (element_compare(tas.data+i,tas.data+HEAP_RIGHTSON(i)) == -1)) return i;
  }
  return -1;
}
