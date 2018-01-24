/**
 * \file grille.c
 * \brief Fonctions qui permettent de gérer les grilles
 * \author TP-unistra
 * \version 1.0
 * \date 19 octobre 2017
 *
 * Fonctions complémentaires au programme.
 *
 */

#include "grille.h"

void alloue_grille (int l, int c, grille* g){
			int i, j;
			g->nbl = l;
			g->nbc = c;
			int ** P = g->cellules;

			P =  malloc(l* sizeof(int *));       //On alloue 'taille1' pointeurs.

			if( P == NULL) exit(EXIT_FAILURE);

			for(i=0 ; i < l ; i++){
     		P[i] =  malloc( c  * sizeof(int) );
     		if(P[i] == NULL){
				 		exit(EXIT_FAILURE);
    			}
				}

			for(i=0; i<l; i = i+1){
				for(j=0; j<c; j = j+1){
								P[i][j] = 0;
					}
				}
				g->cellules= P;
}

void libere_grille (grille* g){

		int i;
				for(i=0 ; i < g->nbl ; i++){
				 free(g->cellules[i]);
			 	}
				free(g->cellules);
				g->cellules = NULL;
}


void init_grille_from_file (char * filename, grille* g){
	FILE * pfile = NULL;
	pfile = fopen(filename, "r");
	assert (pfile != NULL);


	int i,j,n,l,c,vivantes,non_viable=0;

	fscanf(pfile, "%d", &l);
	fscanf(pfile, "%d", &c);

	alloue_grille(l,c,g);

	fscanf(pfile, "%d", &vivantes);
	for (n=0; n< vivantes; ++n){
		fscanf(pfile, "%d", &i);
		fscanf(pfile, "%d", &j);
		set_vivante(i,j,*g);
	}
	fscanf(pfile, "%d", &non_viable);
	for (n=0; n<non_viable; ++n){
		fscanf(pfile, "%d", &i);
		fscanf(pfile, "%d", &j);
		set_nonviable(i,j,*g);
	}

	fclose (pfile);
	return;
}

void copie_grille (grille gs, grille gd){
	int i, j;
	for (i=0; i<gs.nbl; ++i) for (j=0; j<gs.nbc; ++j) gd.cellules[i][j] = gs.cellules[i][j];
	return;
}
