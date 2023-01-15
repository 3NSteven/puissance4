#include "globale.h"

#define NIVEAU_DE_RECHERCHE 4

col_val minmax(char (*grille2)[MAX_COLONNE], int profondeur, bool maximazingPlayer, char signe, int alpha, int beta){

	//int resultat = verifGrille(grille2, (player + tour%2 )->Jsign);
	col_val col_val, new_score;
	int value, colonne;
	char enemy;

	if (signe == 'X')
		enemy = 'O';
	else
		enemy = 'X';	

	int nb_valide = nb_move_valide(grille2);
	/* 
		printf("enemy=%c\n", enemy);
		afficheGrille(grille2);
		printf("enemy gagne=%d\n", verifGrille(grille2, enemy));
		printf("profondeur=%d\n", profondeur);
	*/

	// Toutes les conditions d'arret de la fonction
	if(profondeur == 0 || verifGrille(grille2, signe) == 1 || verifGrille(grille2, enemy) == 1 || nb_valide == 0){
		col_val.colonne = -1;
		if (profondeur != 0)
		{
			if (verifGrille(grille2, signe) == 1){	//la victoire est a chercher absolument
				col_val.valeur = (int) 999999;
			}
			else if (verifGrille(grille2, enemy) == 1){	//la victoire de l'enemi est a eviter absolument
				col_val.valeur = (int) -999999;
			}
			else
				col_val.valeur = 0;	
		}
		else{
			col_val.valeur = position_score(grille2, signe);
		}
		return col_val;
	}

	int pos[nb_valide];
	position_move_valide(grille2, pos); // On remplie le tableau des coups possible pos[]
	char grille_temp[MAX_LINE][MAX_COLONNE];

	if (maximazingPlayer) // Tour de l'ia
	{
		col_val.valeur = (int) -999999;
		col_val.colonne = pos[rand()%nb_valide]; // On prend une colonne au hazar parmis les disponibles

		for (int c = 0; c < nb_valide; c++) //Pour chaque coups possible
		{
			for ( int j = 0; j < MAX_LINE; ++j )
				memcpy(grille_temp[j], grille2[j], MAX_COLONNE);
			
			ajouterJeton(grille_temp, signe, pos[c]);
			new_score = minmax(grille_temp, (profondeur-1), false, signe, alpha, beta);
			if (new_score.valeur > col_val.valeur)
			{
				col_val.colonne = pos[c];
				col_val.valeur = new_score.valeur;
			}
			
			// On prend la valeur la plus grande valeur comme alpha
			if (alpha <= col_val.valeur)
				alpha = col_val.valeur;
			
			// Si alpha devient plus grand que le beta actuel on arrete
			if(alpha >= beta)
				break;
			
		}

		return col_val;
	}
	else{ // Tour de l'adversaire
		col_val.valeur = (int) 999999;

		col_val.colonne = pos[rand()%nb_valide]; // On prend une colonne au hazar parmis les disponibles

		for (int c = 0; c < nb_valide; c++)
		{
			for ( int j = 0; j < MAX_LINE; ++j )
				memcpy(grille_temp[j], grille2[j], MAX_COLONNE);
			
			ajouterJeton(grille_temp, enemy, pos[c]); // L'enemy pose un jeton

			// On calcule a nouveau notre score après le jeu de l'enemy
			new_score = minmax(grille_temp, (profondeur-1), true, signe, alpha, beta);
			if (new_score.valeur < col_val.valeur)
			{
				col_val.colonne = pos[c];
				col_val.valeur = new_score.valeur;
			}

			// On prend la valeur la plus petite valeur comme beta
			if (beta >= col_val.valeur)
				beta = col_val.valeur;
			
			// Si beta devien plus petit que l'alpha actuel on arrete
			if (alpha >= beta)
				break;
		
		}

		return col_val;
	}
	
	//return col_val;
}



/*
	IA qui joue avec la strategie min-max
*/
int ia3(char (*grille2)[MAX_COLONNE], char signe){

	col_val resultat;
	resultat = minmax(grille2, NIVEAU_DE_RECHERCHE, true, signe, -999999, 999999);

    return resultat.colonne;

}