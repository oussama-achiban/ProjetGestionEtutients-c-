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
// ************************************************************-TRIER
void trier(Etudiant *listeEtudiants, int numEtudiants) {
    printf("\nVeuillez choisir une option de tri :\n");
    printf("a. Trier par numero Apogee\n");
    printf("b. Trier par moyenne\n");
    printf("c. Trier par date d inscription\n");
    printf("Votre choix : ");
    char optionTri;
    scanf(" %c", &optionTri);

    switch (optionTri) {
        case 'a':
            trier_par_apogee(listeEtudiants, numEtudiants);
            break;
        case 'b':
            trier_par_moyenne(listeEtudiants, numEtudiants);
            break;
        case 'c':
            trier_par_date_inscription(listeEtudiants, numEtudiants);
            break;
        default:
            printf("\nOption de tri invalide.\n");
    }
}
// ************************************************************-SOUS FONCTION TRIER
// ************************-TRIE APPOG-*********************
void trier_par_apogee(Etudiant *listeEtudiants, int numEtudiants) {
    int i,j;
	for ( i = 0; i < numEtudiants - 1; i++) {
        for ( j = i + 1; j < numEtudiants; j++) {
            if (strcmp(listeEtudiants[j].apogee, listeEtudiants[i].apogee) < 0) {
                Etudiant temp = listeEtudiants[i];
                listeEtudiants[i] = listeEtudiants[j];
                listeEtudiants[j] = temp;
            }
        }
	}
    printf("Les etudiants ont ete tries par numero Apogee avec succes.\n");
    FILE *p=fopen("DATA_TRIE_APOGEE.txt","w");
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
}
// ************************-TRIE MOYENNE-********************
void trier_par_moyenne(Etudiant *listeEtudiants, int numEtudiants) {
    int i,j;
	for ( i = 0; i < numEtudiants - 1; i++) {
        for ( j = 0; j < numEtudiants - i - 1; j++) {
            if (listeEtudiants[j].moyenne < listeEtudiants[j + 1].moyenne) {
                Etudiant temp = listeEtudiants[j];
                listeEtudiants[j] = listeEtudiants[j + 1];
                listeEtudiants[j + 1] = temp;
            }
        }
    }
    printf("Les etudiants ont ete tries par moyenne avec succes.\n");
    FILE *p=fopen("DATA_TRIE_MOYENNE.txt","w");
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
}
// ************************-TRIE DATE.I-*********************
void trier_par_date_inscription(Etudiant *listeEtudiants, int numEtudiants) {
    int i;
	for ( i = 1; i < numEtudiants; i++) {
        Etudiant temp = listeEtudiants[i];
        int j = i - 1;
        while (j >= 0 && strcmp(listeEtudiants[j].date_inscription, temp.date_inscription) > 0) {
            listeEtudiants[j + 1] = listeEtudiants[j];
            j--;
        }
        listeEtudiants[j + 1] = temp;
    }
    printf("Les etudiants ont ete tries par date d'inscription avec succes.\n");
    FILE *p=fopen("DATA_TRIE_INSCRIPTION.txt","w");
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
}