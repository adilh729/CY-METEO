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
    int equilibre;
} Arbre, *pArbre;


int max(int x, int y); 

int hauteur(pArbre arbre);


pArbre rotation_gauche(pArbre arbre);


pArbre rotation_droite(pArbre arbre);


pArbre double_rotation_gauche(pArbre arbre);
    

pArbre double_rotation_droite(pArbre arbre);
    
pArbre ajout_noeud_AVL(pArbre arbre, float *donnees, int nb_donnees);

pArbre creer_AVL(float *tab_temp, int taille_tab, int direction_tri);
