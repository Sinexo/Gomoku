#ifndef MOVE_H
#define MOVE_H

typedef struct Move {
    int row;
    int col;
}Move;

void addMove(struct Move moves[], int* numMoves, int row, int col);
#endif
