#include "board.h"

int make_initial_move(uint64_t board, char player) {
	uint64_t o = 1;
	if (player == 'B') {
		if (board & (o << 36))
			return 36;	// D5
		else
			return 27;	// E4
	} else {
		if (board & (o << 35))
			return 35;	// E5
		else
			return 28;	// D4
	}
}

void get_move_indices(uint64_t from, uint64_t to, int *move) {
	uint64_t o = 1;
	move[0] = move[1] = -1;
	for (int i = 0; i < 64; ++i) {
		if (move[1] == -1 && !(from & (o << i)) && to & (o << i)) {
			move[1] = i;
			continue;
		}

		if (move[0] == -1 && from & (o << i) && !(to & (o << i)) &&
				(move[1] == -1 || (IS_BLACK(move[1]) == IS_BLACK(i)))) {
			move[0] = i;
			continue;
		}

		if (move[0] != -1 && move[1] != -1)
			return;
	}
}

void printBoard(uint64_t board){
	uint64_t spotV;
	int count;
	int numbers = 8;
	printf("%d ", numbers);
	for (count = 63; count >=0; count-=1){
		spotV = (board >>count) &1;
		if (spotV == 0){
			printf("O ");
		}
		else{
			int row = count /8;
			int col = count % 8;
			if (row %2 == 0){
				if (col % 2 == 0)
					printf("B ");
				else
					printf("W ");

			}
			else{
				if (col % 2 == 0)
					printf("W ");
				else
					printf("B ");
			}
		}
		if (count % 8 == 0){
			printf("\n");
			numbers -=1;
			if (numbers !=0)
			printf("%d ", numbers);
		}
	}
	printf("  a b c d e f g h\n\n");
}
int findValue(char space_letter, int space_number){
	int value;
	value = (7-((int)space_letter-97))+((space_number-1)*8);
	return value;
	
}

char findColor(int space_value){
	char color;
	int row = space_value /8;
	int col = space_value % 8;
	if (row %2 == 0){
		if (col % 2 == 0)
			color = 'B';
		else
			color = 'W';
		
	}
	else{
		if (col % 2 == 0)
			color = 'W';
		else
			color = 'B';
	}
	return color;
}

uint64_t makeMove(uint64_t board, int from_value, int to_value, char player){
	uint64_t temp = 0;
	uint64_t toggle = 1;
	int diff = to_value - from_value;
	int frow = from_value /8;
	int fcol = from_value % 8;
	int trow = to_value /8;
	int tcol = to_value %8;
	int fromSpot = (board>>(from_value)) &1;
	int toSpot = (board>>(to_value)) &1;
	int toSpot1; //first spot jumping to
	int space1; //first piece we want to jump
	int toSpot2; //second spot jumping to
	int space2;//second piece we want to jump 
	int space3;
	

	if(findColor(from_value) == player && findColor(to_value)== player && from_value >=0 && from_value<=63 && to_value >=0 && to_value <=63 && fromSpot==1
&& toSpot ==0){
		switch(diff){
		case 16:
			if(tcol == fcol){
				space1 = (board >>(from_value+8)) & 1;
				if(space1 ==1){
					temp = board;
					temp ^= toggle<<from_value;
					temp ^=  toggle<<(from_value+8);
					temp ^=  toggle<<to_value;
					return temp;
					break;
				}
			}
		case -16:
			if(tcol == fcol){
				space1 = (board >>(from_value-8)) & 1;
				if(space1 ==1){
					temp = board;
					temp ^= toggle<<from_value;
					temp ^=  toggle<<(from_value-8);
					temp ^=  toggle<<to_value;
					return temp;
					break;
				}
			}
		case 2:
			if(trow == frow){
				space1 = (board >>(from_value +1)) & 1;
				if(space1 ==1){
					temp = board;
					temp ^= toggle<<from_value;
					temp ^=  toggle<<(from_value+1);
					temp ^=  toggle<<to_value;
					return temp;
					break;
				}
			}
		case -2:
			if(trow == frow){
				space1 = (board >>(from_value-1)) & 1;
				if(space1 ==1){
					temp = board;
					temp ^= toggle<<from_value;
					temp ^=  toggle<<(from_value-1);
					temp ^=  toggle<<to_value;
					return temp;
					break;
				}
			}
		case 4:
			if(trow == frow){
				space1= (board >>(from_value+1)) &1;
				toSpot1=(board >>(from_value+2))&1;
				space2 = (board >> (from_value+3))&1;
				if(space1==1 && space2 == 1 && toSpot1==0){
					temp=board;
					temp ^= toggle<<from_value;
					temp ^= toggle<<(from_value+1);
					temp ^= toggle<<(from_value+3);
					temp ^= toggle <<to_value;
					return temp;
					break;
				}
			}
		case -4:
			if(trow == frow){
				space1= (board >>(from_value-1)) &1;
				toSpot1 =(board >>(from_value-2))&1; 
				space2 = (board >> (from_value-3))&1;
				if(space1==1 && toSpot1==0 && space2 ==1){
					temp=board;
					temp ^= toggle<<from_value;
					temp ^= toggle<<(from_value-1);
					temp ^= toggle<<(from_value-3);
					temp ^= toggle <<to_value;
					return temp;
					break;
				}
			}
		case 32:
			if(tcol == fcol){
				space1= (board >>(from_value+8)) &1;
				toSpot1 =(board >>(from_value+16))&1;
				space2 = (board >> (from_value+24))&1;
				if(space1==1 && toSpot1==0 && space2 ==1){
					temp=board;
					temp ^= toggle<<from_value;
					temp ^= toggle<<(from_value+8);
					temp ^= toggle<<(from_value+24);
					temp ^= toggle <<to_value;
					return temp;
					break;
				}
			}
		case -32:
			if(tcol == fcol){
				space1= (board >>(from_value-8)) &1;
				toSpot1 =(board >>(from_value-16))&1;
				space2 = (board >> (from_value-24))&1;
				if(space1==1 && toSpot1==0 && space2 ==1){
					temp=board;
					temp ^= toggle<<from_value;
					temp ^= toggle<<(from_value-8);
					temp ^= toggle<<(from_value-24);
					temp ^= toggle <<to_value;
					return temp;
					break;
				}
			}
		case 48:
			if(tcol ==fcol){
				space1=(board>>(from_value+8)) & 1;
				toSpot1 =(board >>(from_value+16)) & 1;
				space2 = (board >>(from_value+24)) & 1;
				toSpot2 = (board >>(from_value+32)) & 1;
				space3 = (board >>(from_value+40)) &1;
				if(space1==1 && space2==1 && space3==1 && toSpot1 == 0 && toSpot2 ==0){
					temp=board;
					temp ^= toggle<<from_value;
					temp ^= toggle<<(from_value+8);
					temp ^= toggle<<(from_value+24);
					temp ^= toggle<<(from_value+40);
					temp ^= toggle<<to_value;
					return temp;
					break;
				}
				    
			}
		case -48:
			if(tcol ==fcol){
				space1=(board>>(from_value-8)) & 1;
				toSpot1 =(board >>(from_value-16)) & 1;
				space2 = (board >>(from_value-24)) & 1;
				toSpot2 = (board >>(from_value-32)) & 1;
				space3 = (board >>(from_value-40)) &1;
				if(space1==1 && space2==1 && space3==1 && toSpot1 == 0 && toSpot2 ==0){
					temp=board;
					temp ^= toggle<<from_value;
					temp ^= toggle<<(from_value-8);
					temp ^= toggle<<(from_value-24);
					temp ^= toggle<<(from_value-40);
					temp ^= toggle<<to_value;
					return temp;
					break;
				}
				    
		
			}
		case 6:
			
			if(trow ==frow){
				space1=(board>>(from_value+1)) & 1;
				toSpot1 =(board >>(from_value+2)) & 1;
				space2 = (board >>(from_value+3)) & 1;
				toSpot2 = (board >>(from_value+4)) & 1;
				space3 = (board >>(from_value+5)) &1;
				if(space1==1 && space2==1 && space3==1 && toSpot1 == 0 && toSpot2 ==0){
					temp=board;
					temp ^= toggle<<from_value;
					temp ^= toggle<<(from_value+1);
					temp ^= toggle<<(from_value+3);
					temp ^= toggle<<(from_value+5);
					temp ^= toggle<<to_value;
					return temp;
					break;
				}
				    
			}
		case -6:
			
			if(trow ==frow){
				space1=(board>>(from_value-1)) & 1;
				toSpot1 =(board >>(from_value-2)) & 1;
				space2 = (board >>(from_value-3)) & 1;
				toSpot2 = (board >>(from_value-4)) & 1;
				space3 = (board >>(from_value-5)) &1;
				if(space1==1 && space2==1 && space3==1 && toSpot1 == 0 && toSpot2 ==0){
					temp=board;
					temp ^= toggle<<from_value;
					temp ^= toggle<<(from_value-1);
					temp ^= toggle<<(from_value-3);
					temp ^= toggle<<(from_value-5);
					temp ^= toggle<<to_value;
					return temp;
					break;
				}
				    
			}
			
		}
	}
	return temp;
}
void getMoves(int player, uint64_t board, uint64_t *moves){
	int bSpaces[32]= {0, 2, 4, 6, 9, 11, 13, 15, 16, 18, 20, 22, 25, 27, 29, 31, 32, 34, 36, 38, 41, 43, 45, 47, 48, 50, 52, 54, 57, 59, 61, 63};
	int wSpaces[32] = {1, 3, 5, 7, 8, 10, 12, 14, 17, 19, 21, 23, 24, 26, 28, 30, 33, 35, 37, 39, 40, 42, 44, 46, 49, 51, 53, 55, 56, 58, 60, 62};
	
	uint64_t spotV = 0;
	moves[0]=0;
	if (player == 1){
		for(int i = 0; i<32; i = i +1){
			spotV = (board>>bSpaces[i]) &1;
			if (spotV ==1){
				getPieceMoves( bSpaces[i], board, moves);
			}}
	       
	}

	if (player == 0){
		for(int i = 0; i<32; i=i+1){
	       	spotV = (board>>wSpaces[i]) &1;
			if (spotV ==1){
				getPieceMoves( wSpaces[i], board, moves);
			}}
		}
}

void getPieceMoves( int spot, uint64_t board,uint64_t *moves){
	uint64_t temp;
	int count = moves[0]+1;
	temp=findRight(spot, board);
	if (temp !=0){
		moves[count]=temp;
		count +=1;
	
		temp=findDoubleRight(spot, board);
		if (temp !=0){
			moves[count]=temp;
			count +=1;
			temp=findTripleRight(spot, board);
			if(temp != 0){
				moves[count]=temp;
				count+=1;
			}}
		
	}
	temp=findLeft(spot, board);
	if (temp !=0){
		moves[count]=temp;
		count +=1;
		
		temp=findDoubleLeft(spot, board);
		if (temp !=0){
			moves[count]=temp;
			count +=1;
			temp=findTripleLeft(spot, board);
			if (temp != 0){
				moves[count]=temp;
				count +=1;
			}
		}}
	temp=findUp(spot, board);
	if (temp !=0){
		moves[count]=temp;
		count +=1;
	
		temp=findDoubleUp(spot, board);
		if (temp !=0){
			moves[count]=temp;
			count +=1;
			temp=findTripleUp(spot, board);
			if (temp != 0){
				moves[count]=temp;
				count +=1;
			}
			
		}}
	temp=findDown(spot, board);
	if (temp !=0){
		moves[count]=temp;
		count +=1;
		
		temp=findDoubleDown(spot, board);
		if (temp !=0){
			moves[count]=temp;
			count +=1;
			temp=findTripleDown(spot, board);
			if (temp != 0){
				moves[count]=temp;
				count +=1;
}
		}}
	moves[0]=count-1;
	
}
uint64_t findRight(int spot, uint64_t board){
	int toSpot;
	int spaceSpot;
	uint64_t toggle= 1;
	uint64_t temp=0;
	int to_value = spot -2;
	int frow=spot /8;
	int trow = to_value /8;
	if(frow == trow && to_value >=0){
	toSpot = (board>>(spot-2)) & 1;
	spaceSpot = (board >>(spot-1)) & 1;
	if (toSpot ==0 && spaceSpot ==1){
		temp = board;
		temp ^= toggle<<spot;
		temp ^=  toggle<<(spot-1);
		temp ^=  toggle<<(spot-2);
	}}
	return temp;
}

uint64_t findLeft(int spot, uint64_t board){
	int toSpot;
	int spaceSpot;
	uint64_t toggle= 1;
	uint64_t temp=0;
	int to_value = spot +2;
	int frow = spot/8;
	int trow = to_value/8;
	if(frow == trow && to_value <= 63){
	toSpot = (board>>(spot+2)) & 1;
	spaceSpot = (board >>(spot+1)) & 1;
	if (toSpot ==0 && spaceSpot ==1){
		temp = board;
		temp ^= toggle<<spot;
		temp ^=  toggle<<(spot+1);
		temp ^=  toggle<<(spot+2);
	}}
	return temp;
}

uint64_t findDoubleRight(int spot, uint64_t board){
	int toSpot;
	int spaceSpot;
	int doubleTo;
	int doubleSpace;
	int spotRow;
	int toRow;
	uint64_t toggle =1;
	uint64_t temp = 0;

	toSpot = (board>>(spot-2)) & 1; //middle spot
	spaceSpot = (board >>(spot-1)) & 1; //spot to the right of piece we want to move
	doubleTo = (board >>(spot-4))&1;  //spot we want to jump to
	doubleSpace = (board >>(spot-3))&1; // space to the left of the spot we want to move to
	
	spotRow = spot /8;
	toRow = (spot -4)/8;
	if (toSpot ==0 && spaceSpot ==1 && doubleTo ==0 && doubleSpace ==1 && toRow==spotRow && (spot-4)>=0){
		temp = board;
		temp ^= toggle<<spot;
		temp ^= toggle<<(spot-1);
		temp ^= toggle<<(spot -3);
		temp ^= toggle<< (spot-4);
	}
	return temp;
}
uint64_t findTripleRight(int spot, uint64_t board){
	int toSpot1; //first spot jumping to
	int space1; //first piece we want to jump
	int toSpot2; //second spot jumping to
	int space2;//second piece we want to jump 
	int toSpot3; //third spot jumping to
	int space3;
	int frow;
	int trow;
	int to_value;
	uint64_t toggle = 1;
	uint64_t temp =0;
	
	toSpot1=(board>>(spot-2)) & 1;
	space1 = (board >>(spot-1))& 1;
	toSpot2 =(board >>(spot-4)) & 1;
	space2 = (board >>(spot-3)) & 1;
	toSpot3 = (board >>(spot-6)) & 1;
	space3 = (board >>(spot-5)) & 1;
	to_value = spot -6;
	frow = spot / 8;
	trow = to_value / 8;
	if(toSpot1 ==0 && toSpot2 == 0 && toSpot3 == 0 && space1 == 1 && space2 ==1 && space3 ==1 && to_value >= 0 && frow == trow){
		temp = board;
		temp ^= toggle<<spot;
		temp ^= toggle<<(spot-1);
		temp ^= toggle<<(spot-3);
		temp ^= toggle<<(spot-5);
		temp ^= toggle<<(spot-6);
	}
	return temp;
	
}

uint64_t findDoubleLeft(int spot, uint64_t board){
	int toSpot;
	int spaceSpot;
	int doubleTo;
	int doubleSpace;
	int toRow;
	int spotRow;
	uint64_t toggle =1;
	uint64_t temp = 0;

	toSpot = (board>>(spot+2)) & 1;
	spaceSpot = (board >>(spot+1)) & 1;
	doubleTo = (board >>(spot+4))&1;
	doubleSpace = (board >>(spot+3))&1;
	
	spotRow = spot /8;
	toRow = (spot+4)/8;
	if (toSpot ==0 && spaceSpot ==1 && doubleTo ==0 && doubleSpace ==1 && toRow == spotRow && (spot+4)<=63){
		temp = board;
		temp ^= toggle<<spot;
		temp ^= toggle<<(spot+1);
		temp ^= toggle<<(spot +3);
		temp ^= toggle<< (spot+4);
	}
	return temp;
}

uint64_t findTripleLeft(int spot, uint64_t board){
	int toSpot1; //first spot jumping to
	int space1; //first piece we want to jump
	int toSpot2; //second spot jumping to
	int space2;//second piece we want to jump 
	int toSpot3; //third spot jumping to
	int space3;
	int frow;
	int trow;
	int to_value;
	uint64_t toggle = 1;
	uint64_t temp =0;
	
	toSpot1=(board>>(spot+2)) & 1;
	space1 = (board >>(spot+1))& 1;
	toSpot2 =(board >>(spot+4)) & 1;
	space2 = (board >>(spot+3)) & 1;
	toSpot3 = (board >>(spot+6)) & 1;
	space3 = (board >>(spot+5)) & 1;
	to_value = spot +6;
	frow = spot / 8;
	trow = to_value / 8;
	if(toSpot1 ==0 && toSpot2 == 0 && toSpot3 == 0 && space1 == 1 && space2 ==1 && space3 ==1 && to_value <=63 && frow == trow){
		temp = board;
		temp ^= toggle<<spot;
		temp ^= toggle<<(spot+1);
		temp ^= toggle<<(spot+3);
		temp ^= toggle<<(spot+5);
		temp ^= toggle<<(spot+6);
	}
	return temp;
	
}
uint64_t findUp(int spot, uint64_t board){
	int toSpot;
	int spaceSpot;
	uint64_t toggle= 1;
	uint64_t temp=0;
	int to_value =spot+16;
	int fcol = spot%8;
	int tcol = to_value %8;
	if(tcol == fcol && to_value <=63){
	toSpot = (board>>(spot+16)) & 1;
	spaceSpot = (board >>(spot+8)) & 1;
	if (toSpot ==0 && spaceSpot ==1){
		temp = board;
		temp ^= toggle<<spot;
		temp ^=  toggle<<(spot+8);
		temp ^=  toggle<<(spot+16);
	}}
	return temp;

}
uint64_t findDoubleUp(int spot, uint64_t board){
	int toSpot;
	int spaceSpot;
	int doubleTo;
	int doubleSpace;
	int toCol;
	int spotCol;
	uint64_t toggle =1;
	uint64_t temp = 0;
	toSpot = (board>>(spot+16)) & 1;
	spaceSpot = (board >>(spot+8)) & 1;
	doubleTo = (board >>(spot+32))&1;
	doubleSpace = (board >>(spot+24))&1;
	spotCol = spot % 8;
	toCol = (spot +32) % 8;
	if (toSpot ==0 && spaceSpot ==1 && doubleTo ==0 && doubleSpace ==1 && spotCol == toCol && (spot+32)<=63){
		temp = board;
		temp ^= toggle<<spot;
		temp ^= toggle<<(spot+8);
		temp ^= toggle<<(spot +24);
		temp ^= toggle<< (spot+32);
	}
	return temp;
}

uint64_t findTripleUp(int spot, uint64_t board){
	int toSpot1; //first spot jumping to
	int space1; //first piece we want to jump
	int toSpot2; //second spot jumping to
	int space2;//second piece we want to jump 
	int toSpot3; //third spot jumping to
	int space3;
	int fcol;
	int tcol;
	int to_value;
	uint64_t toggle = 1;
	uint64_t temp =0;
	
	toSpot1=(board>>(spot+16)) & 1;
	space1 = (board >>(spot+8))& 1;
	toSpot2 =(board >>(spot+32)) & 1;
	space2 = (board >>(spot+24)) & 1;
	toSpot3 = (board >>(spot+48)) & 1;
	space3 = (board >>(spot+40)) & 1;
	to_value = spot +48;
	fcol = spot % 8;
	tcol = to_value % 8;
	if(toSpot1 ==0 && toSpot2 == 0 && toSpot3 == 0 && space1 == 1 && space2 ==1 && space3 ==1 && to_value <=63 && fcol == tcol){
		temp = board;
		temp ^= toggle<<spot;
		temp ^= toggle<<(spot+8);
		temp ^= toggle<<(spot+24);
		temp ^= toggle<<(spot+40);
		temp ^= toggle<<(spot+48);
	}
	return temp;
	
}
uint64_t findDown(int spot, uint64_t board){
	int toSpot;
	int spaceSpot;
	uint64_t toggle= 1;
	uint64_t temp=0;
	int to_value = spot-16;
	int fcol = spot %8;
	int tcol = to_value %8;
	if(fcol == tcol && to_value >=0){
	toSpot = (board>>(spot-16)) & 1;
	spaceSpot = (board >>(spot-8)) & 1;
	if (toSpot ==0 && spaceSpot ==1){
		temp = board;
		temp ^= toggle<<spot;
		temp ^=  toggle<<(spot-8);
		temp ^=  toggle<<(spot-16);
	}}
	return temp;
}
uint64_t findDoubleDown(int spot, uint64_t board){
	int toSpot;
	int spaceSpot;
	int doubleTo;
	int doubleSpace;
	int toCol;
	int spotCol;
	uint64_t toggle =1;
	uint64_t temp = 0;
	toSpot = (board>>(spot-16)) & 1;
	spaceSpot = (board >>(spot-8)) & 1;
	doubleTo = (board >>(spot-32))&1;
	doubleSpace = (board >>(spot-24))&1;
	spotCol = spot % 8;
	toCol = (spot-32)% 8;
	if (toSpot ==0 && spaceSpot ==1 && doubleTo ==0 && doubleSpace ==1 && toCol == spotCol && (spot-32)>=0){
		temp = board;
		temp ^= toggle<<spot;
		temp ^= toggle<<(spot-8);
		temp ^= toggle<<(spot -24);
		temp ^= toggle<< (spot-32);
	}
	return temp;
}

uint64_t findTripleDown(int spot, uint64_t board){
	int toSpot1; //first spot jumping to
	int space1; //first piece we want to jump
	int toSpot2; //second spot jumping to
	int space2;//second piece we want to jump 
	int toSpot3; //third spot jumping to
	int space3;
	int fcol;
	int tcol;
	int to_value;
	uint64_t toggle = 1;
	uint64_t temp =0;
	
	toSpot1=(board>>(spot-16)) & 1;
	space1 = (board >>(spot-8))& 1;
	toSpot2 =(board >>(spot-32)) & 1;
	space2 = (board >>(spot-24)) & 1;
	toSpot3 = (board >>(spot-48)) & 1;
	space3 = (board >>(spot-40)) & 1;
	to_value = spot -48;
	fcol = spot % 8;
	tcol = to_value % 8;
	if(toSpot1 ==0 && toSpot2 == 0 && toSpot3 == 0 && space1 == 1 && space2 ==1 && space3 ==1 && to_value >=0 && fcol == tcol){
		temp = board;
		temp ^= toggle<<spot;
		temp ^= toggle<<(spot-8);
		temp ^= toggle<<(spot-24);
		temp ^= toggle<<(spot-40);
		temp ^= toggle<<(spot-48);
	}
	return temp;
	
}

