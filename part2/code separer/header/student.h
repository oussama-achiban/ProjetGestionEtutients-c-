// student.h
#ifndef STUDENT_H
#define STUDENT_H
#include <stdbool.h>
//*************************************************************-ENUMS
typedef enum { HOMME, FEMME } Sexe;
typedef enum { NON, OUI } Bourse;
typedef enum { CNOPS, CNSS, AUCUNE } Assurance;
typedef enum { NON_RESILIE, RESILIE } Resiliation;
// ************************************************************-STRUCTS
typedef struct {
    char nom[50];
    char prenom[50];
    Sexe sexe; 
    char date_naissance[20]; 
    char filiere[50]; 
    char apogee[20]; 
    char code_massar[20]; 
    char date_inscription[20]; 
    char date_resiliation[20]; 
    Bourse bourse; 
    Assurance assurance; 
    Resiliation resiliation; 
    int modules; 
    float *notes; 
    float moyenne;
    char semestre[5]; 
    int semestres_valides; 
    int semestres_non_valides; 
    int semestres_bloques; 
} Etudiant;
// ************************************************************-DECLARATION
void afficherEtudiant(Etudiant listeEtudiants[], int numEtudiants);
void afficher_etudiants_admis(Etudiant listeEtudiants[], int numEtudiants);
void afficher_etudiants_filiere(Etudiant listeEtudiants[], int numEtudiants);
void trier_par_apogee(Etudiant listeEtudiants[], int numEtudiants);
void trier_par_moyenne(Etudiant listeEtudiants[], int numEtudiants);
void trier_par_date_inscription(Etudiant listeEtudiants[], int numEtudiants);
void rechercher_par_apogee(Etudiant listeEtudiants[], int numEtudiants);
void rechercher_par_nom(Etudiant *listeEtudiants, int numEtudiants);
void rechercher_par_prenom(Etudiant *listeEtudiants, int numEtudiants);
void rechercher_etudiants_par_date_inscription(Etudiant *listeEtudiants, int numEtudiants);
void clearScreen();
void gotoxy(int,int);
void lock();
void saisirInfosEtudiant(Etudiant *etudiant);
void modifierEtudiant(Etudiant *listeEtudiants, int numEtudiants);
void consulter(Etudiant *listeEtudiants, int numEtudiants);
void rechercher(Etudiant *listeEtudiants, int numEtudiants);
void trier(Etudiant *listeEtudiants, int numEtudiants);
void supprimerEtudiant(Etudiant **listeEtudiants, int *numEtudiants, char apogee[]);
#endif // STUDENT_H

