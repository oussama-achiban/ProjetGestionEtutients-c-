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
// ************************************************************-RECHERCHER
void rechercher(Etudiant *listeEtudiants, int numEtudiants) {
    printf("\nVeuillez choisir une option de recherche :\n");
    printf("   a. Un etudiant par le Numero apogee\n");
    printf("   b. Tous les etudiants ayant meme :\n");
    printf("      - Nom\n");
    printf("      - Prenom\n");
    printf("      - Date d'inscription\n");
    printf("Votre choix : ");
    char optionRecherche;
    scanf(" %c", &optionRecherche);
    switch (optionRecherche) {
        case 'a':
            rechercher_par_apogee(listeEtudiants, numEtudiants);
            break;
        case 'b': {
            printf("\nVeuillez choisir une option sous 'b' :\n");
            printf("   a. Recherche par Nom\n");
            printf("   b. Recherche par Prenom\n");
            printf("   c. Recherche par Date d'inscription\n");
            printf("Votre choix : ");
            char optionSousB;
            scanf(" %c", &optionSousB);

            switch (optionSousB) {
                case 'a':
                    printf("\nRecherche par Nom :\n");
                    rechercher_par_nom(listeEtudiants, numEtudiants);
                    break;
                case 'b':
                    printf("\nRecherche par Prenom :\n");
                    rechercher_par_prenom(listeEtudiants, numEtudiants);
                    break;
                case 'c':
                    printf("\nRecherche par Date d'inscription :\n");
                    rechercher_etudiants_par_date_inscription(listeEtudiants, numEtudiants);
                    break;
                default:
                    printf("\nOption de recherche invalide.\n");
                    break;
            }
            break;
        }
        default:
            printf("\nOption de recherche invalide.\n");
            break;
    }
}
// ************************************************************-SOUS FONCTION RECHERCHE
// ************************-RECHERCHE APPO-*********************
void rechercher_par_apogee(Etudiant *listeEtudiants, int numEtudiants) {
    char apogee[20];
    printf("Entrez le numero apogee de l'etudiant : ");
    scanf("%s", apogee);
    int found = 0;
    int i;
	for (i = 0; i < numEtudiants; i++) {
        if (strcmp(listeEtudiants[i].apogee, apogee) == 0) {
            found = 1;
            printf("\nEtudiant trouve :\n");
            afficherEtudiant(&listeEtudiants[i], 1);
            FILE *p=fopen("rechercher_par_apogee.txt","w");
                if (p == NULL) {
                    printf("Erreur lors de l'ouverture du fichier.\n");
                    exit(0);
                }
                for(i=0;i<numEtudiants;i++){
                    fprintf(p,"|%8s|%15s|%15s|%8s|%18s|%15s|%9.2f|\n",
                        listeEtudiants[i].apogee,
                        listeEtudiants[i].nom,
                        listeEtudiants[i].prenom,
                        (listeEtudiants[i].sexe == HOMME) ? "Homme" : "Femme",
                        listeEtudiants[i].date_naissance,
                        listeEtudiants[i].filiere,
                        listeEtudiants[i].moyenne);
                }
                fclose(p);
            break;
        }
    }
    if (!found) {
        printf("\nAucun etudiant trouve avec le numero apogee %s.\n", apogee);
    }
}
// ************************-RECHERCHE PAR NOM-*********************
void rechercher_par_nom(Etudiant *listeEtudiants, int numEtudiants) {
    char nom[50];
    printf("Entrez le nom de l'etudiant a chercher : ");
    scanf("%s", nom);
    int found = 0;
    printf("Liste des etudiants avec le meme nom :\n");
    int i;
	for ( i = 0; i < numEtudiants; i++) {
        if (strcmp(listeEtudiants[i].nom, nom) == 0) {
            afficherEtudiant(&listeEtudiants[i], 1);
            FILE *p=fopen("rechercher_par_nom.txt","w");
                if (p == NULL) {
                    printf("Erreur lors de l'ouverture du fichier.\n");
                    exit(0);
                }
                for(i=0;i<numEtudiants;i++){
                    fprintf(p,"|%8s|%15s|%15s|%8s|%18s|%15s|%9.2f|\n",
                        listeEtudiants[i].apogee,
                        listeEtudiants[i].nom,
                        listeEtudiants[i].prenom,
                        (listeEtudiants[i].sexe == HOMME) ? "Homme" : "Femme",
                        listeEtudiants[i].date_naissance,
                        listeEtudiants[i].filiere,
                        listeEtudiants[i].moyenne);
                }
                fclose(p);
            found = 1;
        }
    }
    if (!found) {
        printf("Aucun etudiant trouve avec ce nom\n");
    }
}

// ************************-RECHERCHE PAR PRENOM-*********************
void rechercher_par_prenom(Etudiant *listeEtudiants, int numEtudiants) {
    char prenom[50];
    printf("Entrez le prenom de l'etudiant a chercher : ");
    scanf("%s", prenom);
    int found = 0;
    printf("Liste des etudiants avec le meme prenom :\n");
    int i;
	for (i = 0; i < numEtudiants; i++) {
        if (strcmp(listeEtudiants[i].prenom, prenom) == 0) {
            afficherEtudiant(&listeEtudiants[i], 1);
            FILE *p=fopen("rechercher_par_prenom.txt","w");
            if (p == NULL) {
                printf("Erreur lors de l'ouverture du fichier.\n");
                exit(0);
            }
            for(i=0;i<numEtudiants;i++){
                fprintf(p,"|%8s|%15s|%15s|%8s|%18s|%15s|%9.2f|\n",
                    listeEtudiants[i].apogee,
                    listeEtudiants[i].nom,
                    listeEtudiants[i].prenom,
                    (listeEtudiants[i].sexe == HOMME) ? "Homme" : "Femme",
                    listeEtudiants[i].date_naissance,
                    listeEtudiants[i].filiere,
                    listeEtudiants[i].moyenne);
            }
            fclose(p);
            found = 1;
        }
    }
    if (!found) {
        printf("Aucun etudiant trouve avec ce prenom\n");
    }
}

// ************************-RECHERCHE PAR DATE INSCRIPTION-*********************
void rechercher_etudiants_par_date_inscription(Etudiant *listeEtudiants, int numEtudiants) {
    char date_inscription[20];
    printf("Entrez la date d'inscription de l'etudiant a chercher (jj/mm/aaaa) : ");
    scanf("%s", date_inscription);
    int found = 0;
    printf("Liste des etudiants avec la meme date d'inscription :\n");
    int i;
	for (i = 0; i < numEtudiants; i++) {
        if (strcmp(listeEtudiants[i].date_inscription, date_inscription) == 0) {
            afficherEtudiant(&listeEtudiants[i], 1);
            FILE *p=fopen("rechercher_etudiants_par_date_inscription.txt","w");
                if (p == NULL) {
                    printf("Erreur lors de l'ouverture du fichier.\n");
                    exit(0);
                }
                for(i=0;i<numEtudiants;i++){
                    fprintf(p,"|%8s|%15s|%15s|%8s|%18s|%15s|%9.2f|\n",
                        listeEtudiants[i].apogee,
                        listeEtudiants[i].nom,
                        listeEtudiants[i].prenom,
                        (listeEtudiants[i].sexe == HOMME) ? "Homme" : "Femme",
                        listeEtudiants[i].date_naissance,
                        listeEtudiants[i].filiere,
                        listeEtudiants[i].moyenne);
                }
                fclose(p);
            found = 1;
        }
    }
    if (!found) {
        printf("Aucun etudiant trouve avec cette date d'inscription\n");
    }
}
