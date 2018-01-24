#ifndef __JEU_H
#define __JEU_H

#include "grille.h"
/**
 * \struct jeu.h
 * \brief définitions des fonctions pour le déroulement du jeu et l'evolution des fonctions.
 *
 *
 *
 */
 /**
  * \fn inline int modulo (int i, int  m)
  * \brief modulo modifié pour traiter correctement les bords i=0 et j=0, dans le calcul des voisins avec bords cycliques
  *
  * \param i nombre de lignes, m nombre de colonnes d'une grille.
  *
  */
static inline int modulo(int i, int m) {return (i+m)%m;}

/**
 * \fn compte_voisins_vivants(int i, int j, grille g)
 * \brief compte le nombre de voisins vivants de la cellule (i,j), les bords sont cycliques.
 *
 * \param i nombre de lignes, m nombre de colonnes, g une grille.
 *
 */
int compte_voisins_vivants (int i, int j, grille g);
/**
 * \fn compte_voisins_vivants_non_cyclique(int i, int j, grille g)
 * \brief compte le nombre de voisins vivants de la cellule (i,j), les bords ne sont pas cycliques.
 *
 * \param i nombre de lignes, m nombre de colonnes, g une grille.
 *
 */
int compte_voisins_vivants_non_cyclique (int i, int j, grille g);
/**
  *\fn commande_cyclique(int a)
  *\brief active ou desactive le calcul des voisins en version cyclique
  *\param a un entier qui soit pair soit impair
  */
void commande_cyclique(int a);

// fait évoluer la grille g d'un pas de temps
void evolue (grille *g, grille *gc);

extern int * activation_vieillesse;

#endif
