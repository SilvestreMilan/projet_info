//
//  e_arc.c
//  Projet d'info
//
//  Created by Julien on 27/04/2020.
//  Copyright © 2020 Julien. All rights reserved.
//

#include "e_arc.h"

#define NIL NULL

edge_t creer_arc(){
    edge_t arc;
    arc.depart = 0;
    arc.arrivee = 0;
    arc.cout = 0;
    return arc;
}

// cf v milan
void print_arc(edge_t arc){
    printf("%d %d %lg /",arc.depart, arc.arrivee, arc.cout);
}

int egale_arc(edge_t arc1,edge_t arc2){
    int booleen = 1;
    if (arc1.depart != arc2.depart) booleen = 0;
    else if (arc1.arrivee != arc2.arrivee) booleen = 0;
    else if (arc1.cout != arc2.cout) booleen = 0;
    return booleen;
}



listedge_t list_new_edge() {
  return NIL;
}

int list_is_empty_edge(listedge_t l) {
  return NIL == l;
}

listedge_t list_add_first_edge( edge_t e, listedge_t l ) {
  listedge_t p = calloc( 1, sizeof( *p ) );
  if ( NULL == p ) {
    fprintf( stderr, "Fatal: Unable to allocate new list link.\n" );
    return l;
  }
  p->val  = e;
  p->next = l;
  return p;
}

int est_dans_list_edge(listedge_t liste, edge_t element){
    int n = list_length_edge(liste);
    for (int i= 0;i<n; i++){
        if (egale_arc(element, liste[i].val)){
            return 1;
        }
    }
    return 0;
}

// Precondition : liste non vide
listedge_t list_del_first_edge( listedge_t l ) {
  assert(!list_is_empty_edge(l));
  //element_delete(l->val);
  listedge_t p = l->next;
  free( l );
  return p;
}

void list_print_edge(listedge_t l) {
  listedge_t p;
  printf("( ");
  for ( p=l; ! list_is_empty_edge(p); p = p->next) {
    print_arc(p->val);
    printf( " " );
  }
  printf(")\n");
}

int list_length_edge(listedge_t l) {
  int len = 0;
  listedge_t p;
  for( p=l; ! list_is_empty_edge(p) ; p=p->next ) {
    len ++;
  }
  return len;
}

int egale_larc(listedge_t l1,listedge_t l2){
    listedge_t p1 = l1;
    listedge_t p2 = l2;
    
    while(!list_is_empty_edge(p1) || !list_is_empty_edge(p2)){
        if (!egale_arc(p1->val,p2->val)){
            return 0;
        }
        p1=p1->next;
        p2 = p2->next;
    }
    if (list_is_empty_edge(p1) && list_is_empty_edge(p2)){
        return 1;
    }
    else{
        return 0;
    }
}

listedge_t trouver_arc_voisin(vertex_t sommet1, vertex_t sommet2, int* nb_arc){
    listedge_t liste_arc = list_new_edge();
    int j=0;
    for (int i=0;i< list_length_edge(sommet1.edges); i++){
        if(!est_dans_list_edge(liste_arc,sommet1.edges[i].val)){
            list_add_first_edge(sommet1.edges[i].val, liste_arc);
            j++;
        }

    }
    *nb_arc = j;
    return liste_arc;
}
