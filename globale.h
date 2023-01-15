#ifndef GLOBALE
#define GLOBALE

#define MAX_LINE 6
#define MAX_COLONNE 7

#define MAX_PSEUDO_LEN 20

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>

void afficheGrille(char grille[MAX_LINE][MAX_COLONNE]);
void creerGrille(char (*grille2)[MAX_COLONNE]);
int colonne_rempli(char (*grille2)[MAX_COLONNE], int colonne);
int ajouterJeton(char (*grille2)[MAX_COLONNE], char signe, int colonne);

typedef struct joueur
{
    char Jnom[MAX_PSEUDO_LEN]; // Le nom du joueur
    char Jsign; // Quel jeton il posséde
    bool isIA; // Si c'est une IA
    int whichIA;
    int partieGagner;
}joueur;

int fixesettings(char *J1, char *J2, joueur* J, char *prem_arg);

int verifGrille(char (*grille2)[MAX_COLONNE], char signe);
int partie(joueur* player, int round);

int ia0(char (*grille2)[MAX_COLONNE], char signe);
int ia1(char (*grille2)[MAX_COLONNE], char signe);

//int minimax(int depth, int nodeIndex, int maximizingPlayer, int values[8], int alpha, int beta);


int compte_case(int *tab, char signe);
int calcule_score(int jeton, int libre, int enemy);
int position_score(char (*grille2)[MAX_COLONNE], char signe);
int nb_move_valide(char (*grille2)[MAX_COLONNE]);
void position_move_valide(char (*grille2)[MAX_COLONNE], int *tab);
int select_meilleur_move(char (*grille2)[MAX_COLONNE], char signe);

typedef struct col_val {
	int colonne, valeur;
}col_val;

col_val minmax(char (*grille2)[MAX_COLONNE], int profondeur, bool maximazingPlayer, char signe, int alpha, int beta);
int ia2(char (*grille2)[MAX_COLONNE], char signe);
int ia3(char (*grille2)[MAX_COLONNE], char signe);
int ia4(char (*grille2)[MAX_COLONNE], char signe);

#endif
