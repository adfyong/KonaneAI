#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "search.h"
#include "board.h"
#include "heuristic.h"

#define THINKING_TIME  10
#define INIT_ALPHA    -65
#define INIT_BETA      65
#define DONE printf("done\n")

uint64_t alpha_beta_search(uint64_t board, int(*eval)(uint64_t), int me)
{
	struct minimax *state;
	state = malloc(sizeof(struct minimax));
	state->board = board;
	state->value = INIT_ALPHA;
	
	time_t start = time(NULL);
	int value;
	for (int depth = 1; time(NULL) < (start + THINKING_TIME); depth++)
		value = max_value(state, INIT_ALPHA, INIT_BETA, 1, 2, eval, me);

	int i;
	for (i = 0; state->children[i].value != value; i++);

	return state->children[i].board;
}

int max_value(struct minimax *state, int alpha, int beta,
	      int depth, int max_depth, int(*eval)(uint64_t), int me)
{
	if (depth >= max_depth) {
		uint64_t board = state->board;
		//free(state);
		return eval(board);
	}
	
	int v = INIT_ALPHA;
	uint64_t *moves = malloc(20*sizeof(state->board));
	getMoves(me, state->board, moves);
	me ^= 1;
	state->children = malloc(moves[0] * sizeof(struct minimax));

	if (moves[0] == 0){
		free(moves);
		return eval(state->board);
	}
	for (int i = 1; i <= moves[0]; i++) {
		state->children[i-1].board = moves[i];
	       
		v = max(v, min_value(&(state->children[i-1]),
				     alpha, beta, depth++, max_depth, eval, me));
		
		state->value = v;
		if (v >= alpha){
			free(moves);
			return v;}
		beta = max(beta, v);
	}
	free(moves);
	return v;
}

int min_value(struct minimax *state, int alpha, int beta,
	      int depth, int max_depth, int(*eval)(uint64_t), int me)
{
	if (depth >= max_depth) {
		uint64_t board = state->board;
		//free(state);
		return eval(board);
	}
       
	int v = INIT_BETA;

	uint64_t *moves =malloc(20*sizeof(state->board));
	getMoves(me, state->board, moves);
	me ^= 1;
	state->children = malloc(moves[0] * sizeof(struct minimax));

	if (moves[0] == 0){
		free(moves);
		return eval(state->board);
	}
	for (int i = 1; i <= moves[0]; i++) {
		
		state->children[i-1].board = moves[i];
		v = min(v, max_value(&(state->children[i-1]),
				     alpha, beta, depth++, max_depth, eval, me));

		state->value = v;
		if (v <= alpha){
			free(moves);
			return v;}
		beta = min(beta, v);
	}
	free(moves);
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
