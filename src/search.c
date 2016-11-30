#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "search.h"
#include "board.h"
#include "heuristic.h"

#define THINKING_TIME  3
#define INIT_ALPHA    (-65)
#define INIT_BETA      65
#define DONE printf("done\n")

uint64_t alpha_beta_search(uint64_t board, int(*eval)(uint64_t), int me)
{
	struct minimax *state;
	struct minimax copy;
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
	printf("The final value was %d\n", value);
#endif

	/* 
	   find the node with the value that was returned by the 
	   recursive search
	 */

	free(state->children);
	free(state);
	return next_state;
}

int max_value(struct minimax *state, int alpha, int beta, time_t start,
	      int depth, int max_depth, int(*eval)(uint64_t), int me)
{
	int v = INIT_ALPHA;

	if (time(NULL) >= (start + THINKING_TIME))
		return 100;
	
	if (depth >= max_depth) {
		v = eval(state->board);
		
#ifdef DEBUG
		printf("MAX: max_depth reached in max_value\n");
		printf("MAX: the value of v @ max_depth is %d\n", v);
#endif
		
		return v;
	}
	
	uint64_t moves[33] = {0};
	getMoves(me, state->board, moves);
	int count = 0;
	while (*(moves+count+1) != 0)
		count++;
	state->children = calloc(count, sizeof(struct minimax));
	state->child_count = *moves;


	for (int i = 1; i <= count; i++) {

		state->children[i-1].board = moves[i];

		v = max(v, min_value(&(state->children[i-1]),
				     alpha, beta, start, depth+1, max_depth, eval, me^1));

		
		state->children[i-1].value = v;

		/* if max's value is greater than beta, prune the tree */
		if (v >= beta) {
			if (depth != 1)
				free(state->children);
			
#ifdef DEBUG
			printf("MAX: v is greater than beta @ depth %d\n", depth);
			printf("the value of v @ comparison is %d\n", v);
#endif
			
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
	
#ifdef DEBUG
	printf("MAX: reached end of max function @ depth %d\n", depth);
	printf("the value of v at the end of the function is %d\n", v);
#endif
	
	return v;
}

int min_value(struct minimax *state, int alpha, int beta, time_t start,
	      int depth, int max_depth, int(*eval)(uint64_t), int me)
{
	int v = INIT_BETA;

	if (time(NULL) >= (start + THINKING_TIME))
		return 100;
	
	if (depth >= max_depth) {
		v = eval(state->board);
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
	state->child_count = *moves;
	
	for (int i = 1; i <= count; i++) {
		
		state->children[i-1].board = moves[i];
		
		v = min(v, max_value(&(state->children[i-1]),
				     alpha, beta, start, depth+1, max_depth, eval, me^1));

		state->children[i-1].value = v;
		
		/* if min's value is less than alpha, prune the tree */
		if (v <= alpha) {
			
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
	
#ifdef DEBUG
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
