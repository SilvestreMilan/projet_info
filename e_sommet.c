
//  e_sommet.c
//  Projet d'info
//
//  Created by Julien on 27/04/2020.
//  Copyright © 2020 Julien. All rights reserved.
//

#include "project.h"
#include "e_sommet.h"
#include <string.h>
#define NIL NULL


vertex_t creer_sommet(void){
    vertex_t sommet;
    sommet.numero = 0;
    sommet.pcc = 0;
    sommet.x = 0;
    sommet.y = 0;
    strcpy(sommet.ligne, "\0");
    strcpy(sommet.nom, "\0");
    sommet.edges = NULL;
    return sommet;
}

int egalite_sommet(vertex_t s1, vertex_t s2){
    int booleen = 1;
    if (s1.numero != s2.numero) booleen =0;
    else if (s1.x != s2.x) booleen = 0;
    else if (s1.y != s2.y) booleen = 0;
    else if (strcmp(s1.ligne, s2.ligne) != 0) booleen = 0;
    else if (strcmp(s1.nom, s2.nom) != 0) booleen = 0;
    //else if (egale_larc(s1.edges,s2.edges)) booleen = 0; pour le moment bug un peu
    return booleen;
}


int empty_sommet(vertex_t sommet){
    return (egalite_sommet(sommet, creer_sommet()));
}

void print_sommet(vertex_t sommet){
    printf(" %d %lg %lg %s %s %lg\n", sommet.numero, sommet.x, sommet.y, sommet.ligne, sommet.nom, sommet.pcc);
    return;

}

listvertex_t list_new_vertex() {
  return NIL;
}

int list_is_empty_vertex(listvertex_t l) {
  return NIL == l;
}
vertex_t list_first_vertex(listvertex_t l){
  assert(!list_is_empty_vertex(l));
  return l->val;
}


listvertex_t list_add_first_vertex( vertex_t e, listvertex_t l ) {
  listvertex_t p = calloc( 1, sizeof( *p ) );
  if ( NULL == p ) {
    fprintf( stderr, "Fatal: Unable to allocate new list link.\n" );
    return l;
  }
  p->val  = e;
  p->next = l;
  return p;
}

// Precondition : liste non vide
listvertex_t list_del_first_vertex( listvertex_t l ) {
  assert(!list_is_empty_vertex(l));
  //element_delete(l->val);
  listvertex_t p = l->next;
  free( l );
  return p;
}

void list_print_vertex(listvertex_t l) {
  listvertex_t p;
  printf("( ");
  for ( p=l; ! list_is_empty_vertex(p); p = p->next) {
    print_sommet(p->val);
    printf( " " );
  }
  printf(")\n");
}

int list_length_vertex(listvertex_t l) {
  int len = 0;
  listvertex_t p;
  for( p=l; ! list_is_empty_vertex(p) ; p=p->next ) {
    len ++;
  }
  return len;
}

vertex_t recherche_sommet(graph_t graph, int nb_sommet){ // fonctionne parfaitement.
    for (int i=0; i<graph.size_vertex; i++){
        if (graph.data[i].edges->val.depart == nb_sommet){
            return graph.data[i];
        }
    }
    return creer_sommet();
}

int est_dans_liste_vertex( listvertex_t liste, vertex_t sommet){// fonctionne pas.
    int i=0;
    while (i<list_length_vertex(liste)) {
        if (egalite_sommet(liste[i].val,sommet)){
            return 1;
        }
        i++;
    }
    
    return 0;
}



/*
listvertex_t trouver_voisin(graph_t graphe, vertex_t sommet_depart, int* nb_voisin){
    int i=0;
    while(!egalite_sommet(graphe.data[i],sommet_depart)){// on cherche le bon sommet dans le graphe
        i= i+1;
    }
    int j=0;
    listvertex_t liste_voisin = list_new_vertex();
    int n = list_length_edge(sommet_depart.edges);
    for(int k=0; k< n ; k++){
        vertex_t sommet_intermediaire = recherche_sommet(graphe,graphe.data[i].edges[k].val.arrivee);
        if(!est_dans_liste_vertex(liste_voisin,sommet_intermediaire) ){
            j++;
            liste_voisin = list_add_first_vertex(sommet_intermediaire, liste_voisin);
        }
    }
    *nb_voisin = j;// k permet de regarder tous les arcs. j est le nombre de voisin different
    return liste_voisin;
}
*/

listvertex_t trouver_voisin(graph_t graphe, vertex_t sommet_depart, int* nb_voisin){
    listvertex_t liste_voisin = list_new_vertex();
    vertex_t voisin_potentiel;
    edge_t arc;
    int num_sommet_vise;
    int j = 0;
   // listedge_t liste_arc = sommet_depart.edges;
    //int n = list_length_edge(liste_arc);
    while(!list_is_empty_edge(sommet_depart.edges)){
        arc = list_first_edge(sommet_depart.edges);
        num_sommet_vise = arc.arrivee;
        sommet_depart.edges =list_del_first_edge(sommet_depart.edges);
       // nb_sommet_vise = liste_arc[i].val.arrivee;
        voisin_potentiel = recherche_sommet(graphe,num_sommet_vise);
        if (!est_dans_liste_vertex(liste_voisin, voisin_potentiel)){
            liste_voisin = list_add_first_vertex(voisin_potentiel, liste_voisin);
            j++;
        }
    }
    *nb_voisin = j;
    return liste_voisin;
}
void liberer_memoire(vertex_t* liste_voisin){
    free(liste_voisin);
}

void free_list_vertex(listvertex_t l){
	listvertex_t m;
	while( 1 - list_is_empty_vertex(l) ){
		m = l->next;
		free(l);
		l = m;
	}
	return;
}

void print_pcc_sommet(vertex_t sommet){
    printf("le pcc du sommet est : %lf \n",sommet.pcc);
}


