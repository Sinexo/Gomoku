#include <stdio.h>
#include <stdbool.h>
#include "gomoku.h"
#include "minmax.h"


int main() {
	int GRID_SIZE = 19; //min 15 max infini ?
    char grid[GRID_SIZE][GRID_SIZE];
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            grid[i][j] = EMPTY_CELL;
        }
    }

	// play_pvp(GRID_SIZE,grid);
	play_pve(GRID_SIZE,grid);
    return 0;
}
