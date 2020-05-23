#include "e_arc.h"
#include "e_sommet.h"
#include "e_graph.h"
#include "heap_BFS.h"

// BFS retourn -1 si une erreur s'est produite
//              0 si l'arrivee est inaccessible depuis le depart
//              1 si un chemin a ete trouve
int BFS_sale(int depart, int arrivee, graph_t* g, listvertex_t* petit_poucet_pt){
	//int nb_vertex = g->size_vertex;
	int nb_edges = g->size_edges;
	heap_t h = heap_new(nb_edges);

	heap_t* h_pt = &h; // c'est ici que c'est sale, mais ca evite des complications ligne 38

	/*printf("ceci est un heap vide: ");
	heap_print(*h_pt);
	printf("ceci est sont heap->number: %d\n", h_pt->number);
	*/

	// par defaut tous les sommet ont un pcc de -1 <=> (def) pcc de +infini

	g->data[depart].pcc = 0; // on fixe la référence de départ a 0 (on met le depart a la masse)
	if(heap_add_min(g->data[depart], h_pt) == 0) return -1;
	else{
		//printf("ceci est heap->number après add_min: %d\n", h_pt->number);
		//printf("marqueur 1\n");
		element_t vertex_pcc_min;
		edge_t current_edge;
		listedge_t  l;
		double dist;

		//printf("ceci est heap: ");
		//heap_print(*h_pt);

		vertex_pcc_min = heap_get_min(*h_pt);

		//printf("le sommet vertex_pcc_min est:");
		//print_sommet(vertex_pcc_min);
		//printf("la liste de d'arcs associée est: ");
		//list_print_edge(vertex_pcc_min.edges);           // ok jusqu'ici
		//printf("\n");

		//printf("heap_is_empty(*h_pt) = %d\n", heap_is_empty(*h_pt));
		//printf("element_equal(&vertex_pcc_min, &g->data[arrivee]) = %d\n", element_equal(&vertex_pcc_min, &g->data[arrivee]));

		while( ( 1 - heap_is_empty(*h_pt) ) && ( element_equal(&vertex_pcc_min, &g->data[arrivee]) == 0 ) ){

			//printf("marqueur 2\n");
			vertex_pcc_min = heap_get_min(*h_pt); // fonction ok
			/* //print_sommet(vertex_pcc_min);
			//printf("la liste de d'arcs associée est: ");
			//list_print_edge(vertex_pcc_min.edges);

			//printf("marqueur 2.5\n");

			//printf("petit_poucet avant list_add_first: ");
			//list_print_vertex(petit_poucet);
			 */
			*petit_poucet_pt = list_add_first_vertex( vertex_pcc_min, *petit_poucet_pt); // fonction ok

			printf("petit_poucet ");
			list_print_vertex(*petit_poucet_pt);
			//printf("petit_poucet après: ");
			//list_print_vertex(petit_poucet);
			//list_print_edge(petit_poucet->val.edges);

			printf("ceci est heap: ");
			heap_print(*h_pt);
			//printf("on va heap_delete_min\n");


			heap_delete_min(h_pt);

			//printf("ceci est heap après heap_delete_min: ");
			//heap_print(*h_pt);

			l = vertex_pcc_min.edges;
			//list_print_edge(petit_poucet->val.edges);
			//l = petit_poucet->val.edges;
			//list_print_edge(l);

			while( 1 - list_is_empty_edge( l ) ){

				//printf("marqueur 3\n");

				//printf("1 - list_is_empty_edge( l ) = %d\n", 1 - list_is_empty_edge( l ));
				//list_print_edge(l);


				current_edge = l->val;
				l = list_del_first_edge(l);
				dist = current_edge.cout + vertex_pcc_min.pcc;

				if( ( dist < g->data[current_edge.arrivee].pcc ) || ( g->data[current_edge.arrivee].pcc == -1 ) ){
					g->data[current_edge.arrivee].pcc = dist;
					if(heap_add_min(g->data[current_edge.arrivee], h_pt) == 0) return -1;
				}
			}
		}
		heap_delete(h_pt);
		if( g->data[arrivee].pcc == -1 ) return 0;
		else return 1;
	}
}

// la suite n'est a executer que si BFS_sale renvoie 1!
void trace_de_la_carte(int depart, int arrivee, graph_t* g, listvertex_t* petit_poucet_pt ){

	listvertex_t le_droit_chemin = list_new_vertex();
	listvertex_t petit_poucet;
	listvertex_t l;
	//le_droit_chemin = list_add_first_vertex(g->data[arrivee], le_droit_chemin);
	vertex_t etape;
	double la_route_est_longue = g->data[arrivee].pcc;

	//printf("le droit chemin est sur l'arrivee:");

	//list_print_vertex(le_droit_chemin);

	do{
		/*printf("la_route_est_longue = %lg\n", la_route_est_longue);
		printf("coucou\n");
		printf("petit_poucet->val =\n");
*/


		petit_poucet = *petit_poucet_pt;
		//print_sommet(petit_poucet->val);

		etape = petit_poucet->val;

		//printf("etape =");
		//print_sommet(etape);
		le_droit_chemin = list_add_first_vertex(etape, le_droit_chemin);

		*petit_poucet_pt = list_del_first_vertex(*petit_poucet_pt);

		la_route_est_longue -= etape.pcc;
		printf("1\n");
		list_print_vertex(le_droit_chemin);
		printf(" la_route_est_longue = %lg", la_route_est_longue);

	} while( la_route_est_longue - etape.pcc != 0 );

	printf("Là est le_droit_chemin: \n");
	l = le_droit_chemin;
	list_print_vertex(le_droit_chemin);
	for(; 1 - list_is_empty_vertex(l->next) ; l = l->next){
		printf("%s -- %lg -->", l->val.nom, l->next->val.pcc);
		printf("2\n");

	}
	printf("%s", l->val.nom);

	free_list_vertex(le_droit_chemin);
}

void suivez_ce_chemin( int depart, int arrivee, char* nom_fichier_graphe ){
	listvertex_t petit_poucet = list_new_vertex();
	listvertex_t* petit_poucet_pt = &petit_poucet;
	graph_t* g = graph_creation(nom_fichier_graphe);
	int i = BFS_sale(depart, arrivee, g, petit_poucet_pt);

	if( i == 1 ){
		printf("Le chemin est long de: %lg\n", g->data[arrivee].pcc);
		trace_de_la_carte(depart, arrivee, g, petit_poucet_pt );
	}
	else if( i == 0){
		printf("Itinéraire impossible!\n");
	}
	else{
		printf("Problème(s) i = %d\n", i);
	}
	free_list_vertex(*petit_poucet_pt);
	return;
}
