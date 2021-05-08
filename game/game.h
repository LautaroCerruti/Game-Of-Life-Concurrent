#ifndef GAME_TYPES
#define GAME_TYPES

#include "../board/board.h"
#include "../barrier/barrier.h"

/******************************************************************************/
/* Representamos las células vivas como 'O' y las muertas como 'X' */

typedef enum State {ALIVE = 'O', DEAD = 'X'} State;
/******************************************************************************/
struct _game {
    unsigned int cycles;
    board_t *board;
};

typedef struct _game game_t;
/******************************************************************************/

/* Cargamos el juego desde un archivo */
game_t *loadGame(const char *filename);

/* Guardamos el tablero 'board' en el archivo 'filename' */
void writeBoard(board_t board, const char *filename);

/* Simulamos el Juego de la Vida de Conway con tablero 'board' la cantidad de
ciclos indicados en 'cycles' en 'nuprocs' unidades de procesamiento*/
board_t *conwayGoL(board_t *board, unsigned int cycles, const int nuproc);

/* Destruimos el Game */
void destroyGame(game_t *game);

#endif
