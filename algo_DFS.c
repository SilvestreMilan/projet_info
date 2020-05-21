//
//  algo_DFS.c
//  Projet d'info
//
//  Created by Julien on 25/04/2020.
//  Copyright © 2020 Julien. All rights reserved.
//

#include "algo_DFS.h"


int Parcours_En_Profondeur(vertex_t sommet_depart,vertex_t sommet_arrive,graph_t graphe){
    int trouve=0;
    if (egalite_sommet(sommet_depart,sommet_arrive)){
        return 1;
    }
    else{
        int nb_voisin=0;
        vertex_t* tableau_voisin;
        tableau_voisin = trouver_voisin(graphe,sommet_depart,&nb_voisin);// à tester
        int distance_temps = 0;
        
        for (int i = 0;i<nb_voisin;i++){
            int nb_arc = 0;
            listedge_t liste_arc_voisin = trouver_arc_voisin(sommet_depart,tableau_voisin[i],&nb_arc);
            for(int j = 0; j< nb_arc; j++){
                distance_temps = sommet_depart.pcc + liste_arc_voisin[j].val.cout;
                if (distance_temps< tableau_voisin[i].pcc){
                    tableau_voisin[i].pcc = distance_temps;
                    trouve = Parcours_En_Profondeur(tableau_voisin[i], sommet_arrive, graphe);
                }
            }
        }
        
        
        

        
    }
    return trouve;
}

