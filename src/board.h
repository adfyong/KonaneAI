#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>

void printBoard(uint64_t board);
int getType(int argc);
uint64_t *getMoves(char argc, uint64_t board);
uint64_t *getPieceMoves(int type, int spot, uint64_t board);
