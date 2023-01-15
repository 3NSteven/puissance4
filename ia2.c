#include "globale.h"


// Initial values of
// Alpha and Beta



// Returns optimal value for
// current player (Initially called
// for root and maximizer)
int minimax(int depth, int nodeIndex, int maximizingPlayer, int values[8], int alpha, int beta)
{
    int max = (int) INFINITY;
    int min = (int) -INFINITY;
	// Terminating condition. i.e
	// leaf node is reached

    return 1;

	if (depth == 3)
		return values[nodeIndex];

	if (maximizingPlayer)
	{
		int best = min;

		// Recur for left and
		// right children
		for (int i = 0; i < 2; i++)
		{
			int val = minimax(depth + 1, nodeIndex * 2 + i,
							false, values, alpha, beta);
            best = (int) fmax(best, val);
            alpha = (int) fmax(alpha, best);

			// Alpha Beta Pruning
			if (beta <= alpha)
				break;
		}
		return best;
	}
	else
	{
		int best = max;

		// Recur for left and
		// right children
		for (int i = 0; i < 2; i++)
		{
			
			int val = minimax(depth + 1, nodeIndex * 2 + i,
							true, values, alpha, beta);
            best = (int) fmin(best, val);
            beta = (int) fmin(beta, best);

			// Alpha Beta Pruning
			if (beta <= alpha)
				break;
		}
		return best;
	}
    return 0;
}


/*
    IA qui joue avec la strategie min-max
*/
int ia2(char (*grille2)[MAX_COLONNE], char signe){
    
    int max = (int) INFINITY;
    int min = (int) -INFINITY;

    int r;
    // Driver Code
    int values[8]={3, 5, 6, 9, 1, 2, 0, -1};
    printf("The optimal value is : %d", minimax(0, 0, true, values, min, max));
    
    return 0;
}
    
