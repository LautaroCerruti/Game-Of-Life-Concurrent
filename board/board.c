#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>

#include "board.h"

int board_init(board_t *board, size_t col, size_t row) {
    unsigned int i = 0;
    int falla = 0;

    board->col = col;
    board->row = row;

    board->cell = malloc(sizeof(char*) * row);

    if (!(board->cell)) {
        free(board);
        return 1;
    }
    
    for (; i < row; ++i) {
        board->cell[i] = malloc(sizeof(char) * col);
        if (!(board->cell)) {
            falla = 1;
            break;
        }
    }

    if (falla) {
        for (; i > 0; --i)
            free(board->cell[i]);
        free(board->cell);
        return 1;
    }

    return 0;
}

char board_get(board_t board, unsigned int col, unsigned int row) {
    if (col >= board.col || row >= board.row)
        return ' ';

    return board.cell[row][col];
}

char board_get_round(board_t board, int col, int row) {
    int i = row >= 0 ? row % (int) board.row : (row >= -((int) board.row)) ? (int) board.row + row : (-(row + (int) board.row)) % (int) board.row;

    int j = col >= 0 ? col % (int) board.col : (col >= -((int) board.col)) ? (int) board.col + col : (-(col + (int) board.col)) % (int) board.col;

    return board.cell[i][j];
}

int board_set(board_t board, unsigned int col, unsigned int row, char val) {
    if (col >= board.col || row >= board.row)
        return 1;

    board.cell[row][col] = val;

    return 0;
}

int digits_of_int(unsigned int n) {
    int count = 0;
    while (n != 0) {
        n /= 10;     
        ++count;
    }
    return count;
}

int board_load_row(board_t *board, char *str, unsigned int row) {
    unsigned int j, mult, pos = 0;
    int falla = 0;
    char val;
    while (sscanf(str, " %d%c", &mult, &val) == 2) {
        for (j = 0; j < mult; ++j) {
            falla = board_set(*board, pos, row, val);
            if (falla)
                break;
            ++pos;
        }
        if (falla)
            break;
        str += digits_of_int(mult) + 1;
        if (*str == '\n' || *str == '\0') {
            falla = (pos != board->col);
            if (falla)
                break;
        }
    }
    return falla;
}

void intToString(int val, char *res) {
    int digits = digits_of_int(val), i = 0, pot;

    for (; i < digits; ++i) {
        pot = (int) (pow(10, digits - i - 1));
        *(res + i) = 48 + (val / pot);
        val -= (val / pot) * pot;
    }

    *(res + i) = '\0';
}

void board_show(board_t board, char *res) {
    unsigned int i = 0, j, mult;
    char actual, *aux = res, *aux2 = malloc(sizeof(char) * (digits_of_int(board.col) + 1));
    for (; i < board.row; ++i) {
        mult = 0;
        actual = board.cell[i][0];
        for (j = 0; j < board.col; ++j) {
            if (actual != board.cell[i][j]) {
                intToString(mult, aux2);
                strcpy(aux, aux2);
                aux += digits_of_int(mult);
                *(aux) = actual;
                ++aux;
                actual = board.cell[i][j];
                mult = 1;
            } else
                ++mult;
        }
        
        intToString(mult, aux2);
        strcpy(aux, aux2);
        aux += digits_of_int(mult);
        *(aux) = actual;
        *(aux + 1) = '\n';
        aux += 2;
    }
    *(aux) = '\0';
}

void board_destroy(board_t *board) {
    if (board) {
        for (unsigned int i = 0; i < board->row; ++i)
            free(board->cell[i]);
        free(board->cell);
        free(board);
    }
}
