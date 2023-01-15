#include "globale.h"
#include "settings.h"

/*
    Regle les parametres des joueurs (pseudo, signe, etc..)

    Retourne 0 ou un code d'erreur
    Retourne -1 si il n'y a pas au moins une IA
    Retourne -2 si le nom du joueur est trop grand
*/
int fixesettings(char *J1, char *J2, joueur* J, char *prem_arg){

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
        printf("Ex: '%s Charles IA0' or even '%s IA1 Pablo'\n", prem_arg, prem_arg);
        return -1;
    }
    
    if ( strlen(J1) > MAX_PSEUDO_LEN)
    {
        printf("The first player's name '%s' is too long (must be less than 20 characters)\n", J1);
        return -2;
    }
    if ( strlen(J1) > MAX_PSEUDO_LEN)
    {
        printf("The seconde player's name '%s' is too long (must be less than 20 characters)\n", J2);
        return -2;
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
    
    return 0; // Les paramètres du programme on été fixés
}
