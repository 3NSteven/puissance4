#include "globale.h"

// Initial values of
// Alpha and Beta
int MAX = 1000;
int MIN = -1000;


int max(int a, int b){
    if (a>b)
    {
        return a;
    }
    else{
        return b;
    }  
}
int min(int a, int b){
    if (a<b)
    {
        return a;
    }
    else{
        return b;
    }  
}

// Returns optimal value for
// current player (Initially called
// for root and maximizer)
int minimax(int depth, int nodeIndex, int maximizingPlayer, int values[8], int alpha, int beta)
{
	// Terminating condition. i.e
	// leaf node is reached
	if (depth == 3)
		return values[nodeIndex];

	if (maximizingPlayer)
	{
		int best = MIN;

		// Recur for left and
		// right children
		for (int i = 0; i < 2; i++)
		{
			int val = minimax(depth + 1, nodeIndex * 2 + i,
							false, values, alpha, beta);
			best = max(best, val);
			alpha = max(alpha, best);

			// Alpha Beta Pruning
			if (beta <= alpha)
				break;
		}
		return best;
	}
	else
	{
		int best = MAX;

		// Recur for left and
		// right children
		for (int i = 0; i < 2; i++)
		{
			
			int val = minimax(depth + 1, nodeIndex * 2 + i,
							true, values, alpha, beta);
			best = min(best, val);
			beta = min(beta, best);

			// Alpha Beta Pruning
			if (beta <= alpha)
				break;
		}
		return best;
	}
}



/*
    IA qui joue avec la strategie min-max
*/
int ia2(char (*grille2)[MAX_COLONNE], char signe){
    
    int r;
    // Driver Code
    int values[8]={3, 5, 6, 9, 1, 2, 0, -1};
    printf("The optimal value is : ", minimax(0, 0, true, values, MIN, MAX));
    
}
    
