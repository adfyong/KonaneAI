#include "board.h"
#include "search.h"
#include "heuristic.h"
#include <ctype.h>

int main(int argc, char **argv){
	uint64_t board =0;
	FILE *boardf;

	boardf = fopen(argv[1], "r");
	if (!boardf) {
		fprintf(stderr, "ERROR: Could not open board file\n");
		exit(1);
	}

	if (argc < 3 || (argv[2][0] != 'B' && argv[2][0] != 'W')) {
		fprintf(stderr, "ERROR: Invalid player selection\n");
		exit(1);
	}

	int b_pieces = 0;
	int w_pieces = 0;
	int size = 63;
	for (char f = getc(boardf); f != EOF; f = getc(boardf)) {
		if (size < -1) {
			fprintf(stderr, "ERROR: Too many pieces\n");
			exit(1);
		}

		if (isspace(f)) continue;

		board <<= 1;

		switch(f) {
			case 'B':
				if (!IS_BLACK(size)) {
					fprintf(stderr, "ERROR: Expected W at %c%d\n",
							POS_LETTER(size), POS_NUM(size));
					exit(1);
				}
				++b_pieces;
				board |= 1;
				break;
			case 'W':
				if (IS_BLACK(size)) {
					fprintf(stderr, "ERROR: Expected B at %c%d\n",
							POS_LETTER(size), POS_NUM(size));
					exit(1);
				}
				++w_pieces;
				board |= 1;
				break;
			case 'O':
				break;
			default:
				fprintf(stderr, "ERROR: Unexpected character (%c) at %c%d\n", f,
						POS_LETTER(size), POS_NUM(size));
				exit(1);
				break;
		}

		--size;
	}

	if (size > -1) {
		fprintf(stderr, "ERROR: Unexpected end of file\n");
		printf("Size: %d\n", size);
		exit(1);
	}

#ifdef PRETTY
	printBoard(board);
#endif


#ifdef DEBUG_GETMOVES
	uint64_t moves[10] = {0};
	getMoves(argv[2][0] == 'B', board, moves);
	int indices[2];
	for (int i = 1; i < 10; ++i) {
		printBoard(moves[i]);
		get_move_indices(board, moves[i], indices);
		printf("%c%d-%c%d\n", POS_LETTER(indices[0]), POS_NUM(indices[0]),
				POS_LETTER(indices[1]), POS_NUM(indices[1]));
	}

	return 0;
#endif

	// printf("Black %d\nWhite %d\n", b_pieces, w_pieces);

	int black = (argv[2][0] == 'B' ? 1 : 0);

	if (b_pieces == 32 || w_pieces == 32) {
		if ((black && b_pieces == 31) || (!black && b_pieces == 32)) {
			fprintf(stderr, "WARNING: this should not be an valid state!\n"
					"But as Calin says, YOU'RE THE MASTER\n");
		}
#ifdef PRETTY
		fprintf(stderr, "Making initial move...\n");
#endif
		int move = make_initial_move(board, argv[2][0]);
		board &= ~((uint64_t)1 << move);
		printf("%c%d\n", POS_LETTER(move), POS_NUM(move));
		black ? --b_pieces : --w_pieces;
		black ^= 1;

		if (b_pieces < 32 && w_pieces < 32) {
			// TODO: there's a goto here................................
			// because I forgot about this case.........................
			goto OPPONENT_MOVE;
		}

		while ((black && b_pieces == 32) || (!black && w_pieces == 32)) {
#ifdef PRETTY
			printf("Pick a piece to remove: ");
#endif
			int num;
			char letter;
			scanf(" %c%d", &letter, &num);
			letter = toupper(letter);
			int bit = (num-1) * 8 + (7 - (letter - 'A'));
			if (letter < 'A' || letter > 'H' || num < 1 || num > 8) {
				fprintf(stderr, "Clearly, an invalid move\n");
				continue;
			}

			if ((black && !IS_BLACK(bit)) || (!black && IS_BLACK(bit))) {
				fprintf(stderr, "That's not your piece, doofus\n");
				continue;
			}

			if (!(board & ((uint64_t)1 << bit))) {
				fprintf(stderr, "No piece there, hoss...\n");
				continue;
			}

			if ((black && bit != 36 && bit != 27) ||
					(!black && bit != 35 && bit != 28)) {
				fprintf(stderr, "You picked a move you shouldn't have, but"
						" who am I to stop you?\n");
			}

			board &= ~((uint64_t)1 << bit);
			black ^= 1;
			break;
		}
	}

	while (1) {
#ifdef PRETTY
		printBoard(board);
#endif

		if (game_over(board, black))
			break;

#ifdef SKIP_AB
		uint64_t moves[32];
		getMoves(black, board, moves);
		uint64_t move = moves[1];
#else // do alpha beta
		uint64_t move = alpha_beta_search(board, count_movable, black);
#endif
		black ^= 1;

		int indices[2];
		get_move_indices(board, move, indices);
		printf("%c%d-%c%d\n", POS_LETTER(indices[0]), POS_NUM(indices[0]),
				POS_LETTER(indices[1]), POS_NUM(indices[1]));

		board = move;

OPPONENT_MOVE:

#ifdef PRETTY
		printBoard(board);
#endif

		if (game_over(board, black))
			break;

		move = 0;

		while (move == 0) {
			char fletter, tletter;
			int fnumb, tnumb;
#ifdef PRETTY
			printf("Make a move: ");
#endif
			scanf(" %c%d-%c%d", &fletter, &fnumb, &tletter, &tnumb);
			fletter = tolower(fletter);
			tletter = tolower(tletter);

			move = makeMove(board, findValue(fletter, fnumb),
					findValue(tletter, tnumb), black ? 'B' : 'W');

#ifdef PRETTY
			printf("\n\n");
#endif
		}

		board = move;
		move = 0;

		black ^= 1;
	}

	printf("Game over! %s wins!\n", black ? "White" : "Black");
	return 0;
}
