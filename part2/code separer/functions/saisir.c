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
// ************************************************************-CLEAR
void clearScreen() {
    system(CLEAR_SCREEN);
}
// ************************************************************-SAISIE INFOS
void gotoxy(int x,int y){
	COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
//******************************************************************************
void saisirInfosEtudiant(Etudiant *etudiant) {
	
	gotoxy(0,5);printf("Nom de l'etudiant                                        : ");
    
    gotoxy(0,6);printf("Prenom de l'etudiant                                     : ");
    
    gotoxy(0,7);printf("Sexe de l'etudiant (0 pour Homme, 1 pour Femme)          : ");
    
    gotoxy(0,8);printf("Date de naissance de l'etudiant (jj/mm/aaaa)             : ");
    
    gotoxy(0,9);printf("Filiere de l'etudiant                                    : ");
    
    gotoxy(0,10);printf("Numero d'apogee de l'etudiant                            : ");
    
    gotoxy(0,11);printf("Code Massar de l'etudiant                                : ");
    
    gotoxy(0,12);printf("Date d'inscription de l'etudiant (jj/mm/aaaa)            : ");
    
    gotoxy(0,13);printf("L'etudiant a-t-il ete resilie ? (0 pour Non, 1 pour Oui) : ");
    
    gotoxy(0,15);printf("Bourse de l'etudiant (0 pour Non, 1 pour Oui)            : ");
    
    gotoxy(0,16);printf("Assurance medicale de l'etudiant (0 pour CNOPS, 1 pour CNSS, 2 pour Aucune) : ");
    
    gotoxy(0,17);printf("Nombre de modules : ");
    //******************************************************************************
    gotoxy(60,5);scanf("%s", etudiant->nom);
    
    gotoxy(60,6);scanf("%s", etudiant->prenom);
    
    gotoxy(60,7);scanf("%d", (int *)&etudiant->sexe);
    
    gotoxy(60,8);scanf("%s", etudiant->date_naissance);
    
    gotoxy(60,9);scanf("%s", etudiant->filiere);
    
    gotoxy(60,10);scanf("%s", etudiant->apogee);
    
    gotoxy(60,11);scanf("%s", etudiant->code_massar);
    
    gotoxy(60,12);scanf("%s", etudiant->date_inscription);
    
    gotoxy(60,13);scanf("%d", (int *)&etudiant->resiliation);
    if (etudiant->resiliation == RESILIE) {
        printf("Date de resiliation de l'etudiant (jj/mm/aaaa)         : ");
        scanf("%s", etudiant->date_resiliation);
    }
    
    gotoxy(60,15);scanf("%d", (int *)&etudiant->bourse);
    
    gotoxy(80,16);scanf("%d", (int *)&etudiant->assurance);
    
    gotoxy(30,17);scanf("%d", &etudiant->modules);
    
    if (etudiant->modules > 0) {
        etudiant->notes = (float *)malloc(etudiant->modules * sizeof(float));
        if (etudiant->notes == NULL) {
            fprintf(stderr, "Erreur d'allocation memoire pour les notes.\n");
            exit(EXIT_FAILURE);
        }
        printf("Saisissez les notes de l'etudiant :\n");
        float sommeNotes = 0;
        int i;
        for ( i = 0; i < etudiant->modules; i++) {
            printf("Note %d : ", i + 1);
            scanf("%f", &etudiant->notes[i]);
            sommeNotes += etudiant->notes[i];
        }
        etudiant->moyenne = sommeNotes / etudiant->modules;
        printf("Moyenne de l'etudiant : %.2f\n", etudiant->moyenne);
    }
    printf("Semestre de l'etudiant : ");
    scanf("%s", etudiant->semestre);
    printf("Nombre de semestres valides : ");
    scanf("%d", &etudiant->semestres_valides);
    printf("Nombre de semestres non valides : ");
    scanf("%d", &etudiant->semestres_non_valides);
    printf("Nombre de semestres bloques : ");
    scanf("%d", &etudiant->semestres_bloques);
    
}
