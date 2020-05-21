
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "e_graph.h"
#include "e_sommet.h"
#include "e_arc.h"

void lecture_parametres_graphe(FILE*f, int* NBS, int* NBA){
    fscanf(f, "%d %d", NBS, NBA); printf("ok\n");
// attention ici aucune verification des donnees lues (ex: prend pas en compte le resultat de fscanf) !
}

graph_t* graph_new(int nbs, int nba){
    graph_t* g = calloc(1, sizeof(*g));
    g->size_vertex = nbs;
    g->size_edges = nba;
    g->data = calloc(nbs, sizeof(*g->data));
    return g;
}

void add_vertex(FILE* f, graph_t* g){		/* V2*/

	int num;
	double lat,longi ;
	char line[128] ;
	char mot[512] ;



	/* lecture d’une ligne de description d’un sommet */
	/* on lit d’abord numero du sommet, la position, le nom de la ligne */
	fscanf(f,"%d %lf %lf %s", &num, &lat, &longi, line);
	
	/*printf("marqueur1\n");
	vertex_t** pt_data = &g->data;
	printf("marqueur2\n");
	(*pt_data)[num].numero = num;
	(*pt_data)[num].x = lat;
	(*pt_data)[num].y = longi;
	printf("marqueur3\n");
	printf("%d\n", (*pt_data)[num].numero);
	printf("%lg\n", (*pt_data)[num].x);
	printf("%lg\n", (*pt_data)[num].y);

	printf("marqueur4\n");*/


	g->data[num].numero = num;
	g->data[num].x = lat;
	g->data[num].y = longi;
	g->data[num].pcc = -1;									// initialisation à +infini des couts des sommets
	strcpy(g->data[num].ligne, line);

	/* numero contient alors l’entier ou numero du sommet, lat et longi la position, line le nom de la
	ligne */
	/* Le nom de la station peut contenir des separateurs comme l’espace. On utilise plutot fgets pour lire
	toute la fin de ligne */
	fgets(mot,511,f);
	/* fgets a lu toute la ligne, y compris le retour a la ligne. On supprime le caractere ’\n’ qui peut se
	trouver a la fin de la chaine mot : */
	if (mot[strlen(mot)-1]<32) mot[strlen(mot)-1]=0;
	/* mot contient desormais le nom du sommet. */


	//print_sommet(g->data[numero]);
	//(*pt_data)[num].ligne = mot;
	strcpy(g->data[num].nom, mot);
	//printf("%s\n", g->data[num].ligne);
	//printf("marqueur5\n");

}

void add_edge(FILE* f, graph_t* g){

    listedge_t current_edge_l = calloc(1, sizeof(*current_edge_l));    // allocation de memoire pour un maillon

	if(current_edge_l == NULL) printf("pas bon\n");

    fscanf(f, "%d %d %lf", &current_edge_l->val.depart, &current_edge_l->val.arrivee, &current_edge_l->val.cout);    // lecture des donnees dans l'ordre du format impose

    if(g->data[current_edge_l->val.depart].edges == NULL){                // si la liste des arcs du sommet de depart est vide (on aurait pu importer le module list.c deja implementer mais comme ca sert que dans cette fonction on s'epargne le fait d'aller readapter ce module (notemment element.c))

    	g->data[current_edge_l->val.depart].edges = current_edge_l;

    	g->data[current_edge_l->val.depart].edges->val.depart = current_edge_l->val.depart;

    	g->data[current_edge_l->val.depart].edges->val.arrivee = current_edge_l->val.arrivee;

    	g->data[current_edge_l->val.depart].edges->val.cout = current_edge_l->val.cout;

    	g->data[current_edge_l->val.depart].edges->next = NULL;            // on pointe sur NULL pour indiquer la fin de la liste (il n'y a qu'un seul element)

    	g->data[current_edge_l->val.depart].edges = current_edge_l;        // une liste c'est un pointeur vers un maillon!
    }

    else{
    	g->data[current_edge_l->val.depart].edges = list_add_first_edge( current_edge_l->val, g->data[current_edge_l->val.depart].edges);


    	/*
    	// la suite correspond a list_add_first pour une liste non vide
        listedge_t first = g->data[current_edge_l->val.depart].edges;        // first est le pointeur vers le 1er maillon avant ajout
        listedge_t listToAdd = current_edge_l;                    // listToAdd va prendre la tete de la chaine
        
        g->data[current_edge_l->val.depart].edges = listToAdd;            // mise en tete de listToAdd
        listToAdd->next = first;                        // conservation de la convention du TAD liste, mise en 2eme position de first   */
    }

// attention ici aucune verification des donnees lues (ex: prend pas en compte le resultat de fscanf) !
}

void jump_line(FILE*f){        // saute une ligne
    char mot[512];
    char* essai;
    essai= fgets(mot, 511, f);
    printf("%s\n",essai);
    
}


void delete_listedge(listedge_t l){    // detruit une liste d'arcs
    while(l != NULL){
        l = list_del_first_edge(l);
    }
}

void delete_graph(graph_t* g){
    int i;
    for(i = 0; i < g->size_vertex; i++) delete_listedge(g->data[i].edges);

    free(g->data);
    g->size_vertex = 0;
    g->size_edges = 0;
}

graph_t* graph_creation(char* file_name){

    FILE* f = fopen(file_name, "r+");                        // ouverture du fichier texte en lecture seule
    if( f == NULL ) {puts("Ouverture impossible\n"); return graph_new(0, 0);}    // en cas de probleme on retourne un graphe vide

    else{
        int nbs, nba, i;
        int* NBS = &nbs;
        int* NBA = &nba;
    
        lecture_parametres_graphe(f, NBS, NBA);                    // acquisition des parametre size_vertex et size_edges

        graph_t* g = graph_new(nbs, nba);                    // creation d'un graphe vide a remplir
        jump_line(f);
        jump_line(f);   // saut de la ligne "Sommets du graphe"
        printf("nbs = %d\n", nbs);
        for(i = 0; i<nbs; i++) add_vertex(f, g);             // ajout des noeuds au graphe

        jump_line(f);                                // saut de la ligne "arc du graphe : départ arrivéevaleur"
        
        for(i = 0; i<nba; i++) add_edge(f, g);                    // ajout des arcs dans les noeuds du graphe

        fclose(f);                                // fermeture du fichier
        return g;                                // on retourne bien un graph_t*
    }
}


void graph_print(graph_t* g){
    int size_vertex = g->size_vertex;
    int size_edges = g->size_edges;
    int i;

    printf("size_vertex = %d \n", size_vertex);
    printf("size_edges = %d \n", size_edges);


    for(i = 0; i<size_vertex; i++){
    		print_sommet(g->data[i]);
    		}
    for(i = 0; i<size_edges; i++) list_print_edge(g->data[i].edges);

    return;
}



































