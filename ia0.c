#include "globale.h"

int ia0(char (*grille2)[MAX_COLONNE], char signe){
    int r = rand() % (MAX_COLONNE-1);

    while((*(*(grille2)+r)) != ' '){
        r = rand() % (MAX_COLONNE-1);
    }

    return r;
}
