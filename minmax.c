#include <stdbool.h>
#include "gomoku.h"
#include <limits.h>
#include <stdlib.h>
#include <time.h>

void nuissance(int GRID_SIZE, char grid[GRID_SIZE][GRID_SIZE], char adversaire, int directions[4][2], int* score);
void midgame(int GRID_SIZE,char grid[GRID_SIZE][GRID_SIZE],char adversaire,int directions[4][2],int * score);

int ia_de_fou(int GRID_SIZE,char grid[GRID_SIZE][GRID_SIZE],char symbol){
    // IA naive, joue aléatoirement.
    return 0;
}

bool isNear(int GRID_SIZE, char grid[GRID_SIZE][GRID_SIZE], int row, int col) {
    for (int i = -3; i <= 3; i++){
        for (int j = -1; j <= 1; j++){
            if (i == 0 && j == 0) continue;
            int x = row + i;
            int y = col + j;
            if (x >= 0 && x < GRID_SIZE && y >= 0 && y < GRID_SIZE && grid[x][y] != EMPTY_CELL) {
                return true;
            }
        }
    }
    return false;
}

// void midgame(int GRID_SIZE,char grid[GRID_SIZE][GRID_SIZE],int* count,int *open,int * blocked,char adversaire,int directions[4][2],int * score)
int eval(int GRID_SIZE, char grid[GRID_SIZE][GRID_SIZE], char symbol, int turn) {
    int score = 0;
    char adversaire = (symbol == PLAYER1) ? PLAYER2 : PLAYER1;
    int count, open, blocked;
    int directions[4][2] = {{0, 1}, {1, 0}, {1, 1}, {-1, 1}};

	if (turn < 10) { // debut departie
        int centre = GRID_SIZE / 2;
        for (int i = -2; i <= 2; i++){
            for (int j = -2; j <= 2; j++){
                if (grid[centre + i][centre + j] == symbol){
                    score += 7;
                }
            }
        }}
		else{  //phase de milieu et fin de jeu
        //prioriser le blocage et la création de menaces
			midgame(GRID_SIZE,grid,adversaire,directions,&score);
    }

    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            if (grid[i][j] == symbol || grid[i][j] == adversaire){
                for (int d = 0; d < 4; d++) {
                    int dx = directions[d][0];
                    int dy = directions[d][1];
                    count = 0;
                    open = 0;
                    blocked = 0;

                    for (int k = 0; k < 5; k++) {
                        int x = i + k * dx;
                        int y = j + k * dy;

                        if (!isValid(x, y, GRID_SIZE, grid)) break;
                        if (grid[x][y] == grid[i][j]){
                            count++;
                        } else if (grid[x][y] == EMPTY_CELL){
                            open++;
                            if (open > 1) break;
                        } else {
                            blocked++;
                            if (blocked > 1) break;
                        }

					}
					// if (count > 0 && grid[i][j] == symbol){  // inciter l'ia a jouer près de ses pions et pas juste emmerder l'adversaire
					// 		score+= 5*count;}


	nuissance(GRID_SIZE, grid, adversaire, directions, &score);
                }
            }
        }
    }
    // Évaluation dynamique basée sur le nombre de tour, pour une raison que jenecomprend pas, si elle ne dure pas toute la partie, l'ia ne fonctionne pascorrectement???
	// 09/12/13, problème corriger, le problème était la façon dont j'evaluais les coups
    return score;
}



int minimax(int GRID_SIZE, char grid[GRID_SIZE][GRID_SIZE], int depth, bool isMax, char player, int* bestRow, int* bestCol,int turn) {
    if (depth == 0){
        return eval(GRID_SIZE, grid, player,turn);
    }

    if (isMax){
        int maxEval = INT_MIN;
        for (int row = 0; row < GRID_SIZE; row++){
            for (int col = 0; col < GRID_SIZE; col++){
                if (grid[row][col] == EMPTY_CELL && isNear(GRID_SIZE, grid, row, col)){
                    grid[row][col] = player;
                    int eval = minimax(GRID_SIZE, grid, depth - 1, false, player, bestRow, bestCol,turn);
                    grid[row][col] = EMPTY_CELL;
                    if (eval > maxEval || (eval == maxEval && rand() % 11 > 0)){
                        maxEval = eval;
                        *bestRow = row;
                        *bestCol = col;
                    }
                }
            }
        }
		// printf("\nmax:%d",maxEval);
        return maxEval;
    } else{
        int minEval = INT_MAX;
        for (int row = 0; row < GRID_SIZE; row++){
            for (int col = 0; col < GRID_SIZE; col++){
                if (grid[row][col] == EMPTY_CELL && isNear(GRID_SIZE, grid, row, col)){
                    grid[row][col] = (player == PLAYER1) ? PLAYER2 : PLAYER1;
                    int eval = minimax(GRID_SIZE, grid, depth - 1, true, player, bestRow, bestCol,turn);
                    grid[row][col] = EMPTY_CELL;
                    if (eval < minEval|| (eval == minEval && rand() % 11 > 0)){
                        minEval = eval;
                        *bestRow = row;
                        *bestCol = col;
                    }
                }
            }
        }
		// printf("\nmin:%d",minEval);
        return minEval;
    }
}

int elage(int GRID_SIZE, char grid[GRID_SIZE][GRID_SIZE], int depth, bool isMax, char player, int* bestRow, int* bestCol, int turn, int alpha, int beta) {
    if (depth == 0) {
        return eval(GRID_SIZE, grid, player, turn);
    }

    if (isMax) {
        int maxEval = INT_MIN;
        for (int row = 0; row < GRID_SIZE; row++) {
            for (int col = 0; col < GRID_SIZE; col++) {
                if (grid[row][col] == EMPTY_CELL && isNear(GRID_SIZE, grid, row, col)) {
                    grid[row][col] = player;
                    int eval = elage(GRID_SIZE, grid, depth - 1, false, player, bestRow, bestCol, turn, alpha, beta);
                    grid[row][col] = EMPTY_CELL;

                    if (eval > maxEval || (eval == maxEval && rand() % 11 > 0)) {
                        maxEval = eval;
                        *bestRow = row;
                        *bestCol = col;
                    }

					alpha = (alpha > maxEval) ? alpha : maxEval;
					if (beta <= alpha)
    					break;
                }
            }
            if (beta <= alpha)
                break;
        }
        return maxEval;
    } else {
        int minEval = INT_MAX;
        for (int row = 0; row < GRID_SIZE; row++) {
            for (int col = 0; col < GRID_SIZE; col++) {
                if (grid[row][col] == EMPTY_CELL && isNear(GRID_SIZE, grid, row, col)) {
                    grid[row][col] = (player == PLAYER1) ? PLAYER2 : PLAYER1;
                    int eval = elage(GRID_SIZE, grid, depth - 1, true, player, bestRow, bestCol, turn, alpha, beta);
                    grid[row][col] = EMPTY_CELL;

                    if (eval < minEval || (eval == minEval && rand() % 11 > 0)) {
                        minEval = eval;
                        *bestRow = row;
                        *bestCol = col;
                    }

					beta = (beta < minEval) ? beta : minEval;
					if (beta <= alpha)
						break;
                }
            }
            if (beta <= alpha)
                break;
        }
        return minEval;
    }
}


void midgame(int GRID_SIZE,char grid[GRID_SIZE][GRID_SIZE],char adversaire,int directions[4][2],int * score){
        int count = 0;
	    int open = 0;
        int blocked = 0;
		for (int i = 0; i < GRID_SIZE; i++){
            for (int j = 0; j < GRID_SIZE; j++){
                if (grid[i][j] == adversaire){
                    for (int d = 0; d < 4; d++){
                        int dx = directions[d][0];
                        int dy = directions[d][1];


                        for (int k = 0; k < 5; k++){
                            int x = i + k * dx;
                            int y = j + k * dy;

                            if (!isValid(x, y, GRID_SIZE, grid))
								break;

                            if (grid[x][y] == grid[i][j]){
                                count++;
                            } else if (grid[x][y] == EMPTY_CELL){
                                open++;
                            } else{
                                blocked++;
                            }
                        }

                        if (count >= 3 && open >= 1){
                            score += 100 * (count);
                        }
                    }
                }
            }
        }
}
void nuissance(int GRID_SIZE, char grid[GRID_SIZE][GRID_SIZE], char adversaire, int directions[4][2], int* score) {
    int count;
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            if (grid[i][j] == adversaire) {
                for (int d = 0; d < 4; d++) {
                    count = 1;
                    int dx = directions[d][0];
                    int dy = directions[d][1];


                    int x = i + dx;
                    int y = j + dy;
                    while (x >= 0 && x < GRID_SIZE && y >= 0 && y < GRID_SIZE && grid[x][y] == adversaire) {
                        count++;
                        x += dx;
                        y += dy;
                    }

                    // direction opposé a la précédente
                    x = i - dx;
                    y = j - dy;
                    while (x >= 0 && x < GRID_SIZE && y >= 0 && y < GRID_SIZE && grid[x][y] == adversaire) {
                        count++;
                        x -= dx;
                        y -= dy;
                    }


                    if (count >= 4) {
                        *score -= 100;
                    } else if (count == 3) {
                        *score -= 50;
                    } else if (count == 2) {
                        *score -= 5;
                    }
                }
            }
        }
    }
}
