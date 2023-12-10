#include <stdio.h>
#include <stdbool.h>
#include "gomoku.h"
#include "minmax.h"
#include "time.h"

int main() {
    int GRID_SIZE = 0;
    int choix;

    printf("Veuillez choisir votre mode de jeu : \n1. PvP \n2. PvE \n3. IAvsIA\n4. PvE avec élagage \n5. IAvsIA avec élagage\n");
    scanf("%d", &choix);

	printf("choissisez la taille du plateau (taille*taille)");
	scanf("%d", &GRID_SIZE);

	if (GRID_SIZE<15){
		printf("Plateau trop petit, la taille classique sera choisi automatiquement");
		GRID_SIZE = 19;
	}
	char grid[GRID_SIZE][GRID_SIZE];

    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            grid[i][j] = EMPTY_CELL;
        }
    }
	srand(time(NULL));
    switch (choix) {
        case 1:
            play_pvp(GRID_SIZE, grid);
            break;
        case 2:
            play_pve(GRID_SIZE, grid);
            break;
        case 3:
            play_eve(GRID_SIZE, grid);
            break;
        case 4:
            play_pve_elage(GRID_SIZE, grid);
            break;
        case 5:
            play_eve_elage(GRID_SIZE, grid);
            break;
        default:
            printf("Choix non valide. Veuillez choisir un mode de jeu valide.\n");
            break;
    }

    return 0;
}
