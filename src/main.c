#include "board.h"


int main(int argc, char **argv){
  uint64_t board =0;
  int count = 0;
  FILE *boardf;
  uint64_t *moves;
  boardf = fopen(argv[1], "r");
  char f;
  f = fgetc(boardf);
  while(f != EOF){

    if (f == 'B' || f == 'W')
      board = board | 1;
    
    f = fgetc(boardf);
    if (f == 'B' || f == 'W' || f == 'O')
      board = board << 1;
  };
  printBoard(board);
  printf("\n \n");
  moves = getMoves('B', board);
  int i = moves[0];
  int c = 1;
  for (c; c<=i; c+=1){
    printf("\n");
    printBoard(moves[c]);
     }
}
