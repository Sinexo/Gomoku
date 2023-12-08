struct Move{
    int row;
    int col;
} Move;

void addMove(struct Move moves[], int* numMoves, int row, int col) {
    moves[*numMoves].row = row;
    moves[*numMoves].col = col;
    (*numMoves)++;
}