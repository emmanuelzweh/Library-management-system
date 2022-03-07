#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "mylibrary.h"


//Cette fonction gere la gestion des emprunts
void print(){
    printf("Hello world\n");
}
// emprunter de livres
// CETTE FONCTION C'EST VRAIMMENT COMME LA MODIFICATIONS DES INFORMATION EN NOTRE DEUX FICHIERS PRINCIPAL(LE FICHIER DES LIVRES ET ADHERENTS)
// NORMALEMENT DANS CE PROJET LA MODIFICATION DES INFORMATIONS DANS UN FICHIER ON UTILISE DEUX FICHIER LE FICHIER PRINCIPAL ET TEMPORAIRE
// DONC ON VAS UTLILISER 4 FICHIERS CHAQUE FICHIER PRINCIPAL A SON FICHIER TEMPORAIRE
// VOICI COMMENT CA MARCHE:
// 1. POUR LE LIVRE
// 1. ON UTILISE DEUX FICHIERS, NOTRE FICHIER QUI STOCKE LES FORMATIONS DE TOUS LES LIVRES ET UN FICHIER TEMPORAIRE
// D' DBORD ON OUVRE NOTRE FICHIER DE TOUS LES INFORMATION DE LIVRES DANS UN MODE LIRE ET LE FICHIER TEMPORAIRE DANS LE MODE ECRIRE
//  ON PREND L'ID DU LIVRE ET LA COMPARER AVEC TOUS LES IDS DE LIVRES DANS LE FICHIER PRINCIPAL DES LIVRES
// SI ON TROUVE CET ID ON GARDE TOUS LES INFORMATIONS ET PRENDS L'ID DE L'ADHERENT ET  ON ECRIT  TOUS LES INFORMATIONS DANS LE FICHIER PRINCIPAL DANS LE FICHIER TEMPORAIRE
// MAINTENANT ON POSE LA CONDITION QUE SI ON TROUVE L'ID, ON MET NOTRE FICHIER PRINCIPAL DANS LE MODE D'ECRIRE ET LE TEMPORAIRE DANS LE MONDE LIRE
// ON PREND TOUS LES INFORMATION EN FICHIER TEMPORAIRE DANS NOTRE FICHIER PRINCIPAL 

// LA MEME COMMENT A HAUT S'APPLIQUE POUR LE ADHERENT MAIS POUR LUI C'EST COMME QUAND ON VARIFIE QUE L'ADHERENT PREND LIVRE ON MODIFIE adh_nb_emprunts EN AJOUTANT 1

void emprunter_livres(){
    system("cls");
    printf("ENTREZ LES INFORMATIONS POUR EMPRUNTER UN LIVRE\n--------------------------------------------\n\n");
    adherent_t info;
    livre_t data;
    int found = 0;
    int id_is_found = 0;
    FILE *temp_1 = fopen("temp1.txt", "w");
    FILE *temp = fopen("temp.txt", "w");
    FILE *livre = fopen("fich_livres.txt", "r");
    FILE *emprunte = fopen("emprunt_livres.txt",  "w");
    FILE *adh_fichier = fopen("file.txt", "r");
    int retoure;
    //prendre les information pour emprunter un livre
    emprunt_t prend_liv;
    
    printf("ENTREZ L'IDENTITFIANT DU LIVRE EMPRUNTE: ");
    if(scanf("%d", &prend_liv.livre_id) == 1){
        while (fread(&data, sizeof(livre_t), 1, livre)){
            if(prend_liv.livre_id == data.liv_num){
                found = 1;
                printf("ENTREZ L'IDENTIFIANT DE L'ADHERENT: ");
                retoure = scanf("%d", &prend_liv.adh_id);
                data.liv_num = data.liv_num;
                data.liv_emprunteur = prend_liv.adh_id;
                strcpy(data.auteur_info.nom, data.auteur_info.nom);
                strcpy(data.auteur_info.prenom, data.auteur_info.prenom);
                strcpy(data.liv_titre, data.liv_titre);  
            }
            fwrite(&data, sizeof(livre_t), 1, temp_1);
        }
        fclose(livre);
        fclose(temp_1);
        if (found){
            if(retoure == 1){
                while (fread(&info, sizeof(adherent_t), 1, adh_fichier)){
                    if (prend_liv.adh_id == info.adh_num)
                    {
                        //adherent
                        id_is_found = 1;
                        info.adh_num = info.adh_num;
                        strcpy(info.adh_nom, info.adh_nom);
                        info.adh_adresse.adr_cp = info.adh_adresse.adr_cp;
                        strcpy(info.adh_adresse.adr_rue, info.adh_adresse.adr_rue);
                        strcpy(info.adh_adresse.adr_ville, info.adh_adresse.adr_ville);
                        info.adh_nb_emprunts = info.adh_nb_emprunts + 1;
                        fwrite(&prend_liv, sizeof(emprunt_t), 1, emprunte);
                        fclose(emprunte);
                    }
                    fwrite(&info, sizeof(adherent_t), 1, temp);
                }
                fclose(adh_fichier);
                fclose(temp);
                if (id_is_found){
                    temp = fopen("temp.txt", "r");
                    adh_fichier = fopen("file.txt", "w");
                    while(fread(&info, sizeof(adherent_t), 1, temp)){
                        fwrite(&info, sizeof(adherent_t), 1, adh_fichier);
                    }
                }
                fclose(temp);
                fclose(adh_fichier);
                fclose(temp_1);
                fclose(livre);
            }
        }
        if (found && id_is_found){
            livre = fopen("fich_livres.txt", "w");
            temp_1 = fopen("temp1.txt", "r");
            while (fread(&data, sizeof(livre_t), 1, temp_1)){
                fwrite(&data, sizeof(livre_t), 1, livre);
            }
            printf("LE LIVRE A BIEN ETE EMPRUNTE\n"); 
        }
        fclose(temp_1);
        fclose(livre);   
    }
}

// Rendre un livre
//--------------------------------------------------------------------------------------------------
// CETTE FONCTION C'EST VRAIMMENT COMME LA MODIFICATIONS DES INFORMATION EN NOTRE DEUX FICHIERS PRINCIPAL(LE FICHIER DES LIVRES ET ADHERENTS)
// NORMALEMENT DANS CE PROJET LA MODIFICATION DES INFORMATIONS DANS UN FICHIER ON UTILISE DEUX FICHIER LE FICHIER PRINCIPAL ET TEMPORAIRE
// DONC ON VAS UTLILISER 4 FICHIERS CHAQUE FICHIER PRINCIPAL A SON FICHIER TEMPORAIRE
// VOICI COMMENT CA MARCHE:
// 1. POUR LE LIVRE
// 1. ON UTILISE DEUX FICHIERS, NOTRE FICHIER QUI STOCKE LES FORMATIONS DE TOUS LES LIVRES ET UN FICHIER TEMPORAIRE
// D' DBORD ON OUVRE NOTRE FICHIER DE TOUS LES INFORMATION DE LIVRES DANS UN MODE LIRE ET LE FICHIER TEMPORAIRE DANS LE MODE ECRIRE
//  ON PREND L'ID DU LIVRE ET LA COMPARER AVEC TOUS LES IDS DE LIVRES DANS LE FICHIER PRINCIPAL DES LIVRES
// SI ON TROUVE CET ID ON GARDE TOUS LES INFORMATIONS ET PRENDS L'ID DE L'ADHERENT ET  ON ECRIT  TOUS LES INFORMATIONS DANS LE FICHIER PRINCIPAL DANS LE FICHIER TEMPORAIRE
// MAINTENANT ON POSE LA CONDITION QUE SI ON TROUVE L'ID, ON MET NOTRE FICHIER PRINCIPAL DANS LE MODE D'ECRIRE ET LE TEMPORAIRE DANS LE MONDE LIRE
// ON PREND TOUS LES INFORMATION EN FICHIER TEMPORAIRE DANS NOTRE FICHIER PRINCIPAL 

// LA MEME COMMENT A HAUT S'APPLIQUE POUR LE ADHERENT MAIS POUR LUI C'EST COMME QUAND ON VARIFIE QUE L'ADHERENT PREND LIVRE ON MODIFIE adh_nb_emprunts EN AJOUTANT -1
void rendre_livres(){
    system("cls");
    printf("ENTREZ LES INFORMATIONS POUR RENDRE UN LIVRE\n--------------------------------------------\n\n");
    adherent_t info;
    livre_t data;
    int found = 0;
    int id_is_found = 0;
    FILE *temp_1 = fopen("temp1.txt", "w");
    FILE *temp = fopen("temp.txt", "w");
    FILE *livre = fopen("fich_livres.txt", "r");
    FILE *emprunte = fopen("emprunt_livres.txt",  "w");
    FILE *adh_fichier = fopen("file.txt", "r");
    int retoure;
    //prendre les information pour emprunter un livre
    emprunt_t prend_liv;
    
    printf("ENTREZ L'IDENTIFIANT DU LIVRE: ");
    if(scanf("%d", &prend_liv.livre_id) == 1){
        while (fread(&data, sizeof(livre_t), 1, livre)){
            if(prend_liv.livre_id == data.liv_num){
                found = 1;
                printf("ENTREZ L'IDENTIFIANT DE L'ADHERENT: ");
                retoure = scanf("%d", &prend_liv.adh_id);
                data.liv_num = data.liv_num;
                data.liv_emprunteur = 0;
                strcpy(data.auteur_info.nom, data.auteur_info.nom);
                strcpy(data.auteur_info.prenom, data.auteur_info.prenom);
                strcpy(data.liv_titre, data.liv_titre);  
            }
            fwrite(&data, sizeof(livre_t), 1, temp_1);
        }
        fclose(livre);
        fclose(temp_1);
        if (found){
            if(retoure == 1){
                while (fread(&info, sizeof(adherent_t), 1, adh_fichier)){
                    if (prend_liv.adh_id == info.adh_num){
                        //adherent
                        id_is_found = 1;
                        info.adh_num = info.adh_num;
                        strcpy(info.adh_nom, info.adh_nom);
                        info.adh_adresse.adr_cp = info.adh_adresse.adr_cp;
                        strcpy(info.adh_adresse.adr_rue, info.adh_adresse.adr_rue);
                        strcpy(info.adh_adresse.adr_ville, info.adh_adresse.adr_ville);
                        info.adh_nb_emprunts = info.adh_nb_emprunts - 1;
                        fwrite(&prend_liv, sizeof(emprunt_t), 1, emprunte);
                        fclose(emprunte);
                    }
                    fwrite(&info, sizeof(adherent_t), 1, temp);
                }
                fclose(adh_fichier);
                fclose(temp);
                if (id_is_found){
                    temp = fopen("temp.txt", "r");
                    adh_fichier = fopen("file.txt", "w");
                    while(fread(&info, sizeof(adherent_t), 1, temp)){
                        fwrite(&info, sizeof(adherent_t), 1, adh_fichier);
                    }
                }
                fclose(temp);
                fclose(adh_fichier);
                fclose(temp_1);
                fclose(livre);
            }
        }
        if (!found){
            printf("LE LIVRE EST INDISPONIBLE");
        }
        
        if (found && id_is_found){
            livre = fopen("fich_livres.txt", "w");
            temp_1 = fopen("temp1.txt", "r");
            while (fread(&data, sizeof(livre_t), 1, temp_1)){
                fwrite(&data, sizeof(livre_t), 1, livre);
            } 
            printf("BRAVO! LE LIVRE A BIEN ETE EMPRUNTE\n");
        }
        fclose(temp_1);
        fclose(livre);   
    }
}

//listes des livres emprunte
void liste_emprunts(){
    system("cls");
    emprunt_t prend_liv;
    livre_t data;
    FILE *livre = fopen("fich_livres.txt", "r");
    titre_projet("LES LIVRES EMPRUNTES");
    printf("%15s%15s\n", "Nom", "ID");
    printf("%15s%15s\n\n","----------","----------");
    while (fread(&data, sizeof(livre_t), 1, livre)){
        if (data.liv_emprunteur != 0){
            printf("%15s%15d\n", data.liv_titre, data.liv_num);
        }  
    }
    fclose(livre);
}
// liste des emprunteurs

void liste_emprunteurs(){
    system("cls");
    emprunt_t prend_liv;
    adherent_t info;
	FILE *adh_fic = fopen("file.txt", "r");
    titre_projet("LES EMPRUNTEURS");
    printf("%15s%15s\n", "Nom", "ID");
    printf("%15s%15s\n\n","----------","----------");
    while (fread(&info, sizeof(adherent_t), 1, adh_fic)){
        if (info.adh_nb_emprunts > 0){
            printf("%15s%15d\n", info.adh_nom, info.adh_num);
        }  
    }
    fclose(adh_fic);
}

int total_emprunt(){
	emprunt_t prend_liv;
    FILE *emprunte = fopen("emprunt_livres.txt", "r");
	fseek(emprunte, 0, SEEK_END);
	int reNO = ftell(emprunte)/sizeof(prend_liv);
	fclose(emprunte);
	return reNO;
}
void gestion_emprunts(){
    char emprunt_titre[25] = "GESTION DES EMPRUNTS";
	titre_projet(emprunt_titre);
    int choix_1, readChoix_1;
    do{
        printf("\n\n1. EMPRUNTER UN LIVRE\n");
        printf("2. AFFICHER LA LISTE DES LIVRES EMPRUNTES\n");
        printf("3. RENDRE UN LIVRE\n");
        printf("4. AFFICHER LA LISTE DES EMPRUNTEURS DE LIVRES\n");
        printf("5. RETOUR AU MENU PRINCIPAL\n");

        printf("ENTREZ VOTRE CHOIX: ");
        readChoix_1 = scanf("%d", &choix_1);
        if(readChoix_1 == 0){
            while (readChoix_1 == 0){
                printf("ERREUR DE SAISIE\n");
                printf("ENTREZ VOTRE CHOIX: ");
                scanf("%*[^\n]");
                readChoix_1 = scanf("%d", &choix_1);
            }
        }
        if (readChoix_1 == 1){
            if(choix_1 != 1 && choix_1 != 2 && choix_1 != 3 && choix_1 != 4 && choix_1 != 5){
				printf("ERREUR DE SAISIE.\n");
                printf("VEUILLEZ ENTRER UN NOMBRE COMPRIS ENTRE 1 ET 5.\n");
			}
            else
            {
              switch (choix_1){
                case 1:
                    emprunter_livres();
                break;
                case 2:
                    liste_emprunts();
                break;
                case 3:
                    rendre_livres();
                break;
                case 4:
                    liste_emprunteurs();
                break;
                default:
                break;
              }
            }
        }
    } while (choix_1 != 5);
}