#include "globale.h"

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
int verifGrille(char (*grille2)[MAX_COLONNE], char signe){ //verifie si quatre jetons du meme joueur ont ete alignes

    int count;

    // Verifie les lignes
    for (int i = 0; i < MAX_LINE; i++)
    {
        count = 0;
        for (int j = 0; j < MAX_COLONNE; j++)
        {
            if ( (*(*(grille2+i)+j)) == signe ){
                count++;
            }
            else{
                count = 0;
            }
            
            if (count >= 4){
                printf("Victoire !!\n");
                if(signe == 'X'){
                    return 1;
                }
                else if(signe == 'O')
                {
                    return 2;
                }
            }
        }   
    }

    // Verifie les colonne
    for (int colonne = 0; colonne < MAX_COLONNE; colonne++){
        count = 0;
        for (int i = MAX_LINE-1; i >= 0; i--)
        {
            if ( (*(*(grille2+i)+colonne)) == signe ){
                count++;
            }
            else{
                count = 0;
            }
            
            if (count >= 4){
                printf("Victoire !!\n");
                if(signe == 'X'){
                    return 1;
                }
                else if(signe == 'O')
                {
                    return 2;
                }
            }
        }
    }
    

    for(int i =(MAX_LINE-3); i < MAX_LINE; i++){
        for(int j = 0; j < (MAX_COLONNE-3) ; j++){

            //printf("[%d;%d][%d;%d][%d;%d][%d;%d]", i, j, (i-1), (j+1), (i-2), (j+2), (i-3), (j+3));
            
            if( ((*(*(grille2+i)+j)) == signe) && ((*(*(grille2+(i-1))+(j+1))) == signe) && ((*(*(grille2+(i-2))+(j+2))) == signe) && ((*(*(grille2+(i-3))+(j+3))) == signe) ){
                printf("Victoire !!\n");
                if (signe == 'X'){
                    return 1;
                }
                else{
                    return 2;
                }
            }
        }
    }
 
    //printf("\n\n");

    for(int i =(MAX_LINE-3); i < MAX_LINE; i++){
        for(int j = 0; j < (MAX_COLONNE-3) ; j++){

            //printf("[%d;%d][%d;%d][%d;%d][%d;%d]", i, j, (i+1), (j+1), (i+2), (j+2), (i+3), (j+3));
            
            if( ((*(*(grille2+i)+j)) == signe) && ((*(*(grille2+(i+1))+(j+1))) == signe) && ((*(*(grille2+(i+2))+(j+2))) == signe) && ((*(*(grille2+(i+3))+(j+3))) == signe) ){
                printf("Victoire !!\n");
                if (signe == 'X'){
                    return 1;
                }
                else{
                    return 2;
                }
            }
        }
    }

}
