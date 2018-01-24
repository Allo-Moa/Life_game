#ifndef __GRILLE_H
#define __GRILLE_H

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

/**
 * \struct grille
 * \brief tableau 2 dimensions avec nb l et nb c.
 *
 * la structure grille prend en compte deux entiers nbl et nbc
 * repésentant le nombre de ligne et de colonnes, elle comprend aussi
 * un tableau à 2 dimensions qu'il faut allouer dynamiquement.
 *
 */
typedef struct {int nbl; int nbc; int** cellules;} grille; /*!< nbl nbc doivent être des entiers positifs. */

/**
 * \fn alloue_grille ( l, c ,  grille * g)
 * \brief alloue une grille de taille l*c, et initialise toutes les cellules à mortes.
 *
 * \param l nombre de lignes, c nombre de colonnes, g pointeur sur une grille.
 *
 */

void alloue_grille (int l, int c, grille* g);

/**
 * \fn libere_grille (grille* g)
 * \brief libère une grille
 *
 * \param  g pointeur sur une grille.
 *
 */

void libere_grille (grille* g);

/**
 * \fn init_grille_from_file (char * filename, grille* g
 * \brief alloue et initalise la grille g à partir d'un fichier.
 *
 * \param un tableau de caractère représentant le fichier txt contenant une grille, g pointeur sur une grille.
 *
 */

void init_grille_from_file (char * filename, grille* g);

/**
 * \fn  set_vivante( i, j, grille g)
 * \brief rend vivante la cellule (i,j) de la grille g
 *
 * \param i numéro de la ligne, j numéro de la colonne , g  une grille.
 *
 */

static inline void set_vivante(int i, int j, grille g){g.cellules[i][j] = 1;}

static inline void set_nonviable(int i, int j , grille g){g.cellules[i][j] = -1;}
/**
 * \fn  set_morte( i, j, grille g)
 * \brief rend morte la cellule (i,j) de la grille g
 *
 * \param i numéro de la ligne, j numéro de la colonne , g  une grille.
 *
 */

static inline void set_morte(int i, int j, grille g){g.cellules[i][j] = 0;}

/**
 * \fn  est_vivante( i, j, grille g)
 * \brief teste si la cellule (i,j) de la grille g est vivante
 *
 * \param i numéro de la ligne, j numéro de la colonne , g  une grille.
 *
 */

static inline int est_vivante(int i, int j, grille g){return g.cellules[i][j] >= 1;}

/**
 * \fn  copie_grille (grille gs, grille gd)
 * \brief recopie gs dans gd (sans allocation)
 *
 * \param  gs qui recoit une grille, gd la grille à copier.
 *
 */

void copie_grille (grille gs, grille gd);

/**
  *\fn grandi_de_1(int i, int j, grille g)
  *\brief fait grandir de 1 temps une cellule
  *
  *\param i recoit un entie, j recoit un entier, g est une grille
  *
  **/
static inline void grandi_de_1(int i, int j, grille g){ g.cellules[i][j] = g.cellules[i][j] + 1;}


#endif
