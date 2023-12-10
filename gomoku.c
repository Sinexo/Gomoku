#include <stdio.h>
#include <stdbool.h>
#include "minmax.h"
#include "limits.h"

//#define GRID_SIZE 15
#define EMPTY_CELL '.'
#define PLAYER1 'N'
#define PLAYER2 'B'

// typedef struct Move{
// 	int score;
// 	int row;
// 	int col;
// }Move;


void printGrid(int GRID_SIZE, char grid[GRID_SIZE][GRID_SIZE]){
	for (int i = 0; i < GRID_SIZE; i++)
	{
		for (int j = 0; j < GRID_SIZE; j++)
		{
			if (grid[i][j] == 'N')
				printf("\033[1;30m%c\033[1;0m ", grid[i][j]);
			else
				printf("%c ", grid[i][j]);
		}
		printf("\n");
	}
}

bool checkWin(int GRID_SIZE, char grid[GRID_SIZE][GRID_SIZE], int row, int col, char symbol){
	int directions[4][2] = {{1, 0}, {0, 1}, {1, 1}, {1, -1}};
	for (int i = 0; i < 4; i++){
		int count = 1;
		int dx = directions[i][0], dy = directions[i][1];
		int x = row + dx, y = col + dy;
		while (x >= 0 && x < GRID_SIZE && y >= 0 && y < GRID_SIZE && grid[x][y] == symbol){
			count++;
			x += dx;
			y += dy;
		}
		x = row - dx;
		y = col - dy;
		while (x >= 0 && x < GRID_SIZE && y >= 0 && y < GRID_SIZE && grid[x][y] == symbol){
			count++;
			x -= dx;
			y -= dy;
		}
		if (count >= 5)
			return true;
	}
	return false;
}

bool isValid(int row, int col, int GRID_SIZE, char grid[GRID_SIZE][GRID_SIZE]){
	if (row < 0 || row >= GRID_SIZE || col < 0 || col >= GRID_SIZE || grid[row][col] != EMPTY_CELL){
		return false;
	}
	return true;
}

//Faudrait ajouter des vérification pour être sûr que l'user entre bien  les coordonées de la bonne façon ou du bon type
void play_pvp(int GRID_SIZE, char grid[GRID_SIZE][GRID_SIZE]){
	int turn = 1;
	int row, col;
	bool game_over = false;
	int PionJ1 = 60, PionJ2 = 60;

	while (!game_over){
		printGrid(GRID_SIZE, grid);
		printf("Tour :%d\n", turn);
		printf("Au tour du Joueur %d (entrer dans cette ordre : Ligne, Colonne ): ", turn % 2+1);
		scanf("%d %d", &row, &col);

		if (turn == 1 && (row != GRID_SIZE / 2 || col != GRID_SIZE / 2)){
			printf(" \033[1;31m Le premier pion doit être jouer au centre, soit %d,%d\033[1;0m\n", GRID_SIZE / 2, GRID_SIZE / 2);
			continue;
		}

		if (!isValid(row, col, GRID_SIZE, grid)){
			printf("\033[1;31m Vous ne pouvez pas jouer ici.\033[1;0m\n");
			continue;
		}
		grid[row][col] = (turn % 2 == 0) ? PLAYER2 : PLAYER1;

		if (checkWin(GRID_SIZE, grid, row, col, grid[row][col])){
			printGrid(GRID_SIZE, grid);
			printf("\033[1;32m Le joueur %d remporte la partie !\033[1;0ms\n", turn % 2 + 1);
			game_over = true;
		}

		turn++;
		(turn % 2 == 0) ? PionJ1-- : PionJ2--;
		if (PionJ1 == 0 && PionJ2 == 0){
			printf("\033[1;32mPlus de pions,aucun joueur n'a gagné, Egalité !\033[1;0ms");
			game_over = true;
		}
	}
}

// jeu contre l'ia
void play_pve(int GRID_SIZE, char grid[GRID_SIZE][GRID_SIZE]) {
    bool game_over = false;
    int turn = 1;
    int row, col;
	int PionJ1 = 60,PionJ2=60, nbrPion=0;

    while (!game_over){
        printGrid(GRID_SIZE, grid);
        if (turn % 2 == 1) {
			//tour du joueur (Noir)
            printf("Votre tour (entrer dans cette ordre : Ligne, Colonne ): ");
            scanf("%d %d", &row, &col);

            if (turn == 1 && (row != GRID_SIZE / 2 || col != GRID_SIZE / 2)){
                printf("\033[1;31m Le premier pion doit être joué au centre, soit %d,%d\033[1;0m\n", GRID_SIZE / 2, GRID_SIZE / 2);
                continue;
            }

            if (!isValid(row, col, GRID_SIZE, grid)){
				printf("\033[1;31m Vous ne pouvez pas jouer ici.\033[1;0m\n");
                continue;
			}
            grid[row][col] = PLAYER1;
			nbrPion++;
            if (checkWin(GRID_SIZE, grid, row, col, PLAYER1)){
                printf("Félicitations ! Vous avez gagné.\n");
                game_over = true;
            }
        } else {
            // tour de l'ia (Blanc)
            printf("Tour de l'Ordinateur\n");
            int MoveRow, MoveCol;
            minimax(GRID_SIZE, grid, 3, false, PLAYER2, &MoveRow, &MoveCol,turn);
        	grid[MoveRow][MoveCol] = PLAYER2;
			nbrPion++;

            if (checkWin(GRID_SIZE, grid, MoveRow, MoveCol, PLAYER2)){
                printf("L'Ordinateur a gagné.\n");
                game_over = true;
            }
        }
        turn++;
		(turn % 2 == 0) ? PionJ1-- : PionJ2--;
		if (PionJ1 == 0 && PionJ2 == 0){
			printf("\033[1;32mPlus de pions,aucun joueur n'a gagné, Egalité !\033[1;0ms");
			game_over = true;
		}
    }
}

// jeu ia contre ia
void play_eve(int GRID_SIZE, char grid[GRID_SIZE][GRID_SIZE]){
    bool game_over = false;
    int turn = 1;
    // int row, col;
	int PionJ1 = 60,PionJ2=60;

    while (!game_over){
        printGrid(GRID_SIZE, grid);
        if (turn % 2 == 1) {
			//tour du joueur (Noir)
            printf("Tour de l'Ordinateur 1 \n");
            int MoveRowBlack, MoveColBlack;
			if (turn == 1)
				grid[GRID_SIZE/2][GRID_SIZE/2] = PLAYER1;
			else{
            minimax(GRID_SIZE, grid, 3, true, PLAYER1, &MoveRowBlack, &MoveColBlack,turn);
        	grid[MoveRowBlack][MoveColBlack] = PLAYER1;
			}
            if (checkWin(GRID_SIZE, grid, MoveRowBlack, MoveColBlack, PLAYER1)){
                printf("L'Ordinateur a gagné.\n");
                game_over = true;
            }
        }
        else {
            // tour de l'ia (Blanc)
            printf("Tour de l'Ordinateur 2 \n");
            int MoveRow, MoveCol;
            minimax(GRID_SIZE, grid, 3, false, PLAYER2, &MoveRow, &MoveCol,turn);
        	grid[MoveRow][MoveCol] = PLAYER2;

            if (checkWin(GRID_SIZE, grid, MoveRow, MoveCol, PLAYER2)){
                printf("L'Ordinateur a gagné.\n");
                game_over = true;
            }
        }
        turn++;
		(turn % 2 == 0) ? PionJ1-- : PionJ2--;
		if (PionJ1 == 0 && PionJ2 == 0){
			printf("\033[1;32mPlus de pions,aucun joueur n'a gagné, Egalité !\033[1;0ms");
			game_over = true;
		}
    }
}
void play_eve_elage(int GRID_SIZE, char grid[GRID_SIZE][GRID_SIZE]){
    bool game_over = false;
    int turn = 1;
    // int row, col;
	int PionJ1 = 60,PionJ2=60;

    while (!game_over){
        printGrid(GRID_SIZE, grid);
        if (turn % 2 == 1) {
			//tour du joueur (Noir)
            printf("Tour de l'Ordinateur 1 \n");
            int MoveRowBlack, MoveColBlack;
			if (turn == 1)
				grid[GRID_SIZE/2][GRID_SIZE/2] = PLAYER1;
			else{
            elage(GRID_SIZE, grid, 3, true, PLAYER1, &MoveRowBlack, &MoveColBlack,turn,INT_MIN,INT_MAX,3);
        	grid[MoveRowBlack][MoveColBlack] = PLAYER1;
			}
            if (checkWin(GRID_SIZE, grid, MoveRowBlack, MoveColBlack, PLAYER1)){
                printf("L'Ordinateur a gagné.\n");
                game_over = true;
            }
        }
        else {
            // tour de l'ia (Blanc)
            printf("Tour de l'Ordinateur 2 \n");
            int MoveRow, MoveCol;
            elage(GRID_SIZE, grid, 3, false, PLAYER2, &MoveRow, &MoveCol,turn,INT_MIN,INT_MAX,3);
        	grid[MoveRow][MoveCol] = PLAYER2;

            if (checkWin(GRID_SIZE, grid, MoveRow, MoveCol, PLAYER2)){
                printf("L'Ordinateur a gagné.\n");
                game_over = true;
            }
        }
        turn++;
		(turn % 2 == 0) ? PionJ1-- : PionJ2--;
		if (PionJ1 == 0 && PionJ2 == 0){
			printf("\033[1;32mPlus de pions,aucun joueur n'a gagné, Egalité !\033[1;0ms");
			game_over = true;
		}
    }
}

void play_pve_elage(int GRID_SIZE, char grid[GRID_SIZE][GRID_SIZE]) {
    bool game_over = false;
    int turn = 1;
    int row, col;
	int PionJ1 = 60,PionJ2=60, nbrPion=0;

    while (!game_over){
        printGrid(GRID_SIZE, grid);
        if (turn % 2 == 1) {
			//tour du joueur (Noir)
            printf("Votre tour (entrer dans cette ordre : Ligne, Colonne ): ");
            scanf("%d %d", &row, &col);

            if (turn == 1 && (row != GRID_SIZE / 2 || col != GRID_SIZE / 2)){
                printf("\033[1;31m Le premier pion doit être joué au centre, soit %d,%d\033[1;0m\n", GRID_SIZE / 2, GRID_SIZE / 2);
                continue;
            }

            if (!isValid(row, col, GRID_SIZE, grid)){
				printf("\033[1;31m Vous ne pouvez pas jouer ici.\033[1;0m\n");
                continue;
			}
            grid[row][col] = PLAYER1;
			nbrPion++;
            if (checkWin(GRID_SIZE, grid, row, col, PLAYER1)){
                printf("Félicitations ! Vous avez gagné.\n");
                game_over = true;
            }
        } else {
            // tour de l'ia (Blanc)
            printf("Tour de l'Ordinateur\n");
            int MoveRow, MoveCol;
            elage(GRID_SIZE, grid, 4, false, PLAYER2, &MoveRow, &MoveCol,turn,INT_MIN,INT_MAX,4);
        	grid[MoveRow][MoveCol] = PLAYER2;
			nbrPion++;

            if (checkWin(GRID_SIZE, grid, MoveRow, MoveCol, PLAYER2)){
                printf("L'Ordinateur a gagné.\n");
                game_over = true;
            }
        }
        turn++;
		(turn % 2 == 0) ? PionJ1-- : PionJ2--;
		if (PionJ1 == 0 && PionJ2 == 0){
			printf("\033[1;32mPlus de pions,aucun joueur n'a gagné, Egalité !\033[1;0ms");
			game_over = true;
		}
    }
}