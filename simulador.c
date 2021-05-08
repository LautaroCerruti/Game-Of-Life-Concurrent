#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/sysinfo.h>
#include <assert.h>

#include "./game/game.h"

int main(int argc, char **argv) {
    char *str = malloc(sizeof(char) * strlen(*(argv + 1)));
    game_t *game;

    if (argc < 2)
        return 0;

    if (strcmp(strchr(*(argv + 1), '.'), ".game")) {
        printf("Nombre de archivo erroneo\n");
        return 0;
    }

    game = loadGame(*(argv + 1));

    str = strtok(*(argv + 1), ".");

    strcat(str, ".final");

    assert(game != NULL);

    game->board = conwayGoL(game->board, game->cycles, get_nprocs());

    assert(game->board != NULL);

    writeBoard(*(game->board), str);

    destroyGame(game);

    return 0;
}