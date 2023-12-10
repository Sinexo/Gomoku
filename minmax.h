#ifndef MINMAX_H
#define MINMAX_H


#include <stdbool.h>
#include "gomoku.h"
#include <math.h>
#include <stdlib.h>
#include <time.h>

void midgame(int GRID_SIZE,char grid[GRID_SIZE][GRID_SIZE],char adversaire,int directions[4][2],int * score);
void nuissance(int GRID_SIZE, char grid[GRID_SIZE][GRID_SIZE], char adversaire, int directions[4][2], int* score);
int ia_de_fou(int GRID_SIZE,char grid[GRID_SIZE][GRID_SIZE],char symbol);
bool isNear(int GRID_SIZE, char grid[GRID_SIZE][GRID_SIZE], int row, int col);
int eval(int GRID_SIZE, char grid[GRID_SIZE][GRID_SIZE], char symbol,int turn);
int minimax(int GRID_SIZE, char grid[GRID_SIZE][GRID_SIZE], int depth, bool isMax, char player,int* bestRow,int* bestCol,int turn);
int elage(int GRID_SIZE, char grid[GRID_SIZE][GRID_SIZE], int depth, bool isMax, char player, int* bestRow, int* bestCol, int turn, int alpha, int beta);

#endif