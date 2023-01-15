#ifndef SETTINGS
#define SETTINGS

#define MAX_LINE 6
#define MAX_COLONNE 7

#define MAX_PSEUDO_LEN 20

void afficheGrille(char grille[MAX_LINE][MAX_COLONNE]);
void creerGrille(char (*grille2)[MAX_COLONNE]);
int ajouterJeton(char (*grille2)[MAX_COLONNE], char signe, int colonne);

const char * IA[] = {
    "IA0",
    "IA1"
};

typedef struct joueur
{
    char Jnom[MAX_PSEUDO_LEN]; // Le nom du joueur
    char Jsign; // Quel jeton il posséde
    bool isIA; // Si c'est une IA
    int whichIA;
    int partieGagner;
}joueur;


int partie(joueur* player, int round);

#endif
