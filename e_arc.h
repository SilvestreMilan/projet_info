//
//  e_arc.h
//  Projet d'info
//
//  Created by Julien on 27/04/2020.
//  Copyright © 2020 Julien. All rights reserved.
//


#include "project.h"
#include "e_sommet.h"
#include <string.h>
// Type liste chainee d'arc

#ifndef edge_struct
#define edge_struct
typedef struct{
    int depart, arrivee;    // indices des sommets de depart et d'arrivee de l'arc
    double cout;
} edge_t;



typedef struct maillon_edge{
    edge_t val;        // une option pointeur peut etre envisagee
    struct maillon_edge* next;
} *listedge_t;
#endif

// Fichier list.h
#ifndef _LISTEDGE_H
#define _LISTEDGE_H
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// 2. Protoype des fonctions realisant les opérations essentielles du type abstrait Liste

// Crée une liste vide
listedge_t list_new_edge(void);

// Retourne VRAI si l est une liste vide
int list_is_empty_edge(listedge_t l);


// Retourne le reste de la liste
// PRECONDITION : liste non vide
listedge_t list_next_edge(listedge_t l);

listedge_t list_add_first_edge( edge_t e, listedge_t l );
// Supprime le maillon en tête de liste et retourne la nouvelle liste
// PRECONDITION : liste non vide
listedge_t list_del_first_edge(listedge_t l);
// Retourne le nombre d'éléments (ou de maillons) de la liste
int list_length_edge(listedge_t l);
// Affiche la liste
void list_print_edge(listedge_t l);
// permet de déterminer si le  sommet est dans la liste l. On repère ce sommet avec son numéro. Retourn 1 si oui, 0 sinon.
int est_dans_list_edge(listedge_t l, edge_t arc);
#endif


edge_t creer_arc(void);
int egale_arc(edge_t arc1, edge_t arc2);
int egale_larc(listedge_t l1,listedge_t l2);
void print_arc(edge_t arc);

//trouve tous les arcs entre deux sommets, les places dans une liste et renvoie cette liste
listedge_t trouver_arc_voisin(vertex_t sommet1, vertex_t sommet2, int* nb_arc);




