#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "search.h"
#include "board.h"
#include "heuristic.h"

#define THINKING_TIME  10
#define INIT_ALPHA    -65
#define INIT_BETA      65

uint64_t alpha_beta_search(uint64_t board, int(*eval)(uint64_t))
{
	struct minimax *state = NULL;
	state->board = board;
	state->value = INIT_ALPHA;

	time_t start = time(NULL);

	// add in iterative deepening search
	int value = max_value(state, INIT_ALPHA, INIT_BETA, start, eval);
	
	int i;
	for (i = 0; state->children[i]->value != value; i++);

	return state->children[i]->board;
}

int max_value(struct minimax *state, int alpha, int beta,
	      time_t start, int(*eval)(uint64_t))
{
	if (time(NULL) > (start+10))
		return eval(state->board);
	
	int v = INIT_ALPHA;
	// assumes max is black --> change later
	uint64_t *moves = getMoves('B', state->board);
	state->children = calloc(moves[0] - 1, sizeof(struct minimax));
	
	if (moves[0] == 0)
		return eval(state->board);
	
	for (int i = 1; i <= moves[0]; i++) {
		state->children[i-1]->board = moves[i];
		v = max(v, min_value(state->children[i],
				     alpha, beta, start, eval));
		
		state->value = v;
		if (v >= alpha)
			return v;
		beta = max(beta, v);
	}
	return v;
}

int min_value(struct minimax *state, int alpha, int beta,
	      time_t start, int(*eval)(uint64_t))
{
	if (time(NULL) > (start+10))
		return eval(state->board);
	
	int v = INIT_BETA;
	// assumes min is white --> change later
	uint64_t *moves = getMoves('W', state->board);
	state->children = calloc(moves[0] - 1, sizeof(struct minimax));
	
	if (moves[0] == 0)
		return eval(state->board);
	
	for (int i = 1; i <= moves[0]; i++) {
		state->children[i-1]->board = moves[i];
		v = min(v, max_value(state->children[i],
				     alpha, beta, start, eval));

		state->value = v;
		if (v <= alpha)
			return v;
		beta = min(beta, v);
	}
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
