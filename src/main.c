/**
 * \file main.c
 * \brief Programme principal
 * \author TP-unistra
 * \version 1.2
 * \date  19 octobre 2017
 *
 * Programme de qui lance le jeu_de_la_vie
 *
 */


#include <stdio.h>

#include "grille.h"
#include "io.h"
#include "jeu.h"


/**
 * \fn int main (int argc, char ** argv)
 * \brief Entrée du programme.
 *
 * \return 0- Arrêt normal du programme.
 */
int main (int argc, char ** argv) {

	if (argc != 2 )
	{
		printf("usage : main <fichier grille>");
		return 1;
	}

	grille g, gc;
	init_grille_from_file(argv[1], &g);
	alloue_grille (g.nbl, g.nbc, &gc);
	affiche_grille(g);
	if(*pointeur_activC % 2 == 0 ) printf("cyclic evolution disabled |");
	else printf("cyclic evolution enabled |");
	if(*activation_vieillesse % 2 == 0 ) printf("| life evolution enabled");
	else printf("| life evolution disabled");

	debut_jeu(&g, &gc);

	libere_grille(&g);
	libere_grille(&gc);
	return 0;
}
