// oussama achiban
//2122509
//GP_1
//Abdelmouaiz elmaghoussi
//Appogee 2130138
//GP_3
/////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#ifdef _WIN32
#define CLEAR_SCREEN "cls"
#else
#define CLEAR_SCREEN "clear"
#endif
#define MAX_ATTEMPTS 5
#define USERNAME "admin"
#define PASSWORD "smis4"
#include <windows.h>
#include "../header/student.h"
// ************************************************************-SUPPRIMER

// ************************************************************-SUPPRIMER
void supprimerEtudiant(Etudiant **listeEtudiants, int *numEtudiants, char apogee[]) {
    bool trouve = false;
    int i,j;
	for ( i = 0; i < *numEtudiants; i++) {
        if (strcmp((*listeEtudiants)[i].apogee, apogee) == 0) {
            for ( j = i; j < *numEtudiants - 1; j++) {
                (*listeEtudiants)[j] = (*listeEtudiants)[j + 1];
            }
            (*numEtudiants)--;
                *listeEtudiants = (Etudiant *)realloc(*listeEtudiants, (*numEtudiants) * sizeof(Etudiant));
            if (*listeEtudiants == NULL && *numEtudiants > 0) {
                fprintf(stderr, "Erreur de reallocation memoire.\n");
                FILE *p=fopen("supprimer.txt","w");
                if (p == NULL) {
                    printf("Erreur lors de l'ouverture du fichier.\n");
                    exit(0);
                }
                for(i=0;i<numEtudiants;i++){
                    fprintf(p,"|%8s|%15s|%15s|%8s|%18s|%15s|%9.2f|\n",
                        listeEtudiants[i]->apogee,
                        listeEtudiants[i]->nom,
                        listeEtudiants[i]->prenom,
                        (listeEtudiants[i]->sexe == HOMME) ? "Homme" : "Femme",
                        listeEtudiants[i]->date_naissance,
                        listeEtudiants[i]->filiere,
                        listeEtudiants[i]->moyenne);
                }
                fclose(p);
                exit(EXIT_FAILURE);
            }
            trouve = true;
            break;
        }
    }
    if (trouve) {
        printf("Etudiant avec le code d'apogee %s supprime avec succes.\n", apogee);
    } else {
        printf("Aucun etudiant avec le code d'apogee %s n'a ete trouve.\n", apogee);
    }
    
}
