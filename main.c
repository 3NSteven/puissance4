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
int ajouterJeton(char (*grille2)[MAX_COLONNE], char signe, int colonne){

    if(colonne > 6 || colonne < 0){ //si le joueur n'a pas choisi une colonne entre 1 et 7
        printf("You must select a column between 1 and 7:\n");
        return -1;
    }

    for (int i = 5; i >= 0; i--)    //verifie que la case n'est pas deja remplie (recherche de bas en haut pour savoir ou le jeton ajoute va atterir)
    {

        if( (*(*(grille2+i)+colonne)) == ' ')
        {
            *(*(grille2 + i) + colonne) = signe;
            afficheGrille(grille2); 
            return 0;
        }
        else if( i == 0 ){
            afficheGrille(grille2); 
            printf("This column is full ! Select another one:\n");
            return -1;
        }

    }

}

/*
    Verifie si les conditions de victoires sont remplie sur la grille

    Retourne 0 si rien n'a été trouvé
    Retourne 1 si le joueur 1 a reussi
    Retourne 2 si le joueur 2 a reussi

    Sinon retourne un code d'erreur
*/
int verifGrille(char (*grille2)[MAX_COLONNE] ){ //verifie si quatre jetons du meme joueur ont ete alignes

    // Verifie les lignes
    int count_x, count_o;
    for (int i = 0; i < MAX_LINE; i++)
    {
        count_x = 0;
        count_o = 0;
        for (int j = 0; j < MAX_COLONNE; j++)
        {
            if ( (*(*(grille2+i)+j)) == 'X' ){
                count_o = 0;
                count_x++;
            }
            else if ( (*(*(grille2+i)+j)) == 'O' ){
                count_x = 0;
                count_o++;
            }
            else{
                count_x = 0;
                count_o = 0;
            }
            
            if (count_x >= 4){
                printf("Victoire !!\n");
                return 1;
            }
            if (count_o >= 4){
                printf("Victoire !!\n");
                return 2;
            }
        }
        
    }

    // Verifie les colonne
    for (int colonne = MAX_COLONNE-1; colonne >= 0; colonne--){
        int victoireX = 0;
        int victoireO = 0;
        for (int i = MAX_LINE-1; i >= 0; i--)
        {
            if(victoireX >= 4 ){
                printf("Victoire !!\n");
                return 1;
            }
            else if(victoireO >= 4){
                printf("Victoire !!\n");
                return 2;
            }
            else if( (*(*(grille2+i)+colonne)) == 'X')
            {
                victoireO = 0;
                victoireX++;
            }
            else if( (*(*(grille2+i)+colonne)) == 'O'){
                victoireX = 0;
                victoireO++;
            }
            else if( (*(*(grille2+i)+colonne)) == ' '){
                victoireX = 0;
                victoireO = 0;
            }
        }
    }
/*
    for (int i = 0; i < ; i++)
    {



    }
*/   

}

int partie(joueur* player, int round){
    
    // Initialise la gille
    char grille[6][7];

    creerGrille(grille);

    printf("\n--------GAME %d START--------\n", round);

    afficheGrille(grille);
    
    int fin = 0; //definie la fin d'une partie
    int tour = 0; //definie le nombre de tour joué
    char choixS[20];
    int choix;

    while (!fin)
    {
       
        if ( (player + (tour%2))->isIA == true )    //si le joueur1 est une IA
            {   
            //((player + 0)->Jnom )
            switch ( (player + tour%2)->whichIA)
            {
            case 0:
                //choix = ia0(grille, (player + 0)->Jsign);
                break;
            case 1:

                break;
            default:
                    printf("No function for this AI in the files.\n");
                break;
            }

        }
        else{
            printf("Select a column between 1 and 7:\n");
            do{
                scanf("%s", choixS);
                choix = atoi(choixS);
            }
            while(ajouterJeton(grille, (player + tour%2 )->Jsign, choix-1) == -1);
        }

        switch(verifGrille(grille))
        {
            case 0:
                break;
            case 1:
                printf("The player %s won the game\n", (player + tour%2 )->Jnom );
                printf("--------GAME %d OVER---------\n", round);
                return 1;
                break;
            case 2:
                printf("The player %s won the game\n", (player + tour%2 )->Jnom );
                printf("--------GAME %d OVER---------\n", round);
                return 2;
                break;
        }
        tour++;
    }

    

}


/*
    Regle les parametres des joueurs (pseudo, signe, etc..)

    Retourne 0 ou un code d'erreur
    Retourne -1 si il n'y a pas au moins une IA
    Retourne -2 si le nom du joueur est trop grand
*/
int fixesettings(char *J1, char *J2, joueur* J){

    bool findIA = false;

    int i = 0;
    while(IA[i])
    {
        if ((strcmp(J1, IA[i]) == 0) || (strcmp(J2, IA[i]) == 0))
            findIA = true;
        i++;
    }

    if(!findIA){
        printf("There is no AI's name among the players' names.\n");
        printf("Ex: './main Charles IA0' or even './main IA1 Pablo'\n");
        return -1;
    }
    
        
    for (int i = 0; i < 2; i++)
    {
        if(i == 0){
            strcpy( (J+0)->Jnom, J1);
            (J+0)->Jsign = 'X';
            int i = 0;
            while(IA[i])
            {
                if ( strcmp(J1, IA[i]) == 0)
                {
                    (J+0)->isIA = true;
                    (J+0)->whichIA = i;
                    break;
                }
                else{ (J+0)->isIA = false; }
                i++;
            }
            (J+0)->partieGagner = 0;
        }
        else{
            strcpy( (J+1)->Jnom, J2);
            (J+1)->Jsign = 'O';
            int i = 0;
            while(IA[i])
            {
                if (strcmp(J2, IA[i]) == 0 )
                {
                    (J+1)->isIA = true;
                    (J+1)->whichIA = i;
                    break;
                }
                else{ (J+1)->isIA = false; }
                i++;
            }
            (J+1)->partieGagner = 0;
        }
    } 
    
}



int main(int argc, char * argv[]){

    int nbparties = 0;
    
    if(argc == 3) nbparties = 1;
    else if(argc == 4) nbparties = atoi(argv[3]);
    else {
        printf("Use:\n");
        printf("%s Player1 Player2 (Rounds) \n", argv[0]);
        return 1;
    }

    printf("Player 1 : %s\n", argv[1]);
    printf("Player 2 : %s\n", argv[2]);
    printf("Number of Rounds : %d\n", nbparties);

    // fixé les parametres des joueurs
    joueur* joueurs = malloc( 2 * sizeof *joueurs);

    fixesettings(argv[1], argv[2], joueurs);

    int gagnant;
    for(int round = 1; round<=nbparties; round++){   //chaque partie
        gagnant = partie(joueurs, round);
        
        if(gagnant == 0){
            partieNulles++;
        }
        else{
            joueurs[gagnant-1].partieGagner++;
        }
    }

    printf("SUMMARY:\n%s: %d victories\n%s: %d victories\nDraw: %d\n",
     joueurs[0].Jnom,
      joueurs[0].partieGagner,
       joueurs[1].Jnom,
        joueurs[1].partieGagner,
         partieNulles);

    return 0;
    
}
