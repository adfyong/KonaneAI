#include <stdio.h>
#include <stdlib.h>

#include "search.h"
#include "board.h"
#include "heuristic.h"

#define THINKING_TIME  10
#define INIT_ALPHA    -65
#define INIT_BETA      65

/* from board.h */
uint64_t *get_moves(uint8_t board){}
bool is_over() { return true;}

/* from heuristic.h */
int get_value(){return 1;}


uint64_t alpha_beta_search(uint64_t board)
{
	struct minimax *state;
	state->children = NULL;
	state->board = board;
	state->value = INIT_ALPHA;
	
	int value = max_value(state, INIT_ALPHA, INIT_BETA, 0);
	int i;
	for (i = 0; state->children[i]->value != value; i++);

	return state->children[i]->board;
}

int max_value(struct minimax *state, int alpha, int beta, int depth)
{
	if (depth == THINKING_TIME || is_over(state->board))
		return get_value(state->board);
		
	int v = INIT_ALPHA;
	uint64_t *moves = get_moves(state->board);
	state->children = calloc(moves[0] - 1, sizeof(struct minimax));
	
	for (int i = 1; i < moves[0]; i++) {
		state->children[i]->board = moves[i];
		v = max(v, min_value(state->children[i], alpha, beta, depth + 1));

		state->value = v;
		if (v >= alpha)
			return v;
		beta = max(beta, v);
	}
	return v;
}

int min_value(struct minimax *state, int alpha, int beta, int depth)
{
	if (depth == THINKING_TIME || is_over(state->board))
		return get_value(state->board);
	
	int v = INIT_BETA;
	uint64_t *moves = get_moves(state->board);
	state->children = calloc(moves[0] - 1, sizeof(struct minimax));
	
	for (int i = 1; i < moves[0]; i++) {
		state->children[i]->board = moves[i];
		v = min(v, max_value(state->children[i], alpha, beta, depth + 1));

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
