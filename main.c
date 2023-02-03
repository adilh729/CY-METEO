#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./ABR.h"
#include "./AVL.h"
#include "./TAB.h"

int main(int argc, char *argv[])
{
    char *fichier_entree = NULL;
    char *fichier_sortie = NULL;

    FILE *f_entree = NULL; // fichier d'entrée
    FILE *f_sortie = NULL; // fichier de sortie

    int direction_tri = NULL; // ordre croissant/décroissant
    int type_tri;

    int i = 0;
    char lettre;
    int taille_tab = 1;
    

    // Stock la valeur de la ligne actuelle avant de l'affecter à un chaînon
    float *tab_temp = malloc(sizeof(float) * taille_tab);

    // Definie les variables des chaînons
    int h = 0;
    pArbre a = NULL;
    pChainon pliste = NULL;
    pChainon chainon_recherche = NULL;

    // Traite les arguments du programme
    for (i = 1; i < argc; i++)
    {
        if (strcmp("-f", argv[i]) == 0)
        {
            fichier_entree = argv[i + 1];
        }
        else if (strcmp("-o", argv[i]) == 0)
        {
            fichier_sortie = argv[i + 1];
        }
        // Les différents type de tris[TAB(0)/ABR(1)/AVL(2)]
        else if (strcmp("--tab", argv[i]) == 0)
        {
            type_tri = 0;
        }
        else if (strcmp("--abr", argv[i]) == 0)
        {
            type_tri = 1;
        }
        else if (strcmp("--avl", argv[i]) == 0)
        {
            type_tri = 2;
        }
        // La direction du tri (ordre croissant/décroissant)
        else if (strcmp("-r", argv[i]) == 0)
        {
            direction_tri = 1;
        }

        // Ouverture du fichier
        f_entree = fopen("FinalWeather.csv", "r");
        if (f_entree == NULL)
        {
            printf("Impossible d'ouvrir le fichier d'entrée\n");
            exit(1);
        }
        char *ligne_temp = calloc(1, sizeof(char));
        while ((lettre = fgetc(f_entree)) != EOF)
        {
            // Si la valeur actuelle est un espace, on stocke la valeur actuelle dans le tableau temporaire
            if (lettre == ' ' || lettre == '\n')
            {
                // Ajouter la valeur actuelle au tableau temporaire
                tab_temp[i] = atof(ligne_temp);

                // Ajouter un espace pour le prochain nombre
                taille_tab++;
                tab_temp = realloc(tab_temp, sizeof(float) * taille_tab);
                i++;
            }
            else
            {
                // Ajouter la valeur actuelle à la ligne temporaire
                char c[2];
                c[0] = lettre;
                c[1] = '\0';
                ligne_temp = strcat(ligne_temp, c);
            }
        }

        // Ajouter la dernière valeur
        tab_temp[i] = atof(ligne_temp);

        // Fermer le fichier
        fclose(f_entree);

        // Choisir le type de tri en fonction des arguments
        switch (type_tri)
        {
        case 0: // 0 pour TAB(liste chainée)
            pliste = creer_liste(tab_temp, i + 1, direction_tri);
            break;
        case 1: // 1 pour ABR(arbre binaire de recherche)
            a = creer_ABR(tab_temp, i + 1, direction_tri);
            break;
        case 2: // 2 pour AVL(arbre binaire à hauteur équilibrée)
            a = creer_AVL(tab_temp, i + 1, direction_tri);
            break;
        default:
            break;
        }

        // Ouvre le fichier de sortie
        FILE *fichier_sortie = fopen("test_sortie.txt", "w");

        if (f_sortie == NULL)
        {
            printf("Le fichier de sortie n'a pas pu être ouvert\n");
            return 1;
        }

        // Ecrire les données dans le fichier de sortie
        if (type_tri == 0)
        {
            chainon_recherche = pliste;
            if(chainon_recherche != NULL)
            {
                fprintf(f_sortie, "%f\n", chainon_recherche->suivant);
                chainon_recherche = chainon_recherche->suivant;
            }
            else{
                switch (type_tri){
                case 0: // 0 pour TAB(liste chainée)
                    chainon_recherche = pliste;
                    while (chainon_recherche != NULL)
                    {
                        fprintf(f_sortie, "%.2f\n", chainon_recherche->suivant);
                        chainon_recherche = chainon_recherche->suivant;
                    }
                    break;
                case 1: // 1 pour ABR(arbre binaire de recherche)
                    parcours_infixe(a, f_sortie);
                    break;
                case 2: // 2 pour AVL(arbre binaire à hauteur équilibrée)
                    parcours_infixe(a, f_sortie);
                    break;
                default:
                    break;
                }
                // Fermer le fichier de sortie
                fclose(f_sortie);

                switch (type_tri)
                {
                case 0: // 0 pour TAB(liste chainée)
                    liberer_liste(pliste);
                    break;
                case 1: // 1 pour ABR(arbre binaire de recherche)
                    liberer_ABR(a);
                    break;
                case 2: // 2 pour AVL(arbre binaire à hauteur équilibrée)
                    liberer_AVL(a);
                    break;
                default:
                    break;
                }
                //Libérer la mémoire alloué
                free(tab_temp);

                return 0;
            }
        }
    }
}