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
        printf("Date de resiliation de l'etudiant (jj/mm/aaaa)       : ");
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
        for (i = 0; i < etudiant->modules; i++) {
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
// ************************************************************-CONSULTER
void consulter(Etudiant *listeEtudiants, int numEtudiants) {
    printf("\nVeuillez choisir une option de consultation :\n");
    printf("a. La liste de tous les etudiants\n");
    printf("b. La liste des etudiants admis seulement\n");
    printf("c. La liste des etudiants d'une filiere specifiee\n");
    printf("Votre choix : ");
    char optionConsultation;
    scanf(" %c", &optionConsultation);

    switch (optionConsultation) {
        case 'a':
            afficherEtudiant(listeEtudiants, numEtudiants);
            break;
        case 'b':
            afficher_etudiants_admis(listeEtudiants, numEtudiants);
            break;
        case 'c':
            afficher_etudiants_filiere(listeEtudiants, numEtudiants);
            break;
        default:
            printf("\nOption de consultation invalide.\n");
    }
}
// ************************************************************-SOUS FONCTION CONSULTER
// ************************-AFFICHE INFOS-*********************
void afficherEtudiant(Etudiant listeEtudiants[], int numEtudiants) {
    printf("\n");
    printf("| Appogee |     Nom       |    Prenom     |  Sexe  | Date de Naissance |    Filliere   | Moyenne | Decision |\n");
    int i,j;
	for ( i = 0; i < numEtudiants; i++) {
        char decision[10];
        if (listeEtudiants[i].moyenne >= 10.0) {
            int toutesSuperieuresA5 = 1;
            for ( j = 0; j < listeEtudiants[i].modules; j++) {
                if (listeEtudiants[i].notes[j] < 5.0) {
                    toutesSuperieuresA5 = 0;
                    break;  
                }
            }
            if (toutesSuperieuresA5) {
                strcpy(decision, "Admis");
            } else {
                strcpy(decision, "Non admis");
            }
        } else {
            strcpy(decision, "Non admis");
        }
        printf("|%8s|%15s|%15s|%8s|%18s|%15s|%9.2f|%9s|\n",
            listeEtudiants[i].apogee,
            listeEtudiants[i].nom,
            listeEtudiants[i].prenom,
            (listeEtudiants[i].sexe == HOMME) ? "Homme" : "Femme",
            listeEtudiants[i].date_naissance,
            listeEtudiants[i].filiere,
            listeEtudiants[i].moyenne,decision);
    }
}
// ************************-AFFICHE ADMIS-*********************
void afficher_etudiants_admis(Etudiant *listeEtudiants, int numEtudiants) {
    printf("Liste des etudiants admis :\n");
    printf("| Appogee |     Nom       |    Prenom     |  Sexe  | Date de Naissance |    Filliere   | Moyenne | Decision |\n");
    int i,j;
	for ( i = 0; i < numEtudiants; i++) {
        char decision[10];
        if (listeEtudiants[i].moyenne >= 10.0) {
            int toutesSuperieuresA5 = 1;
            for ( j = 0; j < listeEtudiants[i].modules; j++) {
                if (listeEtudiants[i].notes[j] < 5.0) {
                    toutesSuperieuresA5 = 0;
                    break;  
                }
            }
            if (toutesSuperieuresA5) {
                strcpy(decision, "Admis");
            } else {
                strcpy(decision, "Non admis");
            }
        } else {
            strcpy(decision, "Non admis");
        }
        if(strcmp(decision, "Admis") == 0) {
            printf("|%8s|%15s|%15s|%8s|%18s|%15s|%9.2f|%9s|\n",
                listeEtudiants[i].apogee,
                listeEtudiants[i].nom,
                listeEtudiants[i].prenom,
                (listeEtudiants[i].sexe == HOMME) ? "Homme" : "Femme",
                listeEtudiants[i].date_naissance,
                listeEtudiants[i].filiere,
                listeEtudiants[i].moyenne,
                decision);
        }
    }
}
// ************************-AFFICHE FILLIERE-******************
void afficher_etudiants_filiere(Etudiant *listeEtudiants, int numEtudiants) {
    char filiere[50];
    printf("Entrez le nom de la filiere : ");
    scanf("%s", filiere);
    printf("Liste des etudiants de la filiere %s :\n", filiere);
    int i;
	for ( i = 0; i < numEtudiants; i++) {
        if (strcmp(listeEtudiants[i].filiere, filiere) == 0) {
            afficherEtudiant(&listeEtudiants[i], 1);
        }
    }
}
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
	for (i = 0; i < numEtudiants; i++) {
        if (strcmp(listeEtudiants[i].nom, nom) == 0) {
            afficherEtudiant(&listeEtudiants[i], 1);
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
	for ( i = 0; i < numEtudiants; i++) {
        if (strcmp(listeEtudiants[i].date_inscription, date_inscription) == 0) {
            afficherEtudiant(&listeEtudiants[i], 1);
            found = 1;
        }
    }
    if (!found) {
        printf("Aucun etudiant trouve avec cette date d'inscription\n");
    }
}
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
// ************************************************************-FONCTION FREE
void freeEtudiants(Etudiant* listeEtudiants, int numEtudiants) {
    int i;
	for ( i = 0; i < numEtudiants; i++) {
        free(listeEtudiants[i].notes);
    }
    free(listeEtudiants);
}
// ************************************************************-FONCTION-LOCK
void lock() {
    gotoxy(55,10);printf("Bonjour");
    gotoxy(50,12);printf("Dans STUDENT HUB");
    getchar(); // Attendre une touche pour terminer
    system("cls"); // Effacer l'�cran
    printf("Veuillez vous connecter :\n");

    int tentatives = 0,i;
    char username[100];
    char password[100];
    char password_char;


    while (tentatives < MAX_ATTEMPTS) {
        gotoxy(40,10);printf("+---------------------------------------+\n");
        gotoxy(40,11);printf("|           Entrez vos identifiants     |\n");
        gotoxy(40,12);printf("+---------------------------------------+\n");
        gotoxy(40,13);printf("| Nom d'utilisateur :                   |");
        gotoxy(40,14);printf("| Mot de passe      :                   |");
        gotoxy(40,15);printf("+---------------------------------------+\n");
        gotoxy(64,13);scanf("%s", username);
        gotoxy(64,14);
		i= 0;
        while ((password_char = getch()) != '\r') { // '\r' correspond � la touche "Entr�e" sur Windows
			if (password_char == '\b' && i > 0) { // '\b' correspond � la touche "Retour arri�re" (backspace)
	            printf("\b \b"); // Efface le caract�re pr�c�dent de l'�cran
	            i--;
	            continue;
	        }
        password[i++] = password_char;
        printf("*"); // Affiche un ast�risque pour masquer le caract�re saisi
    	}
    	password[i] = '\0'; // Ajoutez le caract�re de fin de cha�ne � la fin du mot de passe
        getchar(); // Attendre une touche pour terminer
    	system("cls"); // Effacer l'�cran

        if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        	printf("\033[1;32m");
            gotoxy(40,10);printf("+---------------------------------------+\n");
            gotoxy(40,11);printf("|           Connexion reussie.          |\n");
            gotoxy(40,12);printf("+---------------------------------------+\n");
            gotoxy(40,13);printf("|              STUDENT HUB              |\n");
            gotoxy(40,14);printf("+---------------------------------------+\n");
            printf("\033[0m");
            getchar(); // Attendre une touche pour terminer
    		system("cls"); // Effacer l'�cran
            break;
        } else {
            tentatives++;
            printf("\033[1;31m"); 
            gotoxy(40,6);printf("+---------------------------------------+\n");
            gotoxy(40,7);printf("| Nom d'utilisateur ou mot de passe     |\n");
            gotoxy(40,8);printf("| incorrect. Tentatives restantes :  %d  |\n", MAX_ATTEMPTS - tentatives);
            gotoxy(40,9);printf("+---------------------------------------+\n");
            printf("\033[0m");
        }
    }

    if (tentatives < MAX_ATTEMPTS) {
        Etudiant* listeEtudiants = NULL;
        int numEtudiants = 0;
        menuPrincipal(&listeEtudiants, &numEtudiants);
        freeEtudiants(listeEtudiants, numEtudiants);
    } else {
        printf("\nNombre maximum de tentatives atteint. Le programme va se fermer.\n");
    }
    system("cls"); 
    gotoxy(55,10);printf("merci pour");
    gotoxy(50,12);printf(" visite STUDENT HUB");
    getchar(); 
    system("cls"); 
}
// ************************************************************-MAIN
int main() {
    lock();
    return 0;
}






