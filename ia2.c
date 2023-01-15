#include "globale.h"

#define NIVEAU_DE_RECHERCHE 3

// Time : 1:05:45 / 1:27:28

typedef struct col_val {
	int colonne, valeur;
}col_val;

int count_case(int *tab, char signe){
	int nombre = 0;
	for (int i = 0; i < 4; i++)
	{
		if(tab[i] == signe){
			nombre++;
		}
	}
	return nombre;
}

int make_score(int jeton, int libre, int enemy){

	int score = 0;

	if (jeton == 4){
		score = score+9999;
	}
	else if (jeton == 3 && libre == 1){
		score = score+100;
	}
	else if (jeton == 2 && libre == 2){
		score = score+30;
	}

	if (enemy == 3 && libre == 1)
	{
		score = score-80;
	}

	return score;
}

// Donne le score correspondant à la case
int position_score(char (*grille2)[MAX_COLONNE], char signe){

	int score = 0, jeton = 0, libre = 0, op_jeton = 0;
	char op_signe;

	if (signe == 'X')
		op_signe = 'O';
	else
		op_signe = 'X';	


	// Calcule le score du centre
	int tab_centre[MAX_LINE];
	for (int i = 0; i < MAX_LINE; i++) // On prend la colonne du milieu
		tab_centre[i] = (*(*(grille2+i)+(MAX_COLONNE/2)));
	
	int nombre = 1;
	for (int i = 0; i < MAX_LINE; i++) // On compte le nombre de signe au milieu
		if(tab_centre[i] == signe)
			nombre++;
		
	score = score + nombre*6;
	

	// Horizontal
	int tab_ligne[MAX_COLONNE], fenetre[4]; 
	for (int r = 0; r < MAX_LINE; r++)
	{
		for (int j = 0; j < MAX_COLONNE; j++) // Enregistre la ligne r
			tab_ligne[j] = (*(*(grille2+r)+j));
		
		for (int c = 0; c < (MAX_COLONNE-3); c++) // De colonne 0 à 4
		{
			// window = row_array[0:0+4] prend les colonnes de [0-4]
			// window = row_array[1:1+4] prend les colonnes de [1-5]
			// window = row_array[2:2+4] prend les colonnes de [2-6]
			// window = row_array[3:3+4] prend les colonnes de [3-7]
			memcpy(fenetre, tab_ligne+c, sizeof(int)*4);
			
			jeton = count_case(fenetre, signe);
			libre = count_case(fenetre, ' ');
			op_jeton = count_case(fenetre, op_signe);

			score = score + make_score(jeton, libre, op_jeton);
		}
	}

	
	// Verticale
	int tab_colonne[MAX_COLONNE]; 
	for (int c = 0; c < MAX_COLONNE; c++)
	{
		for (int j = 0; j < MAX_LINE; j++) // Enregistre la colonne c
			tab_colonne[j] = (*(*(grille2+j)+c));

		for (int r = 0; r < (MAX_LINE-3); r++)
		{
			memcpy(fenetre, tab_colonne+r, sizeof(int)*4);

			jeton = count_case(fenetre, signe);
			libre = count_case(fenetre, ' ');
			op_jeton = count_case(fenetre, op_signe);

			score = score + make_score(jeton, libre, op_jeton);
		}
		
	}


	
	// Diagonale de bas gauche à haut droite
	for (int r = 0; r < (MAX_LINE-3); r++)
	{
		for (int c = 0; c < (MAX_COLONNE-3); c++)
		{
			for (int i = 0; i < 4; i++)
			{
				// Pour r=0 et c=0 On prend les 4 valeurs de la coordonné 0:0 à 4:4
				// fenetre[0] = grille[0][0];
				// fenetre[1] = grille[1][1];
				// fenetre[2] = grille[2][2];
				// fenetre[3] = grille[3][3];
				fenetre[i] = (*(*(grille2+r+i)+c+i));
			}

			jeton = count_case(fenetre, signe);
			libre = count_case(fenetre, ' ');
			op_jeton = count_case(fenetre, op_signe);

			score = score + make_score(jeton, libre, op_jeton);
		}
	}
	

	
	// Diagonale de haut gauche à bas droit
	for (int r = 0; r < (MAX_LINE-3); r++)
	{
		for (int c = 0; c < (MAX_COLONNE-3); c++)
		{
			for (int i = 0; i < 4; i++)
			{
				// Pour r=0 et c=0 On prend les 4 valeurs de la coordonné 0:0 à 4:4
				// fenetre[0] = grille[3][0];
				// fenetre[1] = grille[2][1];
				// fenetre[2] = grille[1][2];
				// fenetre[3] = grille[0][3];
				fenetre[i] = (*(*(grille2+r+(3-i))+c+i));
			}

			jeton = count_case(fenetre, signe);
			libre = count_case(fenetre, ' ');
			op_jeton = count_case(fenetre, op_signe);

			score = score + make_score(jeton, libre, op_jeton);
		}
	}

	return score;
}



// Nombre de colonnes jouables
int nb_move_valide(char (*grille2)[MAX_COLONNE]){
	int count = 0;
	for (int i = 0; i < MAX_COLONNE; i++){
		if(colonne_rempli(grille2, i) == 1) // Si la colonne n'est pas remplie elle est jouable
		{
			count++;
		}
	}
	return count;
}



// Repertorie toutes les colonnes jouables
void position_move_valide(char (*grille2)[MAX_COLONNE], int *tab){
	int count = 0;
	for (int i = 0; i < MAX_COLONNE; i++)
	{
		if(colonne_rempli(grille2, i)){ // Si la colonne n'est pas remplie elle est jouable
			*(tab+count) = i; // On l'ajoute a la liste des coup jouables
			count++;
		}
	}

}


// Prend le meilleur coup
int select_meilleur_move(char (*grille2)[MAX_COLONNE], char signe){

	char grille_temp[MAX_LINE][MAX_COLONNE];
	int best_score = -999999, score;

	int nb_valide = nb_move_valide(grille2); // Nombre de position valide
	int position_valide[nb_valide];
	position_move_valide(grille2, position_valide); // Tab de position valide
	
	int best_colonne;
	if (nb_valide == 1)
		best_colonne = position_valide[0]; // Colonne randome parmis les colonnes valide
	else
		best_colonne = position_valide[rand()%(nb_valide-1)]; // Colonne randome parmis les colonnes valide
	
	for (int i = 0; i < nb_valide; i++)
	{
		for ( int j = 0; j < MAX_LINE; ++j )
			memcpy(grille_temp[j], grille2[j], MAX_COLONNE);

		ajouterJeton(grille_temp, signe, position_valide[i]);
		score = position_score(grille_temp, signe);

		if (score > best_score){
			best_score = score;
			best_colonne = position_valide[i];
		}
	}
	

	return best_colonne;

}

col_val minmax(char (*grille2)[MAX_COLONNE], int profondeur, bool maximazingPlayer, char signe){

	//int resultat = verifGrille(grille2, (player + tour%2 )->Jsign);
	col_val col_val, new_score;
	int value, colonne;
	char enemy;

	if (signe == 'X')
		enemy = 'O';
	else
		enemy = 'X';	
	
	int nb_valide = nb_move_valide(grille2);
	

	//printf("\n profondeur=%d, verifgrille=%d", profondeur, verifGrille(grille2, signe));
	if(profondeur == 0 || verifGrille(grille2, signe) != 0 || nb_valide == 0){
		col_val.colonne = -1;
		if (profondeur != 0)
		{
			if(signe == 'X'){	//si le signe d'ia2 est X
				if (verifGrille(grille2, signe) == 2)	//la victoire de O est a eviter absolument
					col_val.valeur = (int) -999999;
				else if (verifGrille(grille2, signe) == 1)	//la victoire de X est a chercher absolument
					col_val.valeur = (int) 999999;
				else
					col_val.valeur = 0;
			}
			else if(signe == 'O'){	//si le signe d'ia2 est O
				if (verifGrille(grille2, signe) == 1)	//la victoire de X est a eviter absolument
					col_val.valeur = (int) -999999;
				else if (verifGrille(grille2, signe) == 2)	//la victoire de O est a chercher absolument
					col_val.valeur = (int) 999999;
				else
					col_val.valeur = 0;

			}
			
		}
		else{
			col_val.valeur = position_score(grille2, signe);
		}
		//printf("\n deep=%d, valeur=%d, colonne=%d \n", profondeur, col_val.valeur, col_val.colonne);
		return col_val;
	}

	printf("\n LOOOL %d\n", maximazingPlayer);

	int pos[nb_valide];
	position_move_valide(grille2, pos);

	if (maximazingPlayer)
	{
		printf("\n IA = TRUE \n");
		col_val.valeur = (int) -999999;

		col_val.colonne = pos[rand()%nb_valide]; // On prend une colonne au hazar parmis les disponibles
		printf("nb_position possible IA %d\n", nb_valide);

		for (int c = 0; c < nb_valide; c++)
		{
			char grille_temp[MAX_LINE][MAX_COLONNE];
			for ( int j = 0; j < MAX_LINE; ++j )
				memcpy(grille_temp[j], grille2[j], MAX_COLONNE);
			
			ajouterJeton(grille_temp, signe, pos[c]);
			afficheGrille(grille_temp);

			new_score = minmax(grille_temp, (profondeur-1), false, signe);
			if (new_score.valeur > col_val.valeur)
			{
				col_val.colonne = pos[c];
				col_val.valeur = new_score.valeur;
			}
			printf("On fais des partie max %d, valeur=%d, col=%d\n", pos[c], col_val.valeur, col_val.colonne);
		}

		printf("\n deep=%d, valeur=%d, colonne=%d \n", profondeur, col_val.valeur, col_val.colonne);
		return col_val;
		
	}
	else{
		printf("\n IA = FALSE \n");
		col_val.valeur = (int) 999999;

		col_val.colonne = pos[rand()%nb_valide]; // On prend une colonne au hazar parmis les disponibles
		printf("nb_position possible Joueur %d\n", nb_valide);
		for (int i = 0; i < nb_valide; i++)
			printf("[%d]", pos[i]);
		printf("\n");

		for (int c = 0; c < nb_valide; c++)
		{
			char grille_temp[MAX_LINE][MAX_COLONNE];
			for ( int j = 0; j < MAX_LINE; ++j )
				memcpy(grille_temp[j], grille2[j], MAX_COLONNE);
			
			ajouterJeton(grille_temp, enemy, pos[c]); // L'enemy pose un jeton
			afficheGrille(grille_temp);
			// On calcule a nouveau notre score après le jeu de l'enemy
			new_score = minmax(grille_temp, (profondeur-1), true, signe);
			if (new_score.valeur < col_val.valeur)
			{
				col_val.colonne = pos[c];
				col_val.valeur = new_score.valeur;
			}
			printf("On fais des partie min %d, valeur=%d, col=%d\n", pos[c], col_val.valeur, col_val.colonne);
		}
		printf("----------------------------------");
		printf("\n deep=%d, valeur=%d, colonne=%d \n", profondeur, col_val.valeur, col_val.colonne);
		return col_val;
	}
	
	//return col_val;
}


/*
    IA qui joue avec la strategie min-max
*/
int ia2(char (*grille2)[MAX_COLONNE], char signe){
        

	col_val resultat;
	resultat = minmax(grille2, NIVEAU_DE_RECHERCHE, true, signe);

	printf("\n %d, %d \n", resultat.valeur, resultat.colonne);

    return resultat.colonne;
}
    