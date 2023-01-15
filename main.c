#include "globale.h"

int partie(joueur* player, int round){
    
    // Initialise la grille
    char grille[MAX_LINE][MAX_COLONNE];

    creerGrille(grille);

    printf("\n--------GAME %d START--------\n", round);

    afficheGrille(grille);
    
    int fin = 0; //definie la fin d'une partie
    int tour = 0; //definie le nombre de tour joué
    char choixS[20];
    int choix;

    while (!fin)
    {
       
        if ( (player + (tour%2))->isIA == true ){ //si le joueur1 est une IA   
            switch ( (player + tour%2)->whichIA) // On appele la fonction approprier à la bonne IA
            {
            case 0: // IA0
                choix = ia0(grille, (player + (tour%2))->Jsign);
                break;
            case 1: // IA1
                choix = ia1(grille, (player + (tour%2))->Jsign);
                break;
            case 2: // IA2
                choix = ia2(grille, (player + (tour%2))->Jsign);
                break;
            default: // Fonction non repertorier
                    printf("No function for this AI in the files.\n");
                    return -1;
                break;
            }
            ajouterJeton(grille, (player + tour%2 )->Jsign, choix);
        }
        else{ // Si c'est un joueur humain
            printf("Select a column between 1 and 7:\n");
            do{
                scanf("%s", choixS);
                choix = atoi(choixS);
            }
            while(ajouterJeton(grille, (player + tour%2 )->Jsign, choix-1) == -1);
        }

        // Verification de l'etat de la grille de jeu
        switch(verifGrille(grille, (player + tour%2 )->Jsign))
        {
            case 0: // Rien a signaler
                break;
            case 1: // Le joueur 1 gagne la partie
                printf("The player %s won the game\n", (player + tour%2 )->Jnom );
                printf("--------GAME %d OVER---------\n", round);
                return 1;
                break;
            case 2: // Le joueur 2 gagne la partie
                printf("The player %s won the game\n", (player + tour%2 )->Jnom );
                printf("--------GAME %d OVER---------\n", round);
                return 2;
                break;
        }

        if (tour == 41) //si aucun n'a gagné et que la grille est remplie
        {
            return 0;
        }
        

        tour++;
    }

    

}

void makelog(joueur * J, int nulle){

    const char dossier[] = "logs";
    char **arg = (char**) malloc(3 * sizeof(char*));
    for (int i = 0; i < 3; i++)
        arg[i] = (char*) malloc(200 * sizeof(char));
  
    strcpy(arg[0], "mkdir");
    strcpy(arg[1], "logs");
    arg[2] = NULL;

    // access(dossier, 0) vaudra 0 si le dossier existe sinon -1
    if (access(dossier, 0) == -1){
        if (fork() == 0) {
            int status_code = execvp(arg[0], arg);
            if(status_code == -1)
                printf("Error while making the logs directory.\n");
        }
        sleep(1);
        printf("The logs directory has been succesfully made.\n");
    }
    chdir("logs");
    

    time_t timestamp = time( NULL );
    struct tm * pTime = localtime( & timestamp );
    char  *buffer = (char *) malloc( 200 * sizeof(char));
    strftime( buffer, 80, "%d-%m-%Y %H:%M:%S", pTime );
    strcat(buffer, ".csv");

/*
    printf("Date : %s\n", buffer);

    if (fork() == 0) {

        // Newly spawned child Process. This will be taken over by "mkdir date"
        strcpy(arg[1], buffer);
        int status_code = execvp(arg[0], arg);
        if (status_code == -1)
            printf("Error while making the date directory.\n");
    }
*/

    for (int i = 0; i < 3; i++)
        free(arg[i]);
        
    free(arg);
    //free(buffer);
    
    // On écrit dans un fichier le rapport de la partie
    FILE *log;
    log = fopen(buffer, "w+");
    fprintf(log, "%s\t%d\n%s\t%d\nDraw\t%d\nTotal\t%d\n",
     J[0].Jnom,
      J[0].partieGagner,
       J[1].Jnom,
        J[1].partieGagner,
         nulle,
          (J[0].partieGagner + J[1].partieGagner + nulle));
    close(log);
}


int main(int argc, char * argv[]){

    int nbparties = 0;
    int partieNulles = 0;
    srand(time(NULL));

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

    makelog(joueurs, partieNulles);

    // Libere l'espace allouer 
    free(joueurs);

    return 0;
    
}