#include "globale.h"

#define PROBA_CENTRE 35
#define PROBA_PRESQUE_CENTRE 25
#define PROBA_PRESQUE_HORS 15
#define PROBA_HORS 17

/*
    IA qui essaye de jouer plus souvent au milieu de la grille
*/
int ia1(char (*grille2)[MAX_COLONNE], char signe){
    
    int tendance, r;

    while(1){

        tendance = rand() % 100;

        if (tendance > 100-PROBA_CENTRE)  //entre 100 et 65 donc 35%
        {
            if((*(*(grille2)+3)) == ' ') return 3;
        }
        else if (tendance > 100-PROBA_CENTRE-PROBA_PRESQUE_CENTRE)                              //entre 65 et 40 donc 25%
        {
            if((tendance % 2) && ((*(*(grille2)+2)) == ' ')){
                return 2;
            }
            else if((*(*(grille2)+4)) == ' '){
                return 4;
            }
        }
        else if (tendance > 100-PROBA_CENTRE-PROBA_PRESQUE_CENTRE-PROBA_PRESQUE_HORS)                               //entre 40 et 25 donc 15%
        {
            if((tendance % 2) && ((*(*(grille2)+1)) == ' ')){
                return 1;
            }
            else if((*(*(grille2)+5)) == ' '){
                return 5;
            }
        }
        else if (tendance > 100-PROBA_CENTRE-PROBA_PRESQUE_CENTRE-PROBA_PRESQUE_HORS-PROBA_HORS)                             //entre 25 et 12 donc 17%
        {
            if((tendance % 2) && ((*(*(grille2)+0)) == ' ')){
                return 0;
            }
            else if((*(*(grille2)+6)) == ' '){
                return 6;
            }
        }
        else{                                               //12% de full aleatoire
            r = rand() % MAX_COLONNE;
            if((*(*(grille2)+r)) == ' '){
                return r;
            }
        }                                     
        
    }
}
    