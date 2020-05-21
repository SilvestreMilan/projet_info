//
//  main.c
//  Projet d'info
//
//  Created by Julien on 07/04/2020.
//  Copyright © 2020 Julien. All rights reserved.
//
#include "project.h"
#include "heapsort_BFS.h"

int main(int argc, const char * argv[]){
    // Ce fichier est destine a tester les fonctions de bases du proje
    
	int i;
    graph_t* g = graph_creation("0_graphe1.txt");
    print_sommet(g->data[0]);
    for(i=0; i<g->size_vertex; i++) g->data[i].pcc = i;
    heap_sort(g->data, g->size_vertex);
    graph_print(g);
    

}
