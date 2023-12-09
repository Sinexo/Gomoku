#include <stdbool.h>
#include "gomoku.h"
#include <math.h>
#include <limits.h>

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


int eval(int GRID_SIZE, char grid[GRID_SIZE][GRID_SIZE], char symbol, int turn) {
    int score = 0;
    char adversaire = (symbol == PLAYER1) ? PLAYER2 : PLAYER1;
    int count, open, blocked;
    int directions[4][2] = {{0, 1}, {1, 0}, {1, 1}, {-1, 1}};

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

    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++){
            if (grid[i][j] == adversaire) {
                for (int d = 0; d < 4; d++) {
                    count = 1; // Compte le nombre de pièces consécutives
                    int dx = directions[d][0];
                    int dy = directions[d][1];

                    // Comptez vers une direction
                    int x = i + dx;
                    int y = j + dy;
                    while (x >= 0 && x < GRID_SIZE && y >= 0 && y < GRID_SIZE && grid[x][y] == adversaire){
                        count++;
                        x += dx;
                        y += dy;
                    }

                    // Comptez dans la direction opposée
                    x = i - dx;
                    y = j - dy;
                    while (x >= 0 && x < GRID_SIZE && y >= 0 && y < GRID_SIZE && grid[x][y] == adversaire){
                        count++;
                        x -= dx;
                        y -= dy;
                    }

                    // Attribuer un score négatif en fonction du nombre de pièces consécutives
                    if (count >= 4){
                        score -= 100; // Score négatif important si l'adversaire a 4 pièces en ligne
                    } else if (count == 3){
                        score -= 50; // Score négatif moins important pour 3 pièces
                    }
                }
            }
        }
    }
                }
            }
        }
    }
    // Évaluation dynamique basée sur le nombre de tour, pour une raison que jenecomprend pas, si elle ne dure pas toute la partie, l'ia ne fonctionne pascorrectement???
	// 09/12/13, problème corriger, le problème était la façon dont j'evaluais les coups
	if (turn < 7) {  // debut departie
        int centre = GRID_SIZE / 2;
        for (int i = -1; i <= 1; i++){
            for (int j = -1; j <= 1; j++){
                if (grid[centre + i][centre + j] == symbol){
                    score += 5;
                }
            }
        }}
		else{  // Phase de milieu et fin de jeu
        // Prioriser le blocage et la création de menaces
        for (int i = 0; i < GRID_SIZE; i++){
            for (int j = 0; j < GRID_SIZE; j++){
                if (grid[i][j] == adversaire){
                    for (int d = 0; d < 4; d++){
                        int dx = directions[d][0];
                        int dy = directions[d][1];
                        count = 0;
                        open = 0;
                        blocked = 0;

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
                            score += 100 * count;
                        }
                    }
                }
            }
        }
    }
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
                    if (eval > maxEval){
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
                    if (eval < minEval){
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
