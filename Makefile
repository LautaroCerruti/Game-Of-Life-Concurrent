all: programa

programa: board.o barrier.o game.o
	gcc -Wall -Wextra -Werror -pthread -g -std=c99 -o simulador simulador.c board.o barrier.o game.o -lm

board.o: ./board/board.c
	gcc -Wall -Wextra -Werror -pthread -g -std=c99 -c ./board/board.c -lm

barrier.o: ./barrier/barrier.c
	gcc -Wall -Wextra -Werror -pthread -g -std=c99 -c ./barrier/barrier.c -lm

game.o: ./game/game.c
	gcc -Wall -Wextra -Werror -pthread -g -std=c99 -c ./game/game.c -lm

clean:
	rm -f programa *.o
