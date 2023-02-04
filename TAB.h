#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PTR_NUL(ptr) (!ptr)

typedef struct chainon
{
    float *donnees;
    int nb_donnees;
    struct chainon *suivant;
} Chainon, *pChainon;


pChainon insertfin(pChainon liste, float *donnees, int nb_donnees);

pChainon merge(pChainon liste1, pChainon liste2);


pChainon tri_fusion(pChainon liste);


pChainon creer_liste(char *nom_fichier);
