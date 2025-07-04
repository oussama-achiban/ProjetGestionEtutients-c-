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
// ************************************************************-MODIFIER
void modifierEtudiant(Etudiant *listeEtudiants, int numEtudiants) {
    char apogee[20];
    printf("Entrez le code d'apogee de l'etudiant a modifier : ");
    scanf("%s", apogee);
    int i;
    for ( i = 0; i < numEtudiants; i++) {
        if (strcmp(listeEtudiants[i].apogee, apogee) == 0) {
            printf("Veuillez saisir les nouvelles informations de l'etudiant :\n");
            saisirInfosEtudiant(&listeEtudiants[i]);
            printf("Les informations de l'etudiant ont ete mises a jour avec succes.\n");
            return;
        }
    }
    printf("Aucun etudiant avec le code d'apogee %s n'a ete trouve.\n", apogee);
}
