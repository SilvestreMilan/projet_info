#include "heapsort_BFS.h"

/*
  Tri par tas :
    Cree un tas a partir du tableau tab ,
    tri ce tas par l'algorithem du tri par tas,
    recopie le tas trie dnas le tableau tab
    detruit le tas
*/
void heap_sort(element_t* tab, int size) {
  heap_t* pt_h;
  heap_t h = heap_new(size);
  pt_h = &h;
  int i;
  for( i = 0; i < size; i++ ) heap_add(tab[i], pt_h);
  //for( i = 0; i < size; i++ ) tab[i] = -h.data[i];
  heap_delete(&h);
}
