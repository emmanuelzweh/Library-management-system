
// structure pour l'address de les adherents
typedef struct {
int adr_cp;
char adr_ville[25];
char adr_rue[25];
} adresse_t;

//structure pour les adherents
typedef struct {
int adh_num;
char adh_nom[25];
adresse_t adh_adresse;
int adh_nb_emprunts;
} adherent_t;

//Livres emprunt
typedef struct {
int livre_id;
char titre_de_livre[25];
char nom_prenom_auteur[25];
int adh_id;
} emprunt_t;

// auteur structure
typedef struct {
char nom[25];
char prenom[25];
}liv_auteur;
// la structure de livre
typedef struct {
int liv_num;
char liv_titre[50];
liv_auteur auteur_info;
int liv_emprunteur;
} livre_t;

// extern char main_titre[25] = "GESTION DES LIVRES PRET";
void titre_projet(char *titre);
//les phototypes les fonction en gestion des adherent
int get_id(int id);
void ajout_adherent();
int totalRecord();
void modif_adherent();
void liste_adherents();
void supprime_adherent();
void recherche_adherent();
void gestion_adhr();

//les phototypes les fonction en gestion des livres
void ajout_livre();
int total_livre();
void liste_livres();
void modif_livre();
void supprime_livre();
void recherche_livre();
void gestion_livres();

//emprunt des livre
void emprunter_livres();
void gestion_emprunts();
int total_emprunt();
void liste_emprunteurs();
void rendre_livres();
void liste_emprunts();