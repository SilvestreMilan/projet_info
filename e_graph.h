// Etant donne le sujet, on suppose qu'il existe en amont de la chaine de traitement des donnees un algorithme(essai)
// de mise en forme des donnees ou le format du fichier est celui precise par l'enonce. C'est pourquoi les
// fonctions ci-dessous sont specifique a ce format.

// section recopiant les structures presentees en page 2 du sujet

#include <stdio.h>
#include <stdlib.h>
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



// Type sommet
#ifndef vertex_struct
#define vertex_struct
typedef struct{
    int numero;        // indice sommet
    char nom[512];        // nom du sommet
    char ligne[128];        // uniquement pour le metro
    double x, y;        // latitude et longitude (pour graphique)
    double  pcc;        // "plus court chemin" entre sommet de depart et ce sommet
    listedge_t edges;    // listes des arc qui partent de ce sommet
                // utile que dans l'algorithme
} vertex_t;
#endif

// Type graphe
#ifndef graph_struct
#define graph_struct
typedef struct{
    int size_vertex;    // nombre sommets
    int size_edges;        // nombre d'arc
    vertex_t* data;        // tableau des sommets alloue dynamiquement
} graph_t;
#endif

// Fonction qui lit les premieres lignes du fichier representant un graphe et place les valeurs
// correspondantes aux parametres de ce graphe dans des pointeurs prealablement crees.
// ATTENTION: le fichier f doit avoir ete ouvert dans le main avant appel de la fonction
void lecture_parametres_graphe(FILE* f, int* nbsommets_pt, int* nbarcs_pt);

// Creation d'un tableau alloue dynamiquement qui contient un template de graphe (cf. sujet p2)
// prend en parametre le nombre de sommets (on a pas besoin dunombre d'arcs de par la nature du TAD choisi)
graph_t* graph_new(int nbsommets, int nb_arc);

// Fonction lisant une ligne (du fichier f) correspondant a un sommet (cf. format sujet p6) et qui la charge dans
// le graphe (a la position vertex_flag lue dans le fichier)
// ATTENTION: le fichier f doit avoir ete ouvert dans le main avant appel de la fonction
void add_vertex(FILE* f, graph_t* g_pt);

// Fonction lisant une ligne (du fichier f) correspondant a un arc (cf. format sujet p2 et p7) et qui la charge
// dans le graphe (dans la liste list_edge du sommet lu dans le fichier)
// ATTENTION: le fichier f doit avoir ete ouvert dans le main avant appel de la fonction
void add_edge(FILE* f, graph_t* g_pt);

// Fonction qui saute une ligne lors de la lecture du fichier (utile pour les 2 lignes a sauter dans
// le format propose)
void jump_line(FILE*f);

// Fonction qui cree un graphe a partir d'un fichier source
graph_t* graph_creation(char* file_name);

// A partir d'ici les fonctions sont specifiques au traitement d'un graphe

// Fonction qui affiche un graphe
void graph_print(graph_t*);
