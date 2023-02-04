#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PTR_NUL(ptr) (!ptr)

typedef struct arbre
{
    float *donnees;
    int nb_donnees;
    struct arbre *gauche;
    struct arbre *droite;
} Arbre, *pArbre;



pArbre insertion_ABR(pArbre arbre, float *donnees, int nb_donnees);


pArbre creer_ABR(pChainon liste);


pChainon chainon_recherche(pChainon tete, int valeur_cherchee);

void parcours_infixe(pArbre racine, FILE *f_sortie);
