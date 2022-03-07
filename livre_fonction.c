#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "mylibrary.h"

// la declaration du nom de fichier qui stocke toutes les informations de les livres
char fich_livres[20] = "fich_livres.txt";

// Cette fonction gere la gestion des livre
// La range de livre num
int lower_range = 1000000;
int higher_range = 100000000;

//Comment on va génnérer un nombre unique pour des livres:
//1. On genère un nombre
//2. On varifie si le nombre géneré existe ou pas dans le fichier
// 3. si ça existe on génère un nombre encore et on repète la même action jusqu'à ce que le nombre existe pas dans le fichier
int livre_id(int id){
    srand(time(NULL));
    int choisi = 0;
    FILE *livre_fic = fopen(fich_livres, "r");
    livre_t info;
    while(fread(&info, sizeof(livre_t), 1, livre_fic)){
        if (info.liv_num == id){
            choisi = 1;
        }   
    }
    if (choisi == 0) {
        return id;
    }
    else{
        return livre_id(rand() % (higher_range - lower_range + 1)) + lower_range;
    }
    
    fclose(livre_fic);
}

//ajouter de livre
void ajout_livre(){
    int nombre_de_livre;
	livre_t data;
	int found = 0;
	// FILE *liv_emp = fopen("adh.txt.txt", "r");
	FILE *livre_fic = fopen(fich_livres, "a+"); //pl represent point livre
	system("cls");
	printf("ENTREZ LES INFORMATIONS \n");
	printf("-------------------------------\n\n");
    srand(time(NULL));
    data.liv_num = livre_id(rand() % (higher_range - lower_range + 1)) + lower_range;
	printf(" ENTREZ LE TITRE DU LIVRE: ");
	scanf(" %24[^\n]", data.liv_titre);
    liv_auteur auteur_info;
    printf(" ENTREZ LE NOM DE L'AUTEUR: ");
    scanf("%s", data.auteur_info.nom);
    printf(" ENTREZ LE PRENOM DE L'AUTEUR: ");
    scanf(" %24[^\n]", data.auteur_info.prenom);
    data.liv_emprunteur = 0;
	fwrite(&data, sizeof(livre_t), 1, livre_fic);
	fclose(livre_fic);
	printf("\nLE LIVRE A ETE ENREGISTRE AVEC L'ID SUIVANT: %d\n", data.liv_num);
}
// number of record
int total_livre(){
	livre_t data;
	FILE *livre_fic = fopen(fich_livres, "r");
	fseek(livre_fic, 0, SEEK_END);
	int reNO = ftell(livre_fic)/sizeof(data);
	fclose(livre_fic);
	return reNO;
}

// liste de livre ou affichier de livre

void liste_livres(){
	livre_t *s, data;
	int i;
	int nombre_de_record = total_livre();
	s = (livre_t*) calloc(nombre_de_record, sizeof(livre_t));
	FILE *livre_fic = fopen(fich_livres, "r");
	system("cls");
	printf("%-15s%-15s%-15s%-15s%-15s\n","ID DE LIVRE","TITRE","NOM AUTEUR","PRENOM AUTEUR", "NUMERO EMPRUNTEUR");
	printf("%-15s%-15s%-15s%-15s%-15s","----------","---------","----------","--------------", "----------------\n");
	for ( i = 0; i < nombre_de_record; i++){
		fread(&s[i], sizeof(livre_t), 1, livre_fic);
	}
	// SORTING
	for ( i = 0; i < nombre_de_record; i++){
		for (int j = 0; j < (i + 1); j++){
			if(strcmp(s[i].liv_titre, s[j].liv_titre) < 0){
				data = s[i];
				s[i] = s[j];
				s[j] = data;
			}
		}
	}
	// AFFICHIER LES INFORMATION SORTE
	for ( i = 0; i < nombre_de_record; i++){
		printf("%-15d%-15s%-15s%-15s%-15d\n", s[i].liv_num, s[i].liv_titre, s[i].auteur_info.nom, s[i].auteur_info.prenom, s[i].liv_emprunteur);
	}
	fclose(livre_fic);
}

//Modification de livre
// DETAIL DE CETTE FONCTION:
// 1. ON UTILISE DEUX FICHIERS, NOTRE FICHIER QUI STOCKE LES FORMATIONS DE TOUS LES LIVRES ET UN FICHIER TEMPORAIRE
// D' DBORD ON OUVRE NOTRE FICHIER DE TOUS LES INFORMATION DE LIVRES DANS UN MODE LIRE ET LE FICHIER TEMPORAIRE DANS LE MODE ECRIRE
//  ON PREND L'ID DU LIVRE ET LA COMPARER AVEC TOUS LES IDS DE LIVRES DANS LE FICHIER PRINCIPAL DES LIVRES
// SI ON TROUVE CET ID ON PREND NIVEAUX INFORMATION DU LIVRE ET  ON ECRIT  TOUS LES INFORMATIONS DANS LE FICHIER PRINCIPAL DANS LE FICHIER TEMPORAIRE
// MAINTENANT ON POSE LA CONDITION QUE SI ON TROUVE L'ID, ON MET NOTRE FICHIER PRINCIPAL DANS LE MODE D'ECRIRE ET LE TEMPORAIRE DANS LE MONDE LIRE
// ON PREND TOUS LES INFORMATION EN FICHIER TEMPORAIRE DANS NOTRE FICHIER PRINCIPAL 
void modif_livre(){
	system("cls");
	printf("MODIFIER L'INFORMATION CONCERNANT LE LIVRE\n--------------------------------------------\n\n");
	livre_t data;
	FILE *livre_fic = fopen(fich_livres, "r");
	FILE *livre_temp = fopen("temp.txt", "w");
	int found = 0; //ce variable determine si id existe dans le fichier ou non, le valeur 1 present que ça existe et 0 est le contraire
	int modifier_id, retourne;
	printf("ENTREZ L'ID DU LIVRE A MODIFIER: ");
	retourne = scanf("%d", &modifier_id);
	if(retourne == 1){
		while(fread(&data, sizeof(livre_t), 1, livre_fic)){
			if(data.liv_num == modifier_id){
				found = 1; // CA SIGNIFIE QUE ID IS DISPONIBLE

				// LES CODES SUIVANT PERMETTENT D'ENTRER LES NIVEAUX INFORMATION QUE ON VEUX MODIFIER
                data.liv_num = data.liv_num;
				printf("ENTREZ LE NOUVEAU NOM DU LIVRE: ");
                scanf(" %24[^\n]", data.liv_titre);
            
                liv_auteur auteur_info;
                printf("ENTREZ LE NOUVEAU NOM DE L'AUTEUR: ");
                scanf(" %24[^\n]", &data.auteur_info.nom);
                printf("ENTREZ LE NOUVEAU PRENOM DE L'AUTEUR: ");
                scanf(" %24[^\n]", data.auteur_info.prenom);
				data.liv_emprunteur = data.liv_emprunteur;
                scanf("%d", &data.liv_emprunteur);
			}
			fwrite(&data, sizeof(livre_t), 1, livre_temp);
		}
		//the code below read data from the temp file and write it in the info file
		fclose(livre_fic);
		fclose(livre_temp);

		if(found){
			livre_temp = fopen("temp.txt", "r");
			livre_fic = fopen(fich_livres, "w");
			while(fread(&data, sizeof(livre_t), 1, livre_temp)){
				fwrite(&data, sizeof(livre_t), 1, livre_fic);
			}
			fclose(livre_fic);
			fclose(livre_temp);
		}
		else{
			printf("\nL'ID RECHERCHE EST INEXISTANT\n");
		}
	}
	if (retourne == 0){
		// Dans le cas ou l'utilisateur entres qui n'est pas de type entier
		// on affiche message d'erreur et le demande de mettre le choix encore
		printf("ERREUR DE SAISIE!!!\n");
                printf("RE-ENTREZ VOTRE CHOIX: ");
                scanf("%*[^\n]");
                retourne = scanf("%d", &modifier_id);
	}
}

// Cette fonction permet de supprimer un record
// DETAIL DE CETTE FONCTION:
// 1. ON UTILISE DEUX FICHIERS, NOTRE FICHIER QUI STOCKE LES FORMATIONS DE TOUS LES LIVRES ET UN FICHIER TEMPORAIRE
// D' DBORD ON OUVRE NOTRE FICHIER DE TOUS LES INFORMATION DE LIVRES DANS UN MODE LIRE ET LE FICHIER TEMPORAIRE DANS LE MODE ECRIRE
//  ON PREND L'ID DU LIVRE ET LA COMPARER AVEC TOUS LES IDS DE LIVRES DANS LE FICHIER PRINCIPAL DES LIVRES
// SI ON TROUVE CET ID ON ECRIT TOUS LES INFORMATIONS DANS LE FICHIER PRINCIPAL DANS LE FICHIER TEMPORAIRE SAUF TOUS LES INFORMATION DE L'ID TROUVE
// MAINTENANT ON POSE LA CONDITION QUE SI ON TROUVE L'ID, ON MET NOTRE FICHIER PRINCIPAL DANS LE MODE D'ECRIRE ET LE TEMPORAIRE DANS LE MONDE LIRE
// ON PREND TOUS LES INFORMATION EN FICHIER TEMPORAIRE DANS NOTRE FICHIER PRINCIPAL 
void supprime_livre(){
	system("cls");
	printf("SUPPRIMER UNE INFORMATION\n");
	printf("-------------------------------\n\n");
	livre_t data;
	FILE *livre_fic = fopen(fich_livres, "r");
	FILE *livre_temp = fopen("temp.txt", "w");
	int found = 0; //ce variable determine si id existe dans le fichier ou non, le valeur 1 present que ça existe et 0 est le contraire
	int suprime;
	printf("ENTREZ L'ID DU LIVRE A SUPPRIMER: ");
	scanf("%d", &suprime);
	while(fread(&data, sizeof(livre_t), 1, livre_fic)){
		if(data.liv_num == suprime){ 
			found = 1; // CA SIGNIFIE QUE L'ID DU LIVRE DANS NOTRE BASE DE DONNEE
		}
		else{
			fwrite(&data, sizeof(livre_t), 1, livre_temp);
		}
	}
	fclose(livre_fic);
	fclose(livre_temp);

	if(found){ //when the record is found 
		livre_temp = fopen("temp.txt", "r");
		livre_fic = fopen(fich_livres, "w+");
		while(fread(&data, sizeof(livre_t), 1, livre_temp)){
			fwrite(&data, sizeof(livre_t), 1, livre_fic);
		}
		printf(" LE LIVRE A ETE SUPPRIME AVEC SUCCES\n");
		fclose(livre_fic);
		fclose(livre_temp);
	}
	else{
		// LORSQUE ID N'EST PAS DANS TROUVE ON AFFICHE LE MESSAGE SUIVANT
		printf(" LE LIVRE N'EST PAS DANS LA BASE DE DONNEES!");
	}

}

// Cette fonction permet de chercher dans le fichier info_adh
// D' DBORD ON OUVRE NOTRE FICHIER DE TOUS LES INFORMATION DE LIVRES(FICHIER PRINCIPAL) DANS UN MODE LIRE
// ON LIT LES INFORMATION ET LES COMPARES AVEC LE TITRE MET PAR UTILISATEUR
// SI ON TROUVE CET TITRE DE LIVRE ON AFFICHE TOUS LES INFORMATIONS CORRESPONDANT DE CET ID DANS LE FICHIER PRINCIPAL DANS LE FICHIER TEMPORAIRE SAUF TOUS LES INFORMATION DE L'ID TROUVE
void recherche_livre(){
	livre_t data;
    int resultat;
	FILE *livre_fic = fopen(fich_livres, "r");
	int found = 0;
	char titre_rechercher[20];
	system("cls");
	printf("RECHERCHER LE LIVRE DANS LA BASE DE DONNEES\n");
	printf("-------------------------------\n\n");
	printf("ENTREZ LE TITRE DU LIVRE A RECHERCHER: ");
	scanf(" %19[^\n]", titre_rechercher);
	while(fread(&data, sizeof(livre_t), 1, livre_fic)){
        resultat = strcmp(titre_rechercher, data.liv_titre);
		if(resultat == 0){
			found = 1;
			printf("%-15s%-15s%-15s%-15s%-15s\n","ID DE LIVRE","TITRE","NOM AUTEUR","PRENOM AUTEUR", "NUMERO EMPRUNTEUR");
	        printf("----------     ---------     ----------      ---------\n");
			printf("%-15d%-15s%-15s%-15s%-15d\n", data.liv_num, data.liv_titre, data.auteur_info.nom, data.auteur_info.prenom, data.liv_emprunteur);
		}
	}
	if(resultat != 0){
		printf("CE LIVRE EST INDISPONIBLE\n");
	}
	fclose(livre_fic);
}

// fonction pour gestion des livres
void gestion_livres(){
	char livres_titre[25] = "GESTION DES LIVRES";
	titre_projet(livres_titre);
    int choix_1, readChoix_1;
    do{
        printf("\n\n1. AJOUTER UN LIVRE\n");
        printf("2. MODIFIER UN LIVRE\n");
        printf("3. SUPPRIMER UN LIVRE\n");
        printf("4. AFFICHER LA LISTE DES LIVRES PAR ORDRE ALPHABETIQUE\n");
        printf("5. RECHERCHER LE TITRE D'UN LIVRE ET AFFICHER LES INFORMATIONS CORRESPONDANTES\n");
        printf("6. RETOUR AU MENU PRINCIPAL\n");

        printf("ENTREZ VOTRE CHOIX: ");
        readChoix_1 = scanf("%d", &choix_1);

        if(readChoix_1 == 0){
            while (readChoix_1 == 0){
                printf(" ERREUR DE SAISIE. VEUILLEZ ENTRER UN NOMBRE: ");
                scanf("%*[^\n]");
                readChoix_1 = scanf("%d", &choix_1);
            }
        }
        if (readChoix_1 == 1){
            if(choix_1 != 1 && choix_1 != 2 && choix_1 != 3 && choix_1 != 4 && choix_1 != 5 && choix_1 != 6){
				printf(" VOTRE CHOIX NE FAIT PAS PARTI DES OPTIONS.\n");
			}
            switch (choix_1)
            {
            case 1:
                ajout_livre();
                break;
			case 2:
				modif_livre();
				break;
            case 3:
                supprime_livre();
                break;
            case 4:
                liste_livres();
                break;
            case 5:
                recherche_livre();
                break;
            default:
				system("cls");
				char titre[30] = "GESTION DES LIVRES PRETS";
				titre_projet(titre);
                break;
            }
        }

    } while (choix_1 != 6);
}
