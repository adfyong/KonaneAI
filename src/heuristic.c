#include <stdint.h>
#include <stdio.h>
#include <inttypes.h>

#include "board.h"

static int black = 1;

void initialize_player(int player) {
   black = player;
}

/* For player, detect if there are no more moves remaining */
int game_over(uint64_t board, int black) {
	int movable = 0;
	uint64_t o = 1; // a 64-bit version of 1 so we can shift it
#ifdef DEBUG_GAMEOVER
	fprintf(stderr, "Testing for game over\n");
	printf("%" PRIx64 "\n", board);
#endif
	for (int i = 0; i < 64; ++i) {
		if ((black && !IS_BLACK(i)) || (!black && IS_BLACK(i)))
			continue;

		if (!(board & (o << i)))
			// bit is unset
			continue;

		// up, down, left, right
		if ((i < 48 && (board & (o << (i+8))) && !(board & (o << (i+16)))) ||
			(i > 15 && (board & (o << (i-8))) && !(board & (o << (i-16)))) ||
			((i%8 > 1) && (board & (o << (i-1))) && !(board & (o << (i-2)))) ||
			((i%8 < 6) && (board & (o << (i+1))) && !(board & (o << (i+2))))) {
#ifdef DEBUG_GAMEOVER
			fprintf(stderr, "%c%d (bit %d) is movable\n", POS_LETTER(i), POS_NUM(i), i);
#endif
			++movable;
		}
	}

#ifdef DEBUG_GAMEOVER
	fprintf(stderr, "Movable pieces: %d\n", movable);
#endif

	return !movable;
}

int count_movable(uint64_t board, char blacks_turn) {
	int w_movable = 0;
	int b_movable = 0;
	uint64_t o = 1; // a 64-bit version of 1 so we can shift it
#ifdef DEBUG_HEUR
	fprintf(stderr, "Heuristic analyzing. %s's turn\n", blacks_turn ? "Black" : "White");
	printBoard(board);
#endif
	for (int i = 0; i < 64; ++i) {
		if (!(board & (o << i)))
			// bit is unset
			continue;

		// up, down, left, right
		if ((i < 48 && (board & (o << (i+8))) && !(board & (o << (i+16)))) ||
			(i > 15 && (board & (o << (i-8))) && !(board & (o << (i-16)))) ||
			((i%8 > 1) && (board & (o << (i-1))) && !(board & (o << (i-2)))) ||
			((i%8 < 6) && (board & (o << (i+1))) && !(board & (o << (i+2))))) {
#ifdef DEBUG_HEUR
			fprintf(stderr, "%c%d (bit %d) is movable\n", POS_LETTER(i), POS_NUM(i), i);
#endif
			IS_BLACK(i) ? b_movable++ : w_movable++;
		}
	}

	int h = b_movable - w_movable;

	h *= black ? 1 : -1;
	if ((b_movable == 0 && black && !blacks_turn) ||
			(w_movable == 0 && !black && blacks_turn)) {
		h -= 50;
	}

	if ((w_movable == 0 && black && blacks_turn) ||
			(b_movable == 0 && !black && !blacks_turn)) {
		h += 50;
	}


#ifdef DEBUG_HEUR
	fprintf(stderr, "Movable black pieces: %d\n", b_movable);
	fprintf(stderr, "Movable white pieces: %d\n", w_movable);
	fprintf(stderr, "Heuristic: %d\n", h);
#endif
	/*
	if (h >= 50) {
		printf("Printing +50 for:\n");
		printBoard(board);
	}
	*/
	return h;
}
