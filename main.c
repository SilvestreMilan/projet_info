//
//  main.c
//  Projet d'info
//
//  Created by Julien on 07/04/2020.
//  Copyright © 2020 Julien. All rights reserved.
//
#include "project.h"
#include "element_BFS.h"
#include "heap_BFS.h"
#include "BFS.h"




int main(int argc, const char * argv[]){
    // Ce fichier est destine a tester les fonctions de bases du proje
    
	int depart = 0;
	int arrivee = 5;
	char nom_fichier_graphe[100] = "0_graphe1.txt";

    suivez_ce_chemin(depart, arrivee, nom_fichier_graphe );
}
