#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <stdbool.h>

#include "settings.h"

/*
    Affiche la grille de jeu
*/
void afficheGrille(char grille[MAX_LINE][MAX_COLONNE]){

    for (int i = 0; i < MAX_LINE; i++)
    {
        printf("\n");
        for (int j = 0; j < MAX_COLONNE; j++)
        {
            printf("| %c ", grille[i][j]);
        }
        printf("|");
    }
    printf("\n\n");

}

/*
 Créer une grille 6x7 vide
*/
void creerGrille(char (*grille2)[MAX_COLONNE]){
    for (int i = 0; i < MAX_LINE; i++)
    {
        for (int j = 0; j < MAX_COLONNE; j++)
        {
            *(*(grille2 + i) + j) = ' ';
        }
    }
}

/*
    Ajoute le jeton du joueur a la colonne selectionné

    Retourne 0 ou un code d'erreur
*/
int ajouterJeton(char (*grille2)[MAX_COLONNE], int colonne){


    for (int i = 5; i >= 0; i--)
    {

        if( (*(*(grille2+i)+colonne)) == ' ')
        {
            *(*(grille2 + i) + colonne) = 'X';
            afficheGrille(grille2); 
            return 0;
        }
        else if( i == 0 ){
            afficheGrille(grille2); 
            printf("Cette colonne est plein, selectionné une autre colonne:\n\n");
            return -1;
        }

    }

}

int partie(char *J1, char *J2){

    int fin = 0; //definie la fin d'une partie
    int tour = 0; //definie le nombre de tour joué
    while (!fin)
    {
       if (tour%2 == 0) // Tour du Joueur1
       {
           
       }
       else // Tour du Joueur2
       {

       }

       tour++;
    }

}

int fixesettings(char *J1, char *J2, joueur* J){

    bool findIA = false;
    for (int i = 0; i < 2; i++)
    {
        if ((strcmp(J1, IA[i]) == 0) || (strcmp(J2, IA[i]) == 0))
        { 
           findIA = true; 
        }
    }

    if(!findIA){
        printf("Il n'y a aucun nom d'IA parmis les noms des joueurs.\n");
        printf("Ex: './main Charles IA0' ou encore './main IA1 Pablo'\n");
        return -1;
    }
    else{

        

    }

}



int main(int argc, char * argv[]){

    int nbparties = 0;
    
    if(argc == 3) nbparties = 1;
    else if(argc == 4) nbparties = atoi(argv[3]);
    else {
        printf("Insctruction de lancement\n");
        printf("%s Joueur1 Joueur2 (nbpartie) \n", argv[0]);
        return 1;
    }

    printf("Joueur 1 : %s\n", argv[1]);
    printf("Joueur 2 : %s\n", argv[2]);
    printf("Nombre de partie à lancer : %d\n", nbparties);

    // Initialise la gille
    char grille[6][7];

    creerGrille(grille);
    afficheGrille(grille);

    // fixé les parametres des joueurs
    joueur* joueurs = malloc( 2 * sizeof *joueurs);
    
    //strcpy(joueurs[i].Jnom, Nomjoueur[i]);

    fixesettings(argv[1], argv[2], joueurs);

    /*
    for (int i = 0; i < 7; i++)
    {
        ajouterJeton(grille, 3);
    }
    */

    for(int i = 0; i < nbparties; i++){
        //partie(, ); 
    }

}