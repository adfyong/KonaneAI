#ifndef HEURISTIC_H
#define HEURISTIC_H

#include <stdint.h>

void initialize_player(int);
int game_over(uint64_t, char);
int count_movable(uint64_t board, char);

#endif /* HEURISTIC_H */
