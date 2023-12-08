#include <stdbool.h>
#include "gomoku.h"
#include <math.h>
#include <limits.h>
#include "move.h"


int ia_de_fou(int GRID_SIZE,char grid[GRID_SIZE][GRID_SIZE],char symbol){
	//IA naive, joue aléatoirement.
	return 0;
}
// Fonction qui évalue le plateau

bool isNear(int GRID_SIZE, char grid[GRID_SIZE][GRID_SIZE], int row, int col) {
    for (int i = -2; i <= 2; i++) {
        for (int j = -2; j <= 2; j++) {
            int x = row + i;
            int y = col + j;
            if (x >= 0 && x < GRID_SIZE && y >= 0 && y < GRID_SIZE && grid[x][y] != EMPTY_CELL) {
                return true;
            }
        }
    }
    return false;
}

int eval(int GRID_SIZE, char grid[GRID_SIZE][GRID_SIZE], char symbol) {
    int score = 0;
    char adversaire = (symbol == PLAYER1) ? PLAYER2 : PLAYER1;
    int count, open, blocked;
    int directions[4][2] = {{0, 1}, {1, 0}, {1, 1}, {-1, 1}};

    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            if (grid[i][j] == symbol || grid[i][j] == adversaire) {
				// if (!isNear(GRID_SIZE, grid, i, j))// pour soulager le processeur, les case avec + de 3 case vide avant un pions sont ignoré, ça limite forcément un peu les possibilité d ejeu mais en théorie ça augmente grandement le temps d'exéc 
				// 	continue;
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

                        if (grid[x][y] == grid[i][j]) {
                            count++;
                        } else if (grid[x][y] == EMPTY_CELL) {
                            open++;
                            break;
                        } else {
                            blocked++;
                            break;
                        }
                    }

                    if (count > 0) {
                        int sequence_score = 0;
                        switch (count) {
                            case 1: sequence_score = 1; break;
                            case 2: sequence_score = 10; break;
                            case 3: sequence_score = open > 0 ? 200 : 100; break;
                            case 4: sequence_score = (open > 0) ? 2000 : 1000; break;
                            case 5: sequence_score = 10000; break;
                        }

                        if (blocked == 2) sequence_score /= 2;

                        score += (grid[i][j] == symbol) ? sequence_score : -sequence_score;
                    }
                }
            }
        }
    }

    return score;
}
// minmax sans élagage alpha-beta

int minimax(int GRID_SIZE, char grid[GRID_SIZE][GRID_SIZE], int depth, bool isMax, char player, int* bestRow, int* bestCol, Move *liste, int numCoupValide) {
    if (depth == 0) {
        return eval(GRID_SIZE, grid, player);
    }

    if (isMax) {
        int maxEval = INT_MIN;
        for (int i = 0; i < numCoupValide; i++) {
            int row = liste[i].row;
            int col = liste[i].col;
            if (grid[row][col] == EMPTY_CELL) {
                grid[row][col] = player;
                int eval = minimax(GRID_SIZE, grid, depth - 1, false, player, bestRow, bestCol, liste, numCoupValide);
                grid[row][col] = EMPTY_CELL;
                if (eval > maxEval) {
                    maxEval = eval;
                    *bestRow = row;
                    *bestCol = col;
                }
            }
        }
        return maxEval;
    } else {
        int minEval = INT_MAX;
        for (int i = 0; i < numCoupValide; i++) {
            int row = liste[i].row;
            int col = liste[i].col;
            if (grid[row][col] == EMPTY_CELL) {
                grid[row][col] = (player == PLAYER1) ? PLAYER2 : PLAYER1;
                int eval = minimax(GRID_SIZE, grid, depth - 1, true, player, bestRow, bestCol, liste, numCoupValide);
                grid[row][col] = EMPTY_CELL;
                if (eval < minEval) {
                    minEval = eval;
                    *bestRow = row;
                    *bestCol = col;
                }
            }
        }
        return minEval;
    }
}





