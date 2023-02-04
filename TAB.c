#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <TAB.h>
#define PTR_NUL(ptr) (!ptr)

typedef struct chainon
{
    float *donnees;
    int nb_donnees;
    struct chainon *suivant;
} Chainon, *pChainon;


pChainon insertfin(pChainon liste, float *donnees, int nb_donnees)
{
    pChainon nouveau = malloc(sizeof(pChainon));
    nouveau->donnees = donnees;
    nouveau->nb_donnees = nb_donnees;
    nouveau->suivant = NULL;

    if (PTR_NUL(liste))
    {
        return nouveau;
    }

    pChainon dernier = liste;
    while (!PTR_NUL(dernier->suivant))
    {
        dernier = dernier->suivant;
    }
    dernier->suivant = nouveau;

    return liste;
}

pChainon merge(pChainon liste1, pChainon liste2)
{
    if (PTR_NUL(liste1))
    {
        return liste2;
    }
    if (PTR_NUL(liste2))
    {
        return liste1;
    }

    pChainon resultat = NULL;

    if (liste1->donnees[0] < liste2->donnees[0])
    {
        resultat = liste1;
        resultat->suivant = merge(liste1->suivant, liste2);
    }
    else
    {
        resultat = liste2;
        resultat->suivant = merge(liste1, liste2->suivant);
    }

    return resultat;
}

pChainon tri_fusion(pChainon liste)
{
    if (PTR_NUL(liste) || PTR_NUL(liste->suivant))
    {
        return liste;
    }

    pChainon milieu = liste;
    pChainon fin = liste->suivant;

    while (!PTR_NUL(fin) && !PTR_NUL(fin->suivant))
    {
        milieu = milieu->suivant;
        fin = fin->suivant->suivant;
    }

    fin = milieu->suivant;
    milieu->suivant = NULL;

    return merge(tri_fusion(liste), tri_fusion(fin));
}

pChainon creer_liste(char *nom_fichier)
{
    pChainon liste = NULL;
    FILE *f_entree = fopen("FinalWeather.csv", "r");
    if (f_entree == NULL)
    {
        perror("Erreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }

    float *donnees = malloc(sizeof(float));
    int nb_donnees = 0;

    while (fscanf(f_entree, "%f", &donnees[nb_donnees]) == 1)
    {
        nb_donnees++;
        donnees = realloc(donnees, (nb_donnees + 1) * sizeof(float));
    }

    fclose(f_entree);

    liste = tri_fusion(liste);
    liste = insertfin(liste, donnees, nb_donnees);

    return liste;
}
