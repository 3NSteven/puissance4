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
#include <pthread.h>

void afficheGrille(char grille[MAX_LINE][MAX_COLONNE]);
void creerGrille(char (*grille2)[MAX_COLONNE]);
int ajouterJeton(char (*grille2)[MAX_COLONNE], char signe, int colonne);

typedef struct joueur
{
    char Jnom[MAX_PSEUDO_LEN]; // Le nom du joueur
    char Jsign; // Quel jeton il posséde
    bool isIA; // Si c'est une IA
    int whichIA;
    int partieGagner;
}joueur;

int fixesettings(char *J1, char *J2, joueur* J);

int verifGrille(char (*grille2)[MAX_COLONNE], char signe);
int partie(joueur* player, int round);

int ia0(char (*grille2)[MAX_COLONNE], char signe);
int ia1(char (*grille2)[MAX_COLONNE], char signe);
int ia2(char (*grille2)[MAX_COLONNE], char signe);

#endif
