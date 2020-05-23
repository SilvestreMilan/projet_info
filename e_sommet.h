
//
//  e_sommet.h
//  Projet d'info
//
//  Created by Julien on 27/04/2020.
//  Copyright © 2020 Julien. All rights reserved.
//

#include "project.h"
#include "e_graph.h"
// Type sommet
#ifndef vertex_struct
#define vertex_struct
typedef struct{
    int numero;        // indice sommet
    char* nom;        // nom du sommet
    char* ligne;        // uniquement pour le metro
    double x, y;        // latitude et longitude (pour graphique)
    listedge_t edges;    // listes des arc qui partent de ce sommet
    double  pcc;        // "plus court chemin" entre sommet de depart et ce sommet // utile que dal'algorithme
    int pere;           // represente le numero du sommet pere. Uilie pour DFS.
} vertex_t;
#endif
// Fichier list.h
#ifndef _LISTVERTEX_H
#define _LISTVERTEX_H


// 1. Définition des types maillon (link_t) et liste (list_t)
typedef struct maillon_vertex{
    vertex_t val;        // une option pointeur peut etre envisagee
    struct maillon_vertex* next;
} *listvertex_t;

// 2. Protoype des fonctions realisant les opérations essentielles du type abstrait Liste

// Crée une liste vide
listvertex_t list_new_vertex(void);
// Retourne VRAI si l est une liste vide
int list_is_empty_vertex(listvertex_t l);
// Retourne le reste de la liste
// PRECONDITION : liste non vide
listvertex_t list_next_vertex(listvertex_t l);

vertex_t list_first_vertex(listvertex_t l);

listvertex_t list_add_first_vertex(vertex_t e, listvertex_t l);
// Supprime le maillon en tête de liste et retourne la nouvelle liste
// PRECONDITION : liste non vide
listvertex_t list_del_first_vertex(listvertex_t l);
// Retourne le nombre d'éléments (ou de maillons) de la liste
int list_length_vertex(listvertex_t l);
// Affiche la liste
void list_print_vertex(listvertex_t l);
// permet de déterminer si le  sommet est dans la liste l. On repère ce sommet avec son numéro. Retourn 1 si oui, 0 sinon.
int est_dans_liste_vertex(listvertex_t l,vertex_t sommet);

#endif



vertex_t creer_sommet(void);
int egalite_sommet(vertex_t s1, vertex_t s2);
void print_sommet(vertex_t sommet);
int empty_sommet(vertex_t sommet);
listvertex_t trouver_voisin(graph_t graphe,vertex_t sommet_depart,int* nb_voisin );// permet de génerer un tableau alloué dynamiquement. Donne aussi le nombre de voisin
void liberer_memoire(vertex_t* liste_voisin);
void free_list_vertex(listvertex_t l);
vertex_t recherche_sommet(graph_t graph, int nb_sommet);
void print_pcc_sommet(vertex_t sommet);

