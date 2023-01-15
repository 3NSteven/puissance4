#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void afficheGrille(char grille[6][7]){
    for (int i = 0; i < 6; i++)
    {
        printf("|");
        for (int j = 0; j < 7; j++)
        {
            printf(" ");
           putchar(grille[i][j]);
           printf(" |");
        }
        printf("\n");
    }
}

int creerGrille(char (*grille2)[7]){
    
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            *(*(grille2 + i) + j) = ' ';
        }
    }

}

/*
    Ajoute le jeton du joueur a la colonne selectionné

    Retourne 0 ou un code d'erreur
*/
int ajouterJeton(char (*grille2)[7], int colonne){


    for (int i = 5; i >= 0; i--)
    {

        if( (*(*(grille2+i)+colonne)) == ' ')
        {
            *(*(grille2 + i) + colonne) = 'X';
            return 0;
        }
        else if( i == 0 ){
            printf("This column is full ! Choose another one.\n");
            return -1;
        }

    }

}

int partie(char * joueur1, char * joueur2, int tour){

    //initialise la grille
    creerGrille(grille);

    printf("\n--------ROUND %d START--------\n", i+1);

    while(0){   //tant que personne n'a aligne quatre jetons
        afficheGrille(grille);

        if(tour%2 != 0){    //tour impair (joueur1)
            printf("Au tour de %s", joueur1);
        }
        else if(tour%2 == 0){   //tour pair (joueur2)
            printf("Au tour de %s", joueur2);
        }
    }

        
    printf("--------ROUND %d OVER---------\n\n", i+1);

}

int main(int argc, char * argv[]){

    int nbparties = 0;

    if(argc == 3) nbparties = 1;
    else if(argc == 4) nbparties = atoi(argv[3]);
    else {
        printf("Use:\n");
        printf("%s Player1 Player2 Rounds \n", argv[0]);
        return 1;
    }

    printf("Player 1 : %s\n", argv[1]);
    printf("Player 2 : %s\n", argv[2]);
    printf("Number of Rounds: %d\n", nbparties);

    char * joueur1 = argv[1];
    char * joueur2 = argv[2];


    char grille[6][7];
    

    for(int tour = 1; tour<=nbparties; tour++){   //chaque partie
        
        partie(joueur1, joueur2, tour);


    }

    
    
}
