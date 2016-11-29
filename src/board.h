#ifndef _BOARD_H
#define _BOARD_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>

#define IS_BLACK(i) (((i/8) % 2) == (i % 2))
#define POS_NUM(i) (i/8 + 1)
#define POS_LETTER(i) (7 - (i%8) + 'A')

int make_initial_move(uint64_t, char);
void get_move_indices(uint64_t, uint64_t, int *);
void printBoard(uint64_t board);
int getType(int space_value);
int findValue(char space_letter, int space_number);
char findColor(int space_value);
//uint64_t makeInitialMove(uint64_t board, int argc, char argv);
uint64_t makeMove(uint64_t board, int from_value, int to_value, char player);
void getMoves(int player, uint64_t board,uint64_t *moves);
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
