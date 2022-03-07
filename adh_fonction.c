#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "mylibrary.h"

//La variable de stocker les adherents informations
char fich_adh[20] = "file.txt";

// char titre_adh[30] = "GESTION DES ADHERENTS";
char titre[30] = "GESTION DES LIVRES PRETS";


// L'ID de l'adherent appartient à la plage des valeurs des variables moin et plus
int moin = 1000;
int plus = 1000000;

// prendre id
//Comment on va génnérer un nombre id unique:
//1. On genère un nombre
//2. On varifie si le nombre géneré existe ou pas dans le fichier
// 3. si ça existe on génère un nombre encore et on repète la même action jusqu'à ce que le nombre existe pas dans le fichier
int get_id(int id){
    srand(time(NULL));
    int choisi = 0; // cette variable determine si le nombre existe ou pas
    FILE *adh_fic = fopen(fich_adh, "r");
    adherent_t info;
    while(fread(&info, sizeof(adherent_t), 1, adh_fic)){
        if (info.adh_num == id){
            choisi = 1;
        }   
    }
    if (choisi == 0) {
        return id;
    }
    else{
        return get_id(rand() % (plus - moin + 1)) + moin;
    }
    
    fclose(adh_fic);
}

//fonction pour ajouter un adherent dans le fichier adh_info.
void ajout_adherent(){
    int nombre_de_livre;
    adherent_t info;
	FILE *adh_fic = fopen(fich_adh, "a+");
    srand(time(NULL));
	system("cls");
	printf("ENTREZ LES INFORMATIONS DE L'ADHERENT\n");
	printf("------------------------\n");
    info.adh_num = get_id(rand() % (plus - moin + 1)) + moin; // ID est géneré ici
	printf("ENTREZ LE NOM: ");
	scanf(" %24[^\n]", info.adh_nom);
	int return_de_postale;
    adresse_t adh_adresse;
    printf("ENTREZ LE CODE POSTAL: ");
	// cette partie du code verifie que le code postale est de type entier ou pas
	return_de_postale = scanf("%d", &info.adh_adresse.adr_cp);
    if(return_de_postale == 0){
		// ici la boucle aura affiche un message erreur et donnes une occasion à utilisateur de changer la donnée entrée
            // Tanque il entre un type de donnée qui n'est entier
		while (return_de_postale == 0){
			printf("ERREUR DE SAISIE\n");
			printf("ENTRER LE CODE POSTAL: ");
			scanf("%*[^\n]");
			return_de_postale = scanf("%d", &info.adh_adresse.adr_cp);
		}
	}
    printf("ENTREz LE NOM DE LA VILLE: ");
    scanf(" %24[^\n]", info.adh_adresse.adr_ville);
    printf("ENTREZ LE NOM DE LA RUE: ");
    scanf(" %24[^\n]", info.adh_adresse.adr_rue);
	info.adh_nb_emprunts = 0;
    fwrite(&info, sizeof(adherent_t), 1, adh_fic); // cette ligne du code ecrit les information des adhérents entrées dans dans le fichier 
	fclose(adh_fic);
	printf("\nINFORMATION A ETE BIEN AJOUTE, VOICI LES DETAILS:\n");
	printf("ID: %d\n", info.adh_num);
	printf("NOM: %s\n", info.adh_nom);
	printf("ADDRESSE: %d, %s, %s\n", info.adh_adresse.adr_cp,info.adh_adresse.adr_rue,info.adh_adresse.adr_ville);
}

//getting total number of record
int totalRecord(){
	adherent_t info;
	FILE *adh_fic = fopen(fich_adh, "r");
	fseek(adh_fic, 0, SEEK_END);
	int reNO = ftell(adh_fic)/sizeof(info);
	fclose(adh_fic);
	return reNO;
}

//fonction de modifier le record
// DETAIL DE CETTE FONCTION:
// 1. ON UTILISE DEUX FICHIERS, NOTRE FICHIER QUI STOCKE LES FORMATIONS DE TOUS LES AHDERENTS ET UN FICHIER TEMPORAIRE
// D' DBORD ON OUVRE NOTRE FICHIER DE TOUS LES INFORMATION DES ADHERENTS DANS UN MODE LIRE ET LE FICHIER TEMPORAIRE DANS LE MODE ECRIRE
//  ON PREND L'ID DU LIVRE ET LA COMPARER AVEC TOUS LES IDS DES ADHERENTS DANS LE FICHIER PRINCIPAL DES ADHERENTS
// SI ON TROUVE CET ID ON PREND NIVEAUX INFORMATION DE L'ADHERENT ET  ON ECRIT  TOUS LES INFORMATIONS DANS LE FICHIER PRINCIPAL DANS LE FICHIER TEMPORAIRE
// MAINTENANT ON POSE LA CONDITION QUE SI ON TROUVE L'ID, ON MET NOTRE FICHIER PRINCIPAL DANS LE MODE D'ECRIRE ET LE TEMPORAIRE DANS LE MONDE LIRE
// ON PREND TOUS LES INFORMATION EN FICHIER TEMPORAIRE DANS NOTRE FICHIER PRINCIPAL 
void modif_adherent(){
	adherent_t info;
	FILE *adh_fic = fopen(fich_adh, "r");
	FILE *temp = fopen("temp.txt", "w"); //un fichier temporaire
	int found = 0; //ce variable determine si id existe dans le fichier ou non, le valeur 1 present que ça existe et 0 est le contraire
	int id, nombre_de_livre;
	system("cls");
	printf("MODIFICATION DES ADHERENTS\n");
	printf("-------------------------------\n\n");
	printf("ENTREZ L'IDENTIFIANT DE L'ADHERENT: ");
	if(scanf("%d", &id) == 1){
		while(fread(&info, sizeof(adherent_t), 1, adh_fic)){
            /*
               En lisant le fichier si le id existe on modifie toutes les information sans le id 
             */
			if(info.adh_num == id){
				found = 1; 
                info.adh_num = info.adh_num;
				 info.adh_nb_emprunts = info.adh_nb_emprunts;
				printf("ENTREZ LE NOM: ");
                scanf(" %24[^\n]", info.adh_nom);
                adresse_t adh_adresse;
                printf("ENTREZ LE CODE POSTALE: ");
                scanf("%d", &info.adh_adresse.adr_cp);
                printf("ENTREZ LE NOM DE LA VILLE: ");
                scanf(" %24[^\n]", info.adh_adresse.adr_ville);
                printf("ENTREZ LE NOM DE LA RUE: ");
                scanf(" %24[^\n]", info.adh_adresse.adr_rue); 
			}
			fwrite(&info, sizeof(adherent_t), 1, temp);
		}
		//the code below read data from the temp file and write it in the info file
		fclose(adh_fic);
		fclose(temp);

		if(found){
			temp = fopen("temp.txt", "r");
			adh_fic = fopen(fich_adh, "w");
			while(fread(&info, sizeof(adherent_t), 1, temp)){
				fwrite(&info, sizeof(adherent_t), 1, adh_fic);
			}
		}
		else{
			printf("\nID EST INDISPONIBLE\n");
		}
		fclose(temp);
		fclose(adh_fic);
	}
}

//Cette fonction affiche toutes les informations dans le fichier
void liste_adherents(){
	adherent_t *s, info;
	int i;
	int nombre_de_record = totalRecord();
	s = (adherent_t*) calloc(nombre_de_record, sizeof(adherent_t));
	FILE *adh_fic = fopen(fich_adh, "r");
	s = (adherent_t*) calloc(nombre_de_record, sizeof(adherent_t));
	printf("%-15s%-15s%-15s%-15s%-20s%-15s\n","IDENTIFICATION","NOM","CODE POSTAL","VILLE","RUE","LIVRES");
	printf("----------     ---------     ----------      ----          ------------    --------\n");
	for ( i = 0; i < nombre_de_record; i++){
		fread(&s[i], sizeof(adherent_t), 1, adh_fic);
	}
	for ( i = 0; i < nombre_de_record; i++){
		for (int j = 0; j < (i + 1); j++){
			if(strcmp(s[i].adh_nom, s[j].adh_nom) < 0){
				info = s[i];
				s[i] = s[j];
				s[j] = info;
			}
		}
	}
	for ( i = 0; i < nombre_de_record; i++){
		printf("%-15d%-15s%-15d%-15s%-20s%-15d\n", s[i].adh_num, s[i].adh_nom, s[i].adh_adresse.adr_cp, s[i].adh_adresse.adr_ville, s[i].adh_adresse.adr_rue, s[i].adh_nb_emprunts);
	}
	fclose(adh_fic);
}

// Cette fonction permet de supprimer un record
// DETAIL DE CETTE FONCTION:
// 1. ON UTILISE DEUX FICHIERS, NOTRE FICHIER QUI STOCKE LES FORMATIONS DE TOUS LES ADHERENTS ET UN FICHIER TEMPORAIRE
// D' DBORD ON OUVRE NOTRE FICHIER DE TOUS LES INFORMATION DE LIVRES DANS UN MODE LIRE ET LE FICHIER TEMPORAIRE DANS LE MODE ECRIRE
//  ON PREND L'ID DU LIVRE ET LA COMPARER AVEC TOUS LES IDS DES ADHERENTS DANS LE FICHIER PRINCIPAL DES LIVRES
// SI ON TROUVE CET ID ON ECRIT TOUS LES INFORMATIONS DANS LE FICHIER PRINCIPAL DANS LE FICHIER TEMPORAIRE SAUF TOUS LES INFORMATION DE L'ID TROUVE
// MAINTENANT ON POSE LA CONDITION QUE SI ON TROUVE L'ID, ON MET NOTRE FICHIER PRINCIPAL DANS LE MODE D'ECRIRE ET LE TEMPORAIRE DANS LE MONDE LIRE
// ON PREND TOUS LES INFORMATION EN FICHIER TEMPORAIRE DANS NOTRE FICHIER PRINCIPAL 
void supprime_adherent(){
	adherent_t info;
	FILE *adh_fic = fopen(fich_adh, "r");
	FILE *temp = fopen("temp.txt", "w");
	int found = 0; //ce variable determine si id existe dans le fichier ou non, le valeur 1 present que ça existe et 0 est le contraire
	int id_à_suprime, nombre_de_livre;
	system("cls");
	printf("SUPPRESSION D'UN ADHERENT\n");
	printf("-------------------------------\n\n");
	printf("ENTREZ ID DE L'ADHERENT: ");
	scanf("%d", &id_à_suprime);
	while(fread(&info, sizeof(adherent_t), 1, adh_fic)){
		if(info.adh_num == id_à_suprime){ 
			found = 1;
		}
		else{
			fwrite(&info, sizeof(adherent_t), 1, temp);
		}
	}
	fclose(adh_fic);
	fclose(temp);

	if(found){ //when the record is found 
		temp = fopen("temp.txt", "r");
		adh_fic = fopen(fich_adh, "w+");
		while(fread(&info, sizeof(adherent_t), 1, temp)){
			fwrite(&info, sizeof(adherent_t), 1, adh_fic);
		}
		printf("L'ADHERENT A ETE SUPPRIME\n");
		fclose(adh_fic);
		fclose(temp);
	}
	else{
		printf(" CET ADHERENT N'EST PAS DANS LA BASE DE DONNEE!");
	}
	fclose(temp);
	fclose(adh_fic);

}

// Cette fonction permet de chercher dans le fichier info_adh
void recherche_adherent(){
	adherent_t info;
	FILE *adh_fic = fopen(fich_adh, "r");
	int found = 0;
	int search_id;
	printf("RECHERCHER UN ADHERENT\n");
	printf("-------------------------------\n\n");
	
	printf("ENTREZ LE ID DE L'ADHERENT: ");
	scanf("%d", &search_id);
	while(fread(&info, sizeof(adherent_t), 1, adh_fic)){
		if(info.adh_num == search_id){
			found = 1;
			printf("%-15s%-15s%-15s%-15s%-20s%-15s\n","IDENTIFICATION","NOM","CODE POSTAL","VILLE","RUE","LIVRES");
			printf("----------     ---------     ----------      ----          ------------    --------\n");
			printf("%-15d%-15s%-15d%-15s%-20s%-15d\n", info.adh_num, info.adh_nom, info.adh_adresse.adr_cp, info.adh_adresse.adr_ville, info.adh_adresse.adr_rue, info.adh_nb_emprunts);
		}
	}
	if(info.adh_num != search_id){
		printf("CET ADHERENT N'EST PAS DANS LA BASE DE DONNEES! VERIFIEZ L'ID\n");
	}
	fclose(adh_fic);
}

// Cette fonction gere la gestion des adherent
void gestion_adhr(){
    int choix_1, readChoix_1;
	char adh_titre[25] = "GESTION DES ADHERENTS";
	titre_projet(adh_titre);
    do{
		printf("NOMBRE DES ADHERENTS: %d\n", totalRecord());
        printf("\n\n1. AJOUTER UN ADHERENT\n");
        printf("2. MODIFIER UN ADHERENT\n");
        printf("3. SUPPRIMER UN ADHERENT\n");
        printf("4. AFFICHIER LES LISTE \n");
        printf("5. RECHERCHER\n");
        printf("6. RETOUR MENU PRINCIPAL\n");

        printf("ENTREZ VOTRE CHOIX: ");
        readChoix_1 = scanf("%d", &choix_1);

        if(readChoix_1 == 0){
            while (readChoix_1 == 0){
                printf("ENTREZ UN NOMBRE S'IL VOUS PLAIT: ");
                scanf("%*[^\n]");
                readChoix_1 = scanf("%d", &choix_1);
            }
        }
        if (readChoix_1 == 1){
            if(choix_1 != 1 && choix_1 != 2 && choix_1 != 3 && choix_1 != 4 && choix_1 != 5 && choix_1 != 6){
				printf("VOTRE CHOIX NE FAIT PAS PARTI DES OPTIONS.\n");
			}
            else{
                switch (choix_1){
                case 1:
                    ajout_adherent();
                    break;
                case 2:
                    modif_adherent();
                    break;
                case 3:
                    supprime_adherent();
                    break;
                case 4:
					system("cls");
                    liste_adherents();
                    break;
                case 5:
                    recherche_adherent();
                    break;
                
                default:
					system("cls");
					titre_projet(titre);
                    break;
                }
            }
        
        }

    } while (choix_1 != 6);
}