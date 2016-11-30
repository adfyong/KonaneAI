#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "search.h"
#include "board.h"
#include "heuristic.h"

#define THINKING_TIME  1
#define INIT_ALPHA    (-1000000)
#define INIT_BETA       1000000
#define DONE printf("done\n")

uint64_t alpha_beta_search(uint64_t board, int(*eval)(uint64_t, char), int me)
{
	struct minimax *state;
	state = calloc(1, sizeof(struct minimax));
	state->board = board;
	state->value = INIT_ALPHA;

	time_t start, end, start_thinking;
	start = end = start_thinking = time(NULL);
	int value;
	int i;
	uint64_t next_state;

	/* Time Limited Iterative Deepening Alpha-Beta Search */
	for (int depth = 1; time(NULL) < (start_thinking + THINKING_TIME); depth++) {
		if (state->children) {
			for (i = 0; state->children[i].value != value; i++);
			next_state = state->children[i].board;
			free(state->children);
		}

		value = max_value(state, INIT_ALPHA, INIT_BETA, start, 1, depth, eval, me);
	}

#ifdef DEBUG
	printf("The final value was %d\n", next_state);
#endif

	/*
	   find the node with the value that was returned by the 
	   recursive search
	 */

#ifdef PRINT_STATES
	for (int i = 0; i < state->child_count; ++i) {
		printBoard(state->children[0].board);
		printf("%d\n", state->children[0].value);
	}
#endif

	free(state->children);
	free(state);
	return next_state;
}

int max_value(struct minimax *state, int alpha, int beta, time_t start,
	      int depth, int max_depth, int(*eval)(uint64_t, char), int me)
{
	int v = INIT_ALPHA;

	if (time(NULL) >= (start + THINKING_TIME))
		return 100;

	if (game_over(state->board, me)) {
		v = eval(state->board, me^1);
		state->value = v;
		return v;
	}

	if (depth >= max_depth) {
		v = eval(state->board, me^1);

#ifdef DEBUG
		printf("MAX: max_depth reached in max_value\n");
		printf("MAX: the value of v @ max_depth is %d\n", v);
#endif
		state->value = v;
		return v;
	}

	uint64_t moves[33] = {0};
	getMoves(me, state->board, moves);
	int count = 0;
	while (*(moves+count+1) != 0)
		count++;
	state->children = calloc(count, sizeof(struct minimax));
	state->child_count = count;

	int num_gameovers = 0;
	for (int i = 0; i < count; i++) {
		if (game_over(moves[i+1], me^1)) {
			uint64_t temp = moves[num_gameovers + 1];
			moves[num_gameovers++ + 1] = moves[i+1];
			moves[i+1] = temp;
		}
	}

	for (int i = 1; i <= count; i++) {
		state->children[i-1].board = moves[i];

		state->children[i-1].value = min_value(&(state->children[i-1]), 
				alpha, beta, start, depth+1, max_depth, eval, me^1);

		v = max(v, state->children[i-1].value);

		//printf("Setting value of this board to %d\n", v);
		//printBoard(moves[i]);

		/* if max's value is greater than beta, prune the tree */
		if (v >= beta && 0) {
			if (depth != 1)
				free(state->children);

#ifdef DEBUG
			printf("MAX: v is greater than beta @ depth %d\n", depth);
			printf("the value of v @ comparison is %d\n", v);
#endif

			state->value = v;
			return v;
		}
		alpha = max(beta, v);
	}
	/* 
	   Do not free the moves on the frontier so that a value can be 
	   assigned to them
	   */
	if (depth != 1)
		free(state->children);

#ifdef DEBUG_END_F
	printf("MAX: reached end of max function @ depth %d\n", depth);
	printf("the value of v at the end of the function is %d\n", v);
#endif
	state->value = v;
	return v;
}

int min_value(struct minimax *state, int alpha, int beta, time_t start,
	      int depth, int max_depth, int(*eval)(uint64_t, char), int me)
{
	int v = INIT_BETA;

	if (time(NULL) >= (start + THINKING_TIME))
		return 100;

	if (game_over(state->board, me)) {
		v = eval(state->board, me^1);
		state->value = v;
		return v;
	}

	if (depth >= max_depth) {
		v = eval(state->board, me^1);
#ifdef DEBUG
		printf("MIN: max_depth reached in max_value\n");
		printf("MIN: the value of v @ max_depth is %d\n", v);
#endif

		return v;
	}

	uint64_t moves[33] = {0};
	getMoves(me, state->board, moves);
	int count = 0;
	while (*(moves+count+1) != 0)
		count++;
	state->children = calloc(count, sizeof(struct minimax));
	state->child_count = count;

	int num_gameovers = 0;
	for (int i = 0; i < count; i++) {
		if (game_over(moves[i+1], me^1)) {
			uint64_t temp = moves[num_gameovers + 1];
			moves[num_gameovers++ + 1] = moves[i+1];
			moves[i+1] = temp;
		}
	}

	for (int i = 0; i < count; i++) {

		state->children[i].board = moves[i+1];

		state->children[i].value = max_value(&(state->children[i]),
					alpha, beta, start, depth+1, max_depth, eval, me^1);

		v = min(v, state->children[i].value);

		/* if min's value is less than alpha, prune the tree */
		if (v <= alpha && 0) {
			//printf("Pruning the tree at depth %d\n", depth);

#ifdef DEBUG 
			printf("MIN: v is greater than beta @ depth %d\n", depth);
			printf("the value of v @ comparison is %d\n", v);
#endif

			free(state->children);
			return v;
		}
		beta = min(beta, v);
	}
	free(state->children);

#ifdef DEBUG_END_F
	printf("MIN: reached end of min function @ depth %d\n", depth);
	printf("the value of v at the end of the function is %d\n", v);
#endif

	return v;

}

int max(int a, int b)
{
	if (a >= b)
		return a;
	return b;
}

int min(int a, int b)
{
	if (a <= b)
		return a;
	return b;
}
