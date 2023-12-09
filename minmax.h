#ifndef MINMAX_H
#define MINMAX_H


#include <stdbool.h>
#include "gomoku.h"
#include <math.h>


int ia_de_fou(int GRID_SIZE,char grid[GRID_SIZE][GRID_SIZE],char symbol);
bool isNear(int GRID_SIZE, char grid[GRID_SIZE][GRID_SIZE], int row, int col);
int eval(int GRID_SIZE, char grid[GRID_SIZE][GRID_SIZE], char symbol,int turn);
int minimax(int GRID_SIZE, char grid[GRID_SIZE][GRID_SIZE], int depth, bool isMax, char player,int* bestRow,int* bestCol,int turn);

#endif