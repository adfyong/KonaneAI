#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>

void printBoard(uint64_t board);
int getType(int argc);
uint64_t *getMoves(char argc, uint64_t board);
uint64_t *getPieceMoves(int type, int spot, uint64_t board);

uint64_t findRight(int spot, uint64_t board);
uint64_t findDoubleRight(int spot, uint64_t board);

uint64_t findLeft(int spot, uint64_t board);
uint64_t findDoubleLeft(int spot, uint64_t board);


uint64_t findUp(int spot, uint64_t board);
uint64_t findDoubleUp(int spot, uint64_t board);


uint64_t findDown(int spot, uint64_t board);
uint64_t findDoubleDown(int spot, uint64_t board);
