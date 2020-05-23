#include "e_arc.h"
#include "e_sommet.h"
#include "e_graph.h"
#include "element_BFS.h"
#include "heap_BFS.h"

int BFS_sale(int depart, int arrivee, graph_t* g, listvertex_t petit_poucet);
listvertex_t trace_de_la_carte(int depart, int arrivee, graph_t* g, listvertex_t petit_poucet );
void suivez_ce_chemin( int depart, int arrivee, char* nom_fichier_graphe );


