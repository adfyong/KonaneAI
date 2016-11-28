#ifndef _BOARD_H
#define _BOARD_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>

int make_initial_move(uint64_t, char);
void get_move_indices(uint64_t, uint64_t, int *);
void printBoard(uint64_t board);
int getType(int argc);
int findValue(char argc, int argv);
char findColor(int argc);
//uint64_t makeInitialMove(uint64_t board, int argc, char argv);
uint64_t makeMove(uint64_t board, int argc, int argv, char argv1);
void getMoves(int argc, uint64_t board,uint64_t *moves);
void getPieceMoves(int type, int spot, uint64_t board, uint64_t *moves);

uint64_t findRight(int spot, uint64_t board);
uint64_t findDoubleRight(int spot, uint64_t board);

uint64_t findLeft(int spot, uint64_t board);
uint64_t findDoubleLeft(int spot, uint64_t board);


uint64_t findUp(int spot, uint64_t board);
uint64_t findDoubleUp(int spot, uint64_t board);


uint64_t findDown(int spot, uint64_t board);
uint64_t findDoubleDown(int spot, uint64_t board);

#endif /* _BOARD_H */
