#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BOARD_SIZE 8
#define MAX_MOVES 512

// Chess piece types
typedef enum {
    EMPTY, PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING
} Piece;

// Piece colors
typedef enum {
    WHITE, BLACK
} Color;

// Structure to represent a chessboard square
typedef struct {
    Piece piece;
    Color color;
} Square;

// Structure to represent a move
typedef struct {
    int startRow, startCol;
    int endRow, endCol;
    char moveStr[6]; 
} Move;

Square board[BOARD_SIZE][BOARD_SIZE];
Move moves[MAX_MOVES];
int moveCount = 0;

void initBoard() {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i][j].piece = EMPTY;
        }
    }

    board[0][0].piece = board[0][7].piece = ROOK;
    board[0][1].piece = board[0][6].piece = KNIGHT;
    board[0][2].piece = board[0][5].piece = BISHOP;
    board[0][3].piece = QUEEN;
    board[0][4].piece = KING;

    for (int i = 0; i < BOARD_SIZE; i++) {
        board[1][i].piece = PAWN;
    }

    board[7][0].piece = board[7][7].piece = ROOK;
    board[7][1].piece = board[7][6].piece = KNIGHT;
    board[7][2].piece = board[7][5].piece = BISHOP;
    board[7][3].piece = QUEEN;
    board[7][4].piece = KING;

    for (int i = 0; i < BOARD_SIZE; i++) {
        board[6][i].piece = PAWN;
    }
}

int algebraicToIndex(char file, int rank) {
    return (BOARD_SIZE - rank) * BOARD_SIZE + (file - 'a');
}

int parseMove(char *moveStr, Color color) {
    if (strlen(moveStr) != 4) {
        return 0;
    }

    int startCol = moveStr[0] - 'a';
    int startRow = '8' - moveStr[1];
    int endCol = moveStr[2] - 'a';
    int endRow = '8' - moveStr[3];

    if (startRow < 0 || startRow >= BOARD_SIZE || startCol < 0 || startCol >= BOARD_SIZE ||
        endRow < 0 || endRow >= BOARD_SIZE || endCol < 0 || endCol >= BOARD_SIZE) {
        return 0;
    }

    board[endRow][endCol].piece = board[startRow][startCol].piece;
    board[startRow][startCol].piece = EMPTY;

    // Save the move to the moves array
    moves[moveCount].startRow = startRow;
    moves[moveCount].startCol = startCol;
    moves[moveCount].endRow = endRow;
    moves[moveCount].endCol = endCol;
    snprintf(moves[moveCount].moveStr, 6, "%c%c%c%c", moveStr[0], moveStr[1], moveStr[2], moveStr[3]);

    moveCount++;

    return 1;
}

void savePGN(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Could not open file for writing.\n");
        return;
    }

    fprintf(file, "[Event \"Chess Game\"]\n");
    fprintf(file, "[Site \"Local\"]\n");
    fprintf(file, "[Date \"2025.03.22\"]\n");
    fprintf(file, "[Round \"1\"]\n");
    fprintf(file, "[White \"Player1\"]\n");
    fprintf(file, "[Black \"Player2\"]\n");
    fprintf(file, "\n");

    for (int i = 0; i < moveCount; i++) {
        fprintf(file, "%s ", moves[i].moveStr);
        if ((i + 1) % 2 == 0) {
            fprintf(file, "\n");
        }
    }

    fclose(file);
}

void printBoard() {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            char piece = ' ';
            switch (board[i][j].piece) {
                case PAWN: piece = 'P'; break;
                case KNIGHT: piece = 'N'; break;
                case BISHOP: piece = 'B'; break;
                case ROOK: piece = 'R'; break;
                case QUEEN: piece = 'Q'; break;
                case KING: piece = 'K'; break;
                case EMPTY: piece = '.'; break;
            }
            printf("%c ", piece);
        }
        printf("\n");
    }
}

int main() {
    initBoard();

    char moveStr[6];
    while (1) {
        printf("Enter move (e.g., e2e4): ");
        scanf("%s", moveStr);

        if (strcmp(moveStr, "exit") == 0) {
            break;
        }

        static Color currentColor = WHITE;
        if (parseMove(moveStr, currentColor)) {
            printBoard();
            currentColor = (currentColor == WHITE) ? BLACK : WHITE;
        } else {
            printf("Invalid move. Try again.\n");
        }
    }

    savePGN("game.pgn");

    return 0;
}
