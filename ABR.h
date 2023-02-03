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



pArbre insertion_ABR(pArbre arbre, float *donnees, int nb_donnees)
{
    pArbre nouvel_arbre = malloc(sizeof(pArbre));
    if (PTR_NUL(arbre))
    {

        nouvel_arbre->donnees = donnees;
        nouvel_arbre->nb_donnees = nb_donnees;
        nouvel_arbre->gauche = NULL;
        nouvel_arbre->droite = NULL;
        return nouvel_arbre;
    }

    if (donnees[0] < arbre->donnees[0])
    {
        arbre->gauche = insertion_ABR(arbre->gauche, donnees, nb_donnees);
    }
    else if (donnees[0] > arbre->donnees[0])
    {
        arbre->droite = insertion_ABR(arbre->droite, donnees, nb_donnees);
    }

    return arbre;
}

pArbre creer_ABR(pChainon liste)
{
    pArbre arbre = NULL;

    while (liste != NULL)
    {
        arbre = insertion_ABR(arbre, liste->donnees, liste->nb_donnees);
        liste = liste->suivant;
    }

    return arbre;
}



pChainon chainon_recherche(pChainon tete, int valeur_cherchee)
{
    pChainon courant = tete;
    while (courant != NULL && courant->suivant != valeur_cherchee)
    {
        courant = courant->suivant;
    }
    return courant;
}

void parcours_infixe(pArbre racine, FILE *f_sortie)
{
    if (racine == NULL)
        return;
    parcours_infixe(racine->gauche, f_sortie);
    fprintf(f_sortie, "%f ", racine->donnees);
    parcours_infixe(racine->droite, f_sortie);
}
