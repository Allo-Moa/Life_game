/**
 * \file io.c
 * \brief Fonctions d'affichage et début du jeu.
 * \author TP-unistra
 * \version 1.0
 * \date 19 octobre 2017
 *
 * Fonctions complémentaires.
 *
 */
#include <cairo.h>
#include <cairo-xlib.h>
#include <X11/Xlib.h>
#include "io.h"
#include <string.h>

int compt_temp = 0;

int activC = 1;
int *pointeur_activC = &activC;

void affiche_trait (int c){
	int i;
	for (i=0; i<c; ++i) printf ("|---");
	printf("|\n");
	return;
}

void affiche_ligne (int c, int* ligne){
	int i;
	for (i=0; i<c; ++i)
		if (ligne[i] == 0 ) printf ("|   "); else {
																				if(ligne[i] == -1){
																					printf("| X ");
																				}else{
																				 printf("| %d ",ligne[i]);
																			 }
																		 }
	printf("|\n");
	return;
}

void affiche_grille (grille g){
	printf("\rTemps numero : %d", compt_temp);
	int i, l=g.nbl, c=g.nbc;
	printf("\n");
	affiche_trait(c);
	for (i=0; i<l; ++i) {
		affiche_ligne(c, g.cellules[i]);
		affiche_trait(c);
	}
	printf("\n");
	return;
}

void efface_grille (grille g){
	printf("\n\e[%dA",g.nbl*2 + 5);
}

void debut_jeu(grille *g, grille *gc){
	char c = getchar();
	while (c != 'q') // touche 'q' pour quitter
	{
		switch (c) {
			case '\n' :
			{ // touche "entree" pour évoluer
					compt_temp ++;
				evolue(g,gc);
				efface_grille(*g);
				affiche_grille(*g);
				if(activC % 2 == 0 ) printf("cyclic evolution disabled |");
				else printf("cyclic evolution enabled |");
				if(*activation_vieillesse % 2 == 0 ) printf("| life evolution enabled ");
				else printf("| life evolution disabled ");
				break;
			}
			case 'n':
			{ //touche "n" pour faire rentrer au clavier le nom d'une nouvelle grille
			compt_temp = 0;
			char nv_grille[12] = {0};
			char repert[] = "grilles/";
				printf("Quelle grille voulez vous ? (grilleX.txt):" );
				scanf("%s", nv_grille );
				printf("\n" );
				init_grille_from_file(strcat(repert, nv_grille), g);
				alloue_grille (g->nbl, g->nbc, gc);
				affiche_grille(*g);
				scanf("%c",&c );
				break;

			}
			case 'c' :
			{
				 	activC ++;
					commande_cyclique(activC);
				break;
			}
			case 'v':
			{
				*activation_vieillesse +=1;
			}
			default :
			{ // touche non traitée
				printf("\n\e[1A");
				break;
			}
		}
		c = getchar();
	}
	return;
}
void paint(cairo_surface_t *surface, grille g)
{
	cairo_t *cr;
	cr=cairo_create(surface);

	int i, l=g.nbl, c=g.nbc;
	int j=0;

	for (i=0; i<=l; ++i) {

		cairo_set_source_rgb (cr, 1.0, 1.0, 1.0);
		cairo_move_to(cr,20.0,20.0+i*20);
		cairo_line_to(cr,20+c*20.0,20.0+i*20);
		cairo_set_line_width (cr, 2);
		cairo_stroke (cr);
		if(i<l){
		for(j=0; j<c; j++){
			if(g.cellules[i][j] >=1 && g.cellules[i][j] < 8){
										cairo_rectangle(cr,25+j*20,25+i*20,10,10);
										cairo_set_source_rgb (cr, 0.0, 1.0, 0.0);
										cairo_fill(cr);
											}
			if(g.cellules[i][j] == -1){
				cairo_rectangle(cr,25+j*20,25+i*20,10,10);
				cairo_set_source_rgb (cr, 1.0, 0.0, 0.0);
				cairo_fill(cr);

			}
					}
				}
			}
for(j=0; j<=c; j++){
		cairo_set_source_rgb (cr, 1.0, 1.0, 1.0);
		cairo_move_to(cr,20.0+j*20,20.0);
		cairo_line_to(cr,20.0+j*20,20+l*20.0);
		cairo_set_line_width (cr, 2);
		cairo_stroke (cr);

	}
	cairo_destroy(cr); // destroy cairo mask
}

void efface_paint(cairo_surface_t *surface)
{
	cairo_t *cr;
	cr=cairo_create(surface);
								cairo_rectangle(cr,0,0,SIZEX, SIZEY);
								cairo_set_source_rgb (cr, 0.0, 0.0, 0.0);
										cairo_fill(cr);


	cairo_destroy(cr); // destroy cairo mask
}
