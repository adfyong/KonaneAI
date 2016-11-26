#include <stdbool.h>
#include <stdint.h>
#include <time.h>

struct minimax {
	struct minimax *children;
	int child_count;
	uint64_t board;
	int value;
};

/* 
   initializes the alpha-beta pruning algorithm 
   returns the optimal board state for the next move
*/
uint64_t alpha_beta_search(uint64_t state, int(*eval)(uint64_t), int me);

/* recursively gets the value for a max node */
int max_value(struct minimax *state, int alpha, int beta,
	      int depth, int max_depth, int(*eval)(uint64_t), int me);

/* recursively gets the value for a min node */
int min_value(struct minimax *state, int alpha, int beta,
	      int depth, int max_depth, int(*eval)(uint64_t), int me);

/* returns the max of a and b */
int max(int a, int b);

/* returns the min of a and b */
int min(int a, int b);


void free_minimax(struct minimax *tree);
