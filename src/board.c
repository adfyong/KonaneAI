#include "board.h"



void printBoard(uint64_t board){
  uint64_t spotV;
  int count;
  for (count = 63; count >=0; count-=1){
    spotV = (board >>count) &1;
    if (spotV == 0){
      printf("O");
  }
    else{
       int row = count /8;
       int col = count % 8;
       if (row %2 == 0){
	 if (col % 2 == 0)
	   printf("B");
	 else
	   printf("W");
	 
       }
       else{
	 if (col % 2 == 0)
	   printf("W");
	 else
	   printf("B");
       }
}
    if (count % 8 == 0)
      printf("\n");
  }}

uint64_t *getMoves(char argc, uint64_t board){
  int bSpaces[33]= {0, 2, 4, 6, 9, 11, 13, 15, 16, 18, 20, 22, 25, 27, 29, 31, 32, 34, 36, 38, 41, 43, 45, 47, 48, 50, 52, 54, 57, 59, 61, 63};
  int wSpaces[33] = {1, 3, 5, 7, 8, 10, 12, 14, 17, 19, 21, 23, 24, 26, 28, 30, 31, 33, 35, 37, 39, 40, 42, 44, 46, 49, 51, 53, 55, 56, 58, 60, 62};
  int type;
  int count=0;
  uint64_t spotV = 0;
  uint64_t *moves = malloc(20 *sizeof(board));
if (argc == 'B'){
  for(int i = 0; i<32; i = i +1){
    spotV = (board>>bSpaces[i]) &1;
    if (spotV ==1){
      type = getType(bSpaces[i]);
      uint64_t *pieceMoves = getPieceMoves(type, bSpaces[i], board);
      int counter = 0;
      uint64_t temp = pieceMoves[counter];
      while (temp != 0){
	count +=1;
	moves[count] = temp;
	counter +=1;
	temp = pieceMoves[counter];}
    }
  }
  moves[0] = count;
  return moves;
  }

  if (argc == 'W'){
    
  for(int i = 0; i<32; i = i +1){
    spotV = (board>>wSpaces[i]) &1;
    if (spotV ==1){
      type = getType(wSpaces[i]);
      uint64_t *pieceMoves = getPieceMoves(type, wSpaces[i], board);
      int counter = 0;
      uint64_t temp = pieceMoves[counter];
      while (temp != 0){
	count +=1;
	moves[count] = temp;
	counter +=1;
	temp = pieceMoves[counter];}
    }
  }
  moves[0] = count;
  return moves;
  }


}

uint64_t *getPieceMoves(int type, int spot, uint64_t board){
  int toSpot;
  int spaceSpot;
  uint64_t *moves;
  uint64_t temp;
  int count = 0;
  uint64_t toggle = 1;
  if (type ==1) {
    moves = malloc(3*sizeof(board));
    toSpot = (board>>(spot-2)) & 1;
    spaceSpot = (board >>(spot-1)) & 1;
    
    if (toSpot ==0 && spaceSpot ==1){
      temp = board;
      temp ^= toggle<<spot;
      temp ^=  toggle<<(spot-1);
      temp ^=  toggle<<(spot-2);
      moves[count] = temp;
      count +=1;
  }
    
     toSpot = (board>>(spot-16)) & 1;
    spaceSpot = (board >>(spot-8)) & 1;
    
    if (toSpot ==0 && spaceSpot ==1){
      temp = board;
      temp ^=  toggle<<spot;
      temp ^=  toggle<<(spot-8);
      temp ^=  toggle<<(spot-16);
      moves[count] = temp;
      count +=1;
  }
  }
  if (type ==2) {

    
    moves = malloc(3*sizeof(board));
    toSpot = (board>>(spot-2)) & 1;
    spaceSpot = (board >>(spot-1)) & 1;
    
    if (toSpot ==0 && spaceSpot ==1){
      temp = board;
      temp ^=  toggle<<spot;
      temp ^=  toggle<<(spot-1);
      temp ^=  toggle<<(spot-2);
      moves[count] = temp;
      count +=1;
  }
    
     toSpot = (board>>(spot+16)) & 1;
    spaceSpot = (board >>(spot+8)) & 1;
    
    if (toSpot ==0 && spaceSpot ==1){
      temp = board;
      temp ^=  toggle<<spot;
      temp ^=  toggle<<(spot+8);
      temp ^=  toggle<<(spot+16);
      moves[count] = temp;
      count +=1;
  }
    }

  if (type ==3) {
    moves = malloc(3*sizeof(board));
    toSpot = (board>>(spot+2)) & 1;
    spaceSpot = (board >>(spot+1)) & 1;
    
    if (toSpot ==0 && spaceSpot ==1){
      temp = board;
      temp ^=  toggle<<spot;
      temp ^=  toggle<<(spot+1);
      temp ^=  toggle<<(spot+2);
      moves[count] = temp;
      count +=1;
  }
    
     toSpot = (board>>(spot-16)) & 1;
    spaceSpot = (board >>(spot-8)) & 1;
    
    if (toSpot ==0 && spaceSpot ==1){
      temp = board;
      temp ^=  toggle<<spot;
      temp ^=  toggle<<(spot-8);
      temp ^=  toggle<<(spot-16);
      moves[count] = temp;
      count +=1;
  }
   }

  if (type ==4) {
    moves = malloc(3*sizeof(board));
    toSpot = (board>>(spot+2)) & 1;
    spaceSpot = (board >>(spot+1)) & 1;
    
    if (toSpot ==0 && spaceSpot ==1){
      temp = board;
      temp ^=  toggle<<spot;
      temp ^=  toggle<<(spot+1);
      temp ^=  toggle<<(spot+2);
      moves[count] = temp;
      count +=1;
  }
    
     toSpot = (board>>(spot+16)) & 1;
    spaceSpot = (board >>(spot+8)) & 1;
    
    if (toSpot ==0 && spaceSpot ==1){
      temp = board;
      temp ^=  toggle<<spot;
      temp ^=  toggle<<(spot+8);
      temp ^=  toggle<<(spot+16);
      moves[count] = temp;
      count +=1;
  }
    }
  
  if (type ==5) {
    moves = malloc(4*sizeof(board));
    toSpot = (board>>(spot-2)) & 1;
    spaceSpot = (board >>(spot-1)) & 1;
    
    if (toSpot ==0 && spaceSpot ==1){
      temp = board;
      temp ^=  toggle<<spot;
      temp ^=  toggle<<(spot-1);
      temp ^=  toggle<<(spot-2);
      moves[count] = temp;
      count +=1;
  }
   
    toSpot = (board>>(spot+2)) & 1;
    spaceSpot = (board >>(spot+1)) & 1;
    
    if (toSpot ==0 && spaceSpot ==1){
      temp = board;
      temp ^=  toggle<<spot;
      temp ^=  toggle<<(spot+1);
      temp ^=  toggle<<(spot+2);
      moves[count] = temp;
      count +=1;
  }
 
     toSpot = (board>>(spot-16)) & 1;
    spaceSpot = (board >>(spot-8)) & 1;
    
    if (toSpot ==0 && spaceSpot ==1){
      temp = board;
      temp ^=  toggle<<spot;
      temp ^=  toggle<<(spot-8);
      temp ^=  toggle<<(spot-16);
      moves[count] = temp;
      count +=1;
  }
  }

  if (type ==6) {
    moves = malloc(4*sizeof(board));
    toSpot = (board>>(spot-2)) & 1;
    spaceSpot = (board >>(spot-1)) & 1;
    
    if (toSpot ==0 && spaceSpot ==1){
      temp = board;
      temp ^=  toggle<<spot;
      temp ^=  toggle<<(spot-1);
      temp ^=  toggle<<(spot-2);
      moves[count] = temp;
      count +=1;
  }
   
    toSpot = (board>>(spot+2)) & 1;
    spaceSpot = (board >>(spot+1)) & 1;
    
    if (toSpot ==0 && spaceSpot ==1){
      temp = board;
      temp ^=  toggle<<spot;
      temp ^=  toggle<<(spot+1);
      temp ^=  toggle<<(spot+2);
      moves[count] = temp;
      count +=1;
  }
 
     toSpot = (board>>(spot+16)) & 1;
    spaceSpot = (board >>(spot+8)) & 1;
    
    if (toSpot ==0 && spaceSpot ==1){
      temp = board;
      temp ^=  toggle<<spot;
      temp ^=  toggle<<(spot+8);
      temp ^=  toggle<<(spot+16);
      moves[count] = temp;
      count +=1;
  }
   }

  if (type ==7) {
    moves = malloc(4*sizeof(board));
    toSpot = (board>>(spot+16)) & 1;
    spaceSpot = (board >>(spot+8)) & 1;
    
    if (toSpot ==0 && spaceSpot ==1){
      temp = board;
      temp ^=  toggle<<spot;
      temp ^=  toggle<<(spot+8);
      temp ^=  toggle<<(spot+16);
      moves[count] = temp;
      count +=1;
  }
   
    toSpot = (board>>(spot-2)) & 1;
    spaceSpot = (board >>(spot-1)) & 1;
    
    if (toSpot ==0 && spaceSpot ==1){
      temp = board;
      temp ^=  toggle<<spot;
      temp ^=  toggle<<(spot-1);
      temp ^=  toggle<<(spot-2);
      moves[count] = temp;
      count +=1;
  }
 
     toSpot = (board>>(spot-16)) & 1;
    spaceSpot = (board >>(spot-8)) & 1;
    
    if (toSpot ==0 && spaceSpot ==1){
      temp = board;
      temp ^=  toggle<<spot;
      temp ^=  toggle<<(spot-8);
      temp ^=  toggle<<(spot-16);
      moves[count] = temp;
      count +=1;
  }
   }

  if (type ==8) {
    moves = malloc(4*sizeof(board));
    toSpot = (board>>(spot+16)) & 1;
    spaceSpot = (board >>(spot+8)) & 1;
    
    if (toSpot ==0 && spaceSpot ==1){
      temp = board;
      temp ^=  toggle<<spot;
      temp ^=  toggle<<(spot+8);
      temp ^=  toggle<<(spot+16);
      moves[count] = temp;
      count +=1;
  }
   
    toSpot = (board>>(spot+2)) & 1;
    spaceSpot = (board >>(spot+1)) & 1;
    
    if (toSpot ==0 && spaceSpot ==1){
      temp = board;
      temp ^=  toggle<<spot;
      temp ^=  toggle<<(spot+1);
      temp ^=  toggle<<(spot+2);
      moves[count] = temp;
      count +=1;
  }
 
     toSpot = (board>>(spot-16)) & 1;
    spaceSpot = (board >>(spot-8)) & 1;
    
    if (toSpot ==0 && spaceSpot ==1){
      temp = board;
      temp ^=  toggle<<spot;
      temp ^=  toggle<<(spot-8);
      temp ^=  toggle<<(spot-16);
      moves[count] = temp;
      count +=1;
  }
   }
  
  if (type ==9) {
    moves = malloc(5*sizeof(board));
    
    toSpot = (board>>(spot-2)) & 1;
    spaceSpot = (board >>(spot-1)) & 1;
    
    if (toSpot ==0 && spaceSpot ==1){
      temp = board;
      temp ^=  toggle<<spot;
      temp ^=  toggle<<(spot-1);
      temp ^=  toggle<<(spot-2);
      moves[count] = temp;
      count +=1;
  }

    

    toSpot = (board>>(spot+16)) & 1;
    spaceSpot = (board >>(spot+8)) & 1;
    
    if (toSpot ==0 && spaceSpot ==1){
      temp = board;
      temp ^=  toggle<<spot;
      temp ^=  toggle<<(spot+8);
      temp ^= toggle<<(spot+16);
      moves[count] = temp;
      count +=1;
  }
   
    toSpot = (board>>(spot+2)) & 1;
    spaceSpot = (board >>(spot+1)) & 1;
    
    if (toSpot ==0 && spaceSpot ==1){
      temp = board;
      temp ^=  toggle<<spot;
      temp ^=  toggle<<(spot+1);
      temp ^=  toggle<<(spot+2);
      moves[count] = temp;
      count +=1;
  }
 
     toSpot = (board>>(spot-16)) & 1;
    spaceSpot = (board >>(spot-8)) & 1;
    
    if (toSpot ==0 && spaceSpot ==1){
      temp = board;
      temp ^=  toggle<<spot;
      temp ^=  toggle<<(spot-8);
      temp ^=  toggle<<(spot-16);
      moves[count] = temp;
      count +=1;
  }
   }
  moves[count] = 0;
  return moves;
  
} 


int getType(int argc){
  int row = argc /8;
  int col = argc % 8;
  int type = 0;
  if (row <=7 && row >=6 && col <=7 && col >=6)
    type = 1;
  
  if (row <=1 && row >=0 && col <=7 && col >=6)
    type = 2;
  
  if (row <=7 && row >=6 && col <=1 && col >=0)
    type = 3;

  if (row <=1 && row >=0 && col <=1 && col >=0)
    type = 4;
  
  if (row <=7 && row >=6 && col <=5 && col >=2)
    type = 5;

  if (row <=1 && row >=0 && col <=5 && col >=2)
    type = 6;

  if (row <=5 && row >=2 && col <=7 && col >=6)
    type = 7;

  if (row <=5 && row >=2 && col <= 1 && col >=0)
    type = 8;

  if (row <=5 && row >=2 && col <=5 && col >=2)
    type = 9;

  return type;
}
