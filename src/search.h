#include <stdbool.h>
#include <stdint.h>

struct minimax {
	struct minimax **children;
	uint64_t board;
	int value;
};

/* 
   initializes the alpha-beta pruning algorithm 
   returns the optimal board state for the next move
*/
uint64_t alpha_beta_search(uint64_t state, int(*eval)(uint64_t));

/* recursively gets the value for a max node */
int max_value(struct minimax *state, int alpha, int beta,
	      time_t start, int(*eval)(uint64_t));

/* recursively gets the value for a min node */
int min_value(struct minimax *state, int alpha, int beta,
	      time_t start, int(*eval)(uint64_t));

/* returns the max of a and b */
int max(int a, int b);

/* returns the min of a and b */
int min(int a, int b);
