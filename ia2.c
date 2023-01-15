#include "globale.h"

/*
	Compte le nombres de signe correspondant au signe dans le tableau
	Exemple:
	fenetre[4] = {'X', 'X', 'X', ' '}
	compte_case(fenetre, 'X') // return 4
*/
int compte_case(int *tab, char signe){
	int nombre = 0;
	for (int i = 0; i < 4; i++)
		if(tab[i] == signe)
			nombre++;
	
	return nombre;
}

/*
	Calcule le score par rapport au jeton
*/
int calcule_score(int jeton, int libre, int enemy){

	int score = 0;

	if (jeton == 4) // On aligne 4 jeton !!!!
		score = score+9999;

	else if (jeton == 3 && libre == 1) // On aligne 3 jeton
		score = score+5;

	else if (jeton == 2 && libre == 2) // On aligne 2 jeton
		score = score+2;
	

	if (enemy == 3 && libre == 1) // enemy aligne 3 jeton
		score = score-20;
	else if (enemy == 4) // enemy aligne 4 jeton !!!!
		score = score-9999;

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
	for (int i = 0; i < MAX_LINE; i++) // On prend les signes de la colonne du milieu dans tab_centre
		tab_centre[i] = (*(*(grille2+i)+(MAX_COLONNE/2)));
	
	int nombre = 0;
	for (int i = 0; i < MAX_LINE; i++) // Pour chaque signe que l'on posséde deja au milieu nombre+1
		if(tab_centre[i] == signe)
			nombre++;
		
	score = score + nombre*3; // On augmente le score pour chaque signe que l'on possede au milieu
	
	//printf("score apres centre:%d\n", score);

	// Horizontal
	int tab_ligne[MAX_COLONNE], fenetre[4]; 
	for (int r = 0; r < MAX_LINE; r++) // Pour chaque ligne
	{
		for (int j = 0; j < MAX_COLONNE; j++) // Enregistre la ligne dans tab_ligne
			tab_ligne[j] = (*(*(grille2+r)+j));
		
		for (int c = 0; c < (MAX_COLONNE-3); c++) // Des colonnes [0-4], [1-5], [2-6], [3-7]
		{
			// fenetre = tab_ligne[0:0+4] prend les colonnes de [0-4]
			// fenetre = tab_ligne[1:1+4] prend les colonnes de [1-5]
			// fenetre = tab_ligne[2:2+4] prend les colonnes de [2-6]
			// fenetre = tab_ligne[3:3+4] prend les colonnes de [3-7]
			memcpy(fenetre, tab_ligne+c, sizeof(int)*4);
			
			// compte parmis les 4 cases aligné le nb de signe, de vide et de signe oposé
			jeton = compte_case(fenetre, signe);
			libre = compte_case(fenetre, ' ');
			op_jeton = compte_case(fenetre, op_signe);

			score = score + calcule_score(jeton, libre, op_jeton);
		}
	}

	//printf("score après horizontal:%d\n", score);

	
	// Verticale
	int tab_colonne[MAX_COLONNE]; 
	for (int c = 0; c < MAX_COLONNE; c++) // Pour chaque colonne
	{
		for (int j = 0; j < MAX_LINE; j++) // Enregistre la colonne dans tab_colonne
			tab_colonne[j] = (*(*(grille2+j)+c));

		for (int r = 0; r < (MAX_LINE-3); r++)
		{
			memcpy(fenetre, tab_colonne+r, sizeof(int)*4);

			// compte parmis les 4 cases aligné le nb de signe, de vide et de signe oposé
			jeton = compte_case(fenetre, signe);
			libre = compte_case(fenetre, ' ');
			op_jeton = compte_case(fenetre, op_signe);

			score = score + calcule_score(jeton, libre, op_jeton);
		}
		
	}

	//printf("score apres Verticale:%d\n", score);

	
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

			jeton = compte_case(fenetre, signe);
			libre = compte_case(fenetre, ' ');
			op_jeton = compte_case(fenetre, op_signe);

			score = score + calcule_score(jeton, libre, op_jeton);
		}
	}

	//printf("score apres bas gauche à haut droite:%d\n", score);
	
	
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

			jeton = compte_case(fenetre, signe);
			libre = compte_case(fenetre, ' ');
			op_jeton = compte_case(fenetre, op_signe);

			score = score + calcule_score(jeton, libre, op_jeton);
		}
	}

	//printf("score apres haut gauche à bas droit:%d\n", score);

	//printf("score = score(%d)\n", score);
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
		
        //printf("col %d:\n", (position_valide[i]+1));

        score = position_score(grille_temp, signe);
        
        //printf("col %d, value %d\n", (position_valide[i]+1), score);

		if (score > best_score){
			best_score = score;
			best_colonne = position_valide[i];
		}
	}
	
	return best_colonne;
}


/*
    IA qui joue avec la strategie du meilleur coup disponible
*/
int ia2(char (*grille2)[MAX_COLONNE], char signe){

	return select_meilleur_move(grille2, signe);
}