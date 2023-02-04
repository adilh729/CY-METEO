#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <AVL.h>
#define PTR_NUL(ptr) (!ptr)

typedef struct arbre
{
    float *donnees;
    int nb_donnees;
    struct arbre *gauche;
    struct arbre *droite;
    int equilibre;
} Arbre, *pArbre;


int max(int x, int y) {
    return (x > y) ? x : y;
}

int hauteur(pArbre arbre)
{
    if (PTR_NUL(arbre))
    {
        return 0;
    }
    return max(hauteur(arbre->gauche), hauteur(arbre->droite)+1);
}

pArbre rotation_gauche(pArbre arbre)
{
    pArbre temp = arbre->gauche;
    arbre->gauche = temp->droite;
    temp->droite = arbre;
    arbre->nb_donnees = max(hauteur(arbre->gauche), hauteur(arbre->droite)) + 1;
    temp->nb_donnees = max(hauteur(temp->gauche), arbre->nb_donnees) + 1;

    return temp;
}

pArbre rotation_droite(pArbre arbre)
{
    pArbre temp = arbre->droite;
    arbre->droite = temp->gauche;
    temp->gauche = arbre;
    arbre->nb_donnees = max(hauteur(arbre->gauche), hauteur(arbre->droite)) + 1;
    temp->nb_donnees = max(hauteur(temp->droite), arbre->nb_donnees) + 1;

    return temp;
}

pArbre double_rotation_gauche(pArbre arbre){
    arbre->gauche = rotation_droite(arbre->gauche);
    return rotation_gauche(arbre);
}

pArbre double_rotation_droite(pArbre arbre){
    arbre->droite = rotation_gauche(arbre->droite);
    return rotation_droite(arbre);
}

pArbre ajout_noeud_AVL(pArbre arbre, float *donnees, int nb_donnees)
{
    if (PTR_NUL(arbre))
    {
        pArbre nouveau = malloc(sizeof(pArbre));
        nouveau->donnees = donnees;
        nouveau->nb_donnees = nb_donnees;
        nouveau->gauche = NULL;
        nouveau->droite = NULL;
        return nouveau;
    }

    if (donnees[0] < arbre->donnees[0])
    {
        arbre->gauche = ajout_noeud_AVL(arbre->gauche, donnees, nb_donnees);
        if (hauteur(arbre->gauche) - hauteur(arbre->droite) == 2)
        {
            if (donnees[0] < arbre->gauche->donnees[0])
            {
                arbre = rotation_gauche(arbre);
            }
            else
            {
                arbre = double_rotation_gauche(arbre);
            }
        }
    }
    else
    {
        arbre->droite = ajout_noeud_AVL(arbre->droite, donnees, nb_donnees);
        if (hauteur(arbre->droite) - hauteur(arbre->gauche) == 2)
        {
            if (donnees[0] > arbre->droite->donnees[0])
            {
                arbre = rotation_droite(arbre);
            }
            else
            {
                arbre = double_rotation_droite(arbre);
            }
        }
    }

    arbre->nb_donnees = max(hauteur(arbre->gauche), hauteur(arbre->droite)) + 1;
    return arbre;
}

pArbre creer_AVL(float *tab_temp, int taille_tab, int direction_tri)
{
    pArbre a = NULL;
    for (int i = 0; i < taille_tab; i++)
    {
        a = ajout_noeud_AVL(a, tab_temp[i]);
    }
    return a;
}
