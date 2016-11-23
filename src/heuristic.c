#include <stdint.h>
#include <stdio.h>
#include <inttypes.h>

#define IS_BLACK(i) ((((i/8) % 2) && (i % 2)) || (!((i/8) % 2) && !(i % 2)))

int count_movable(uint64_t board) {
	int w_movable = 0;
	int b_movable = 0;
	uint64_t o = 1; // a 64-bit version of 1 so we can shift it
#ifdef DEBUG
	fprintf(stderr, "Heuristic analyzing ");
	printf("%" PRIx64 "\n", board);
#endif
	for (int i = 0; i < 64; ++i) {
		if (!(board & (1 << i)))
			// bit is unset
			continue;

		// up
		if (i < 48 && (board & (o << (i+8))) && !(board & (o << (i+16)))) {
			IS_BLACK(i) ? b_movable++ : w_movable++;
			continue;
		}

		// down
		if (i > 15 && (board & (o << (i-8))) && !(board & (o << (i-16)))) {
			IS_BLACK(i) ? b_movable++ : w_movable++;
			continue;
		}

		// right
		if ((i%8 > 1) && (board & (o << (i-1))) && !(board & (o << (i-2)))) {
			IS_BLACK(i) ? b_movable++ : w_movable++;
			continue;
		}

		// left
		if ((i%8 < 5) && (board & (o << (i+1))) && !(board & (o << (i+2)))) {
			IS_BLACK(i) ? b_movable++ : w_movable++;
			continue;
		}
	}
#ifdef DEBUG
	fprintf(stderr, "Movable black pieces: %d\n", b_movable);
	fprintf(stderr, "Movable white pieces: %d\n", w_movable);
#endif
	return b_movable - w_movable;
}
