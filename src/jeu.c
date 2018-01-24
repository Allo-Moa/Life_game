/**
 * \file jeu.c
 * \brief Fonctions qui permet de faire dérouler le jeu.
 * \author TP-unistra
 * \version 1.0
 * \date 19 octobre 2017
 *
 * Fonctions complémentaires au programme.
 *
 */
#include "jeu.h"

static int depasse( int a, int b){
	if (a <= 0 || a >= b){ return 0; }else {return a;}
}

int compte_voisins_vivants_non_cyclique (int i, int j, grille g){
	int v = 0,  l=g.nbl, c = g.nbc;

	v+= est_vivante(depasse(i-1,l),depasse(j-1,c),g);
	v+= est_vivante(depasse(i-1,l),depasse(j,c),g);
	v+= est_vivante(depasse(i-1,l),depasse(j+1,c),g);
	v+= est_vivante(depasse(i,l),depasse(j-1,c),g);
	v+= est_vivante(depasse(i,l),depasse(j+1,c),g);
	v+= est_vivante(depasse(i+1,l),depasse(j-1,c),g);
	v+= est_vivante(depasse(i+1,l),depasse(j,c),g);
	v+= est_vivante(depasse(i+1,l),depasse(j+1,c),g);


	return v;
}

int compte_voisins_vivants (int i, int j, grille g){
	int v = 0, l=g.nbl, c = g.nbc;
	v+= est_vivante(modulo(i-1,l),modulo(j-1,c),g);
	v+= est_vivante(modulo(i-1,l),modulo(j,c),g);
	v+= est_vivante(modulo(i-1,l),modulo(j+1,c),g);
	v+= est_vivante(modulo(i,l),modulo(j-1,c),g);
	v+= est_vivante(modulo(i,l),modulo(j+1,c),g);
	v+= est_vivante(modulo(i+1,l),modulo(j-1,c),g);
	v+= est_vivante(modulo(i+1,l),modulo(j,c),g);
	v+= est_vivante(modulo(i+1,l),modulo(j+1,c),g);

	return v;
}
int (*ptr_compte_voisins_vivants) (int, int, grille) = &compte_voisins_vivants;


void commande_cyclique( int a){
	if(a % 2 ==0){
		ptr_compte_voisins_vivants = &compte_voisins_vivants_non_cyclique;
	}
	else{
		ptr_compte_voisins_vivants = &compte_voisins_vivants;

	}
}
int activV =1;
int *activation_vieillesse = &activV;

void evolue (grille *g, grille *gc){
	copie_grille (*g,*gc); // copie temporaire de la grille
	int i,j,l=g->nbl, c = g->nbc,v;
	for (i=0; i<l; i++)
	{
		for (j=0; j<c; ++j)
		{
			v = (*ptr_compte_voisins_vivants)(i, j, *gc);
			if (est_vivante(i,j,*g))
			{ // evolution d'une cellule vivante
				if ( v!=2 && v!= 3 ){set_morte(i,j,*g);}
				else{
						if(activV % 2 == 0 ){
							if( g->cellules[i][j] > 8){set_morte(i,j, *g);}
							else{	grandi_de_1(i,j,*g);
							}
						}
				}
			}
			else
			{ // evolution d'une cellule morte
				if ( v==3 && g->cellules[i][j] !=-1 ) set_vivante(i,j,*g);
			}
		}
	}
	return;
}
