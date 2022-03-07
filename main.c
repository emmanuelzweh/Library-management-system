#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "mylibrary.h"


// les titres de heading
char main_titre[40] = "GESTION DES LIVRES PRETS";

// Cette fonction permet d'afficher le titre d'un section dans l'application
void titre_projet(char *titre){
    printf("------------------------------------------------------------------------------------------------------\n");
	printf("|                                     %s                                        |\n", titre);
	printf("-------------------------------------------------------------------------------------------------------\n");
}

int main(){
    system("cls"); // cette permet d'effacer de reintialiser la console
    titre_projet(main_titre);
	int choix,scanChoix;
    //NB: les commentaires sont appliqués aux autres menus
	do{
		printf("\n\n1. GESTION DES ADHERENTS\n");
		printf("2. GESTION DES LIVRES\n");
		printf("3. GESTION DES EMPRUNTS\n");
		printf("4. QUITTER LE PROGRAMME\n");

		printf("\nENTREZ VOTRE CHOIX: ");
         //la fonction scanf retourne un booléen(0 et 1)
         //si un utilsateur entres un entier dans cas elle retourne 1 et O pour d'autres type de donnée
		scanChoix = scanf("%d", &choix);
		if(scanChoix == 0){
            // ici la boucle aura affiche un message erreur et donnes une occasion à utilisateur de changer son choix
            // Tanque il entre un type de donnée qui n'est entier
			while (scanChoix == 0){
                printf("ERREUR DE SAISIE!!!\nVEUILLEZ ENTRER UN NOMBRE COMPRIS ENTRE 1 ET 4\n");
                printf("ENTREZ VOTRE CHOIX: ");
                scanf("%*[^\n]");
                scanChoix = scanf("%d", &choix);
            }		
		}
        // ici le choix est validé parce que c'est un entier	
		if (scanChoix == 1){
            //ce conditon permet d'afficher un message d'erreur lorsque l'entier n'est pas compris entre 1 et 4						
			if(choix != 1 && choix != 2 && choix != 3 && choix != 4){
				printf("ERREUR DE SAISIE.\n");
			}
            else{
                switch (choix)
                {
                case 1:
                    system("cls");
                    gestion_adhr();
                    break;
                case 2:
					system("cls");
                    gestion_livres();
                    break;
                case 3:
					system("cls");
                    gestion_emprunts();
                    break;
                default:
                    system("cls");
                    break;
                }
            }
		}
	}while(choix != 4);
    return 0;
}  