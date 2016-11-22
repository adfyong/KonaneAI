#include <stdint.h>
#include <stdio.h>

#define IS_BLACK(i) ((((i/8) % 2) && (i % 2)) || (!((i/8) % 2) && !(i % 2)))

int count_movable(uint64_t board) {
	printf("%x\n", board);
	int w_movable = 0;
	int b_movable = 0;
	for (int i = 0; i < 64; ++i) {
		if (!(board & (1 << i)))
			// bit is unset
			continue;

		// up
		if (i < 48 && (board & (1 << (i+8))) && !(board & (1 << (i+16)))) {
			IS_BLACK(i) ? b_movable++ : w_movable++;
			continue;
		}

		// down
		if (i > 15 && (board & (1 << (i-8))) && !(board & (1 << (i-16)))) {
			IS_BLACK(i) ? b_movable++ : w_movable++;
			continue;
		}

		// right
		if ((i%8 > 1) && (board & (1 << (i-1))) && !(board & (1 << (i-2)))) {
			IS_BLACK(i) ? b_movable++ : w_movable++;
			continue;
		}

		// left
		if ((i%8 < 5) && (board & (1 << (i+1))) && !(board & (1 << (i+2)))) {
			IS_BLACK(i) ? b_movable++ : w_movable++;
			continue;
		}
	}

	printf("Movable black pieces: %d\n", b_movable);
	printf("Movable white pieces: %d\n", w_movable);
	return b_movable - w_movable;
}
