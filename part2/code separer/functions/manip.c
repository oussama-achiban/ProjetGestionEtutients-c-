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
// ************************************************************-AFFICHAGE MENU
void afficherMenu() {
    printf("\nCette application permet d'effectuer les taches suivantes :\n");
    printf("1. Ajouter un ou plusieurs etudiants\n");
    printf("2. Modifier les informations sur l'etudiant\n");
    printf("3. Consulter :\n");
    printf("   a. La liste de tous les etudiants\n");
    printf("   b. La liste des etudiants admis seulement\n");
    printf("   c. La liste des etudiants d'une filiere specifiee\n");
    printf("4. Trier les etudiants par :\n");
    printf("   a. Numero Apogee\n");
    printf("   b. Moyenne\n");
    printf("   c. Date d'inscription\n");
    printf("5. Rechercher :\n");
    printf("   a. Un etudiant par le Numero apogee\n");
    printf("   b. Tous les etudiants ayant meme :\n");
    printf("      - Nom\n");
    printf("      - Prenom\n");
    printf("      - Date d'inscription\n");
    printf("6. Supprimer un etudiant\n");
    printf("0. Quitter\n");
}
// ************************************************************-MENU PRINCIPALE
void menuPrincipal(Etudiant **listeEtudiants, int *numEtudiants) {
    int choix;
    FILE *p = fopen("DATA.txt", "r");
    if (p == NULL) {
        printf("Erreur : le fichier DATA.txt n'existe pas.\n");
    } else {
    	listeEtudiants= malloc(sizeof(Etudiant));
        int i = 0; // Initialisez l'indice du tableau d'�tudiants
        while (fscanf(p, "|%s|%s|%s|%s|%s|%s|%f|\n",
                      (*listeEtudiants)[i].apogee,
                      (*listeEtudiants)[i].nom,
                      (*listeEtudiants)[i].prenom,
                      (*listeEtudiants)[i].sexe,
                      (*listeEtudiants)[i].date_naissance,
                      (*listeEtudiants)[i].filiere,
                      &(*listeEtudiants)[i].moyenne) != EOF) {
            // Incr�mente l'indice pour passer � l'�tudiant suivant
            i++;
            listeEtudiants= malloc((i+1)*sizeof(Etudiant));
        }
        fclose(p);
        *numEtudiants = i; // Mettez � jour le nombre total d'�tudiants
    }
	int i ;
	char apogee[20];
    do {
        afficherMenu();
        printf("\nChoisissez une option (0-6) : ");
        scanf("%d", &choix);
        clearScreen();
        switch (choix) {
		    case 1:
                printf("-----------------------------------------|STUDENT HUB|------------------------------------------------");
                printf("\nCombien d'etudiants voulez-vous ajouter ? ");
                int nombreEtudiants;
                scanf("%d", &nombreEtudiants);
                *listeEtudiants = realloc(*listeEtudiants, (*numEtudiants + nombreEtudiants) * sizeof(Etudiant));
                if (*listeEtudiants == NULL) {
                    fprintf(stderr, "Erreur d'allocation memoire pour les nouveaux etudiants.\n");
                    exit(EXIT_FAILURE);
                }
                for (i = 0; i < nombreEtudiants; i++) {
                    printf("                                    \nETUDIANT: %d        \n", *numEtudiants + i + 1);
                    saisirInfosEtudiant(&(*listeEtudiants)[*numEtudiants + i]); 
                    clearScreen();
                }
                *numEtudiants += nombreEtudiants;

                // Writing added students to file
                p = fopen("DATA.txt", "w");
                if (p == NULL) {
                    printf("Erreur lors de l'ouverture du fichier.\n");
                    exit(EXIT_FAILURE);
                }
                // Write header line
                fprintf(p, "| Appogee |     Nom       |    Prenom     |  Sexe  | Date de Naissance |    Filliere   | Moyenne | Decision |\n");

                // Write student information
                for (i = *numEtudiants - nombreEtudiants; i < *numEtudiants; i++) {
                    fprintf(p, "|%20s|%20s|%20s|%8s|%20s|%20s|%9.2f|\n",
                            (*listeEtudiants)[i].apogee,
                            (*listeEtudiants)[i].nom,
                            (*listeEtudiants)[i].prenom,
                            ((*listeEtudiants)[i].sexe == HOMME) ? "Homme" : "Femme",
                            (*listeEtudiants)[i].date_naissance,
                            (*listeEtudiants)[i].filiere,
                            (*listeEtudiants)[i].moyenne);
                }
                fclose(p);
                break;

            case 2:
                modifierEtudiant(*listeEtudiants, *numEtudiants);
                p = fopen("DATA.txt", "w");
                if (p == NULL) {
                    printf("Erreur lors de l'ouverture du fichier.\n");
                    exit(EXIT_FAILURE);
                }
                // Write header line
                fprintf(p, "| Appogee |     Nom       |    Prenom     |  Sexe  | Date de Naissance |    Filliere   | Moyenne | Decision |\n");

                // Write student information
                for (i = 0; i < *numEtudiants; i++) {
                    fprintf(p, "|%8s|%15s|%15s|%8s|%18s|%15s|%9.2f|\n",
                            (*listeEtudiants)[i].apogee,
                            (*listeEtudiants)[i].nom,
                            (*listeEtudiants)[i].prenom,
                            ((*listeEtudiants)[i].sexe == HOMME) ? "Homme" : "Femme",
                            (*listeEtudiants)[i].date_naissance,
                            (*listeEtudiants)[i].filiere,
                            (*listeEtudiants)[i].moyenne);
                }
                fclose(p);
                break;

            case 3:
                consulter(*listeEtudiants, *numEtudiants);
                break;
            case 4:
                trier(*listeEtudiants, *numEtudiants);
                break;
            case 5:
                rechercher(*listeEtudiants, *numEtudiants);
                break;
            case 6:
                
                printf("Entrez le code d'apogee de l'etudiant a supprimer : ");
                scanf("%s", apogee);
                supprimerEtudiant(listeEtudiants, numEtudiants, apogee);
                break;
            case 0:
                printf("\nFin du programme.\n");
                break;
            default:
                printf("\nChoix invalide. Veuillez choisir une option valide.\n");
        }

        char reponse;
        printf("\nVoulez-vous afficher le menu principal a nouveau ? (O/N) : ");
        scanf(" %c", &reponse);
        if (reponse != 'O' && reponse != 'o') {
            break;
        }

        clearScreen();

    } while (choix != 0);
    gotoxy(55,10);printf("merci pour");
    gotoxy(50,12);printf(" visite STUDENT HUB");
    getchar(); // Attendre une touche pour terminer
    system("cls"); // Effacer l'�cran
}