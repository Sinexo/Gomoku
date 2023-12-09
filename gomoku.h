#ifndef GOMOKU_H
#define GOMOKU_H

#include <stdio.h>
#include <stdbool.h>
#include "minmax.h"

#define EMPTY_CELL '.'
#define PLAYER1 'N'
#define PLAYER2 'B'

void printGrid(int GRID_SIZE, char grid[GRID_SIZE][GRID_SIZE]);
bool checkWin(int GRID_SIZE, char grid[GRID_SIZE][GRID_SIZE], int row, int col, char symbol);
bool isValid(int row,int col, int GRID_SIZE, char grid[GRID_SIZE][GRID_SIZE]);
void play_pvp(int GRID_SIZE,char grid[GRID_SIZE][GRID_SIZE]);
void play_pve(int GRID_SIZE, char grid[GRID_SIZE][GRID_SIZE]);

#endif
