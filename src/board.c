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
	for (int i = 0; i < 64; ++i) {
		if (!(from & (o << i)) && to & (o << i)) {
			move[0] = move[1] = i;
			break;
		}
	}

	// up
	while (move[0] < 48 && (from & (o << (move[0]+16))) &&
			!(to & (o << (move[0]+16)))) {
		move[0] += 16;
	}
	if (move[0] != move[1]) return;

	// left
	if ((move[0]%8 < 6) && (from & (o << (move[0]+2))) &&
			!(to & (o << (move[0]+2)))) {
		move[0] += 2;
	}
	if (move[0] != move[1]) return;

	// down
	while (move[0] > 15 && (from & (o << (move[0]-16))) &&
			!(to & (o << (move[0]-16)))) {
		move[0] -= 16;
	}
	if (move[0] != move[1]) return;

	// right
	if ((move[0]%8 > 1) && (from & (o << (move[0]-2))) &&
			!(to & (o << (move[0]-2)))) {
		move[0] -= 2;
	}
	return;
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
//bool gameOver(uint64_t board, int argc){
//	return true;
//}
int findValue(char argc, int argv){
	int value;
	//	printf("%i\n", argc);
	value = (7-((int)argc-97))+((argv-1)*8);
	//printf("%d \n", value);
	return value;

}

char findColor(int argc){
	char color;
	int row = argc /8;
	int col = argc % 8;
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

uint64_t makeMove(uint64_t board, int argc, int argv, char argv1){
	uint64_t temp = 0;
	uint64_t toggle = 1;
	int diff = argv - argc;
	int frow = argc /8;
	int fcol = argc % 8;
	int trow = argv /8;
	int tcol = argv %8;
	int spotV;
	if(findColor(argc) == argv1 && findColor(argv)== argv1 && argc >=0 && argc<=63 && argv >=0 && argv <=63){
		switch(diff){
		case 16:
			if(tcol == fcol){
				spotV = (board >>(argc+8)) & 1;
				if(spotV ==1){
					temp = board;
					temp ^= toggle<<argc;
					temp ^=  toggle<<(argc+8);
					temp ^=  toggle<<argv;
					return temp;
					break;
				}
			}
		case -16:
			if(tcol == fcol){
				spotV = (board >>(argc-8)) & 1;
				if(spotV ==1){
					temp = board;
					temp ^= toggle<<argc;
					temp ^=  toggle<<(argc-8);
					temp ^=  toggle<<argv;
					return temp;
					break;
				}
			}
		case 2:
			if(trow == frow){
				spotV = (board >>(argc +1)) & 1;
				if(spotV ==1){
					temp = board;
					temp ^= toggle<<argc;
					temp ^=  toggle<<(argc+1);
					temp ^=  toggle<<argv;
					return temp;
					break;
				}
			}
		case -2:
			if(trow == frow){
				spotV = (board >>(argc-1)) & 1;
				if(spotV ==1){
					temp = board;
					temp ^= toggle<<argc;
					temp ^=  toggle<<(argc-1);
					temp ^=  toggle<<argv;
					return temp;
					break;
				}
			}
			
		}
	}
	return temp;
}
uint64_t makeInitialMove(uint64_t board, int argc, char argv){
	uint64_t temp =0;
	uint64_t toggle =1;
	if(argv == findColor(argc)){
		temp =board;
		temp ^= toggle<<argc;
		return temp;
	}
	return temp;
}
void getMoves(int argc, uint64_t board, uint64_t *moves){
	int bSpaces[33]= {0, 2, 4, 6, 9, 11, 13, 15, 16, 18, 20, 22, 25, 27, 29, 31, 32, 34, 36, 38, 41, 43, 45, 47, 48, 50, 52, 54, 57, 59, 61, 63};
	int wSpaces[33] = {1, 3, 5, 7, 8, 10, 12, 14, 17, 19, 21, 23, 24, 26, 28, 30, 31, 33, 35, 37, 39, 40, 42, 44, 46, 49, 51, 53, 55, 56, 58, 60, 62};
	int type;
	uint64_t spotV = 0;
	moves[0]=0;
	if (argc == 1){
		for(int i = 0; i<32; i = i +1){
			spotV = (board>>bSpaces[i]) &1;
			if (spotV ==1){
				type = getType(bSpaces[i]);
				getPieceMoves(type, bSpaces[i], board, moves);
			}}
	       
	}

	if (argc == 0){
		for(int i = 0; i<32; i=i+1){
	       	spotV = (board>>wSpaces[i]) &1;
			if (spotV ==1){
				type = getType(wSpaces[i]);
				getPieceMoves(type, wSpaces[i], board, moves);
			}}
		}
}

void getPieceMoves(int type, int spot, uint64_t board,uint64_t *moves){
	uint64_t temp;
	int count = moves[0]+1;
	switch(type){
	case 1:
		temp = findRight(spot, board);
		if (temp != 0){
			moves[count] = temp;
			count +=1;
		}
		temp = findDoubleRight(spot, board);
		if (temp != 0){
			moves[count] = temp;
			count +=1;
		}
		temp = findDown(spot, board);
		if (temp != 0){
			moves[count] = temp;
			count +=1;
		}
		temp = findDoubleDown(spot, board);
		if (temp != 0){
			moves[count] = temp;
			count +=1;
		}
		moves[0]=count-1;
		//return moves;
		break;
	case 2:
		temp = findRight(spot, board);
		if (temp != 0){
			moves[count] = temp;
			count +=1;
		}
		temp = findDoubleRight(spot, board);
		if (temp != 0){
			moves[count] = temp;
			count +=1;
		}
		temp = findUp(spot, board);
		if (temp != 0){
			moves[count] = temp;
			count +=1;
		}
		temp = findDoubleUp(spot, board);
		if (temp != 0){
			moves[count] = temp;
			count +=1;
		}
				moves[0]=count-1;
				//return moves;
		break;
	case 3:
		temp = findLeft(spot, board);
		if (temp != 0){
			moves[count] = temp;
			count +=1;
		}
		temp = findDoubleLeft(spot, board);
		if (temp != 0){
			moves[count] = temp;
			count +=1;
		}
		temp = findDown(spot, board);
		if (temp != 0){
			moves[count] = temp;
			count +=1;
		}
		temp = findDoubleDown(spot, board);
		if (temp != 0){
			moves[count] = temp;
			count +=1;
		}
		moves[0]=count-1;
		//	return moves;
		break;
	case 4:
		temp = findLeft(spot, board);
		if (temp != 0){
			moves[count] = temp;
			count +=1;
		}
		temp = findDoubleLeft(spot, board);
		if (temp != 0){
			moves[count] = temp;
			count +=1;
		}
		temp = findUp(spot, board);
		if (temp != 0){
			moves[count] = temp;
			count +=1;
		}
		temp = findDoubleUp(spot, board);
		if (temp != 0){
			moves[count] = temp;
			count +=1;
		}
		moves[0]=count-1;
		//		return moves;
		break;
	case 5:
		temp = findRight(spot, board);
		if (temp != 0){
			moves[count] = temp;
			count +=1;
		}
		temp = findDoubleRight(spot, board);
		if (temp != 0){
			moves[count] = temp;
			count +=1;
		}
		temp = findLeft(spot, board);
		if (temp != 0){
			moves[count] = temp;
			count +=1;
		}
		temp = findDoubleLeft(spot, board);
		if (temp != 0){
			moves[count] = temp;
			count +=1;
		}
		temp = findDown(spot, board);
		if (temp != 0){
			moves[count] = temp;
			count +=1;
		}
		temp = findDoubleDown(spot, board);
		if (temp != 0){
			moves[count] = temp;
			count +=1;
		}
		moves[0]=count-1;
		//		return moves;
		break;
	case 6:
		temp = findRight(spot, board);
		if (temp != 0){
			moves[count] = temp;
			count +=1;
		}
		temp = findDoubleRight(spot, board);
		if (temp != 0){
			moves[count] = temp;
			count +=1;
		}
		temp = findLeft(spot, board);
		if (temp != 0){
			moves[count] = temp;
			count +=1;
		}
		temp = findDoubleLeft(spot, board);
		if (temp != 0){
			moves[count] = temp;
			count +=1;
		}
		temp = findUp(spot, board);
		if (temp != 0){
			moves[count] = temp;
			count +=1;
		}
		temp = findDoubleUp(spot, board);
		if (temp != 0){
			moves[count] = temp;
			count +=1;
		}
		moves[0]=count-1;
		//		return moves;
		break;
	case 7:
		temp = findRight(spot, board);
		if (temp != 0){
			moves[count] = temp;
			count +=1;
		}
		temp = findDoubleRight(spot, board);
		if (temp != 0){
			moves[count] = temp;
			count +=1;
		}
		temp = findDown(spot, board);
		if (temp != 0){
			moves[count] = temp;
			count +=1;
		}
		temp = findDoubleDown(spot, board);
		if (temp != 0){
			moves[count] = temp;
			count +=1;
		}
		temp = findUp(spot, board);
		if (temp != 0){
			moves[count] = temp;
			count +=1;
		}
		temp = findDoubleUp(spot, board);
		if (temp != 0){
			moves[count] = temp;
			count +=1;
		}
		moves[0]=count-1;
		//	return moves;
		break;
	case 8:
		temp = findDown(spot, board);
		if (temp != 0){
			moves[count] = temp;
			count +=1;
		}
		temp = findDoubleDown(spot, board);
		if (temp != 0){
			moves[count] = temp;
			count +=1;
		}
		temp = findLeft(spot, board);
		if (temp != 0){
			moves[count] = temp;
			count +=1;
		}
		temp = findDoubleLeft(spot, board);
		if (temp != 0){
			moves[count] = temp;
			count +=1;
		}
		temp = findUp(spot, board);
		if (temp != 0){
			moves[count] = temp;
			count +=1;
		}
		temp = findDoubleUp(spot, board);
		if (temp != 0){
			moves[count] = temp;
			count +=1;
		}
		moves[0]=count-1;
		//		return moves;
		break;
	case 9:
		temp = findRight(spot, board);
		if (temp != 0){
			moves[count] = temp;
			count +=1;
		}
		temp = findDoubleRight(spot, board);
		if (temp != 0){
			moves[count] = temp;
			count +=1;
		}
		temp = findLeft(spot, board);
		if (temp != 0){
			moves[count] = temp;
			count +=1;
		}
		temp = findDoubleLeft(spot, board);
		if (temp != 0){
			moves[count] = temp;
			count +=1;
		}
		temp = findUp(spot, board);
		if (temp != 0){
			moves[count] = temp;
			count +=1;
		}
		temp = findDoubleUp(spot, board);
		if (temp != 0){
			moves[count] = temp;
			count +=1;
		}
		temp = findDown(spot, board);
		if (temp != 0){
			moves[count] = temp;
			count +=1;
		}
		temp = findDoubleDown(spot, board);
		if (temp != 0){
			moves[count] = temp;
			count +=1;
		}
		moves[0]=count-1;
		//	return moves;
		break;
	}
	}
uint64_t findRight(int spot, uint64_t board){
	int toSpot;
	int spaceSpot;
	uint64_t toggle= 1;
	uint64_t temp=0;
	toSpot = (board>>(spot-2)) & 1;
	spaceSpot = (board >>(spot-1)) & 1;
	if (toSpot ==0 && spaceSpot ==1){
		temp = board;
		temp ^= toggle<<spot;
		temp ^=  toggle<<(spot-1);
		temp ^=  toggle<<(spot-2);
	}
	return temp;
}
uint64_t findDoubleRight(int spot, uint64_t board){
	int toSpot;
	int spaceSpot;
	int doubleTo;
	int doubleSpace;
	int spotCol;
	int toCol;
	uint64_t toggle =1;
	uint64_t temp = 0;

	toSpot = (board>>(spot-2)) & 1;
	spaceSpot = (board >>(spot-1)) & 1;
	doubleTo = (board >>(spot-4))&1;
	doubleSpace = (board >>(spot-3))&1;
	spotCol = spot /8;
	toCol = (spot -4)/8;
	if (toSpot ==0 && spaceSpot ==1 && doubleTo ==0 && doubleSpace ==1 && toCol==spotCol && (spot-4)>=0){
		temp = board;
		toggle ^= toggle<<spot;
		temp ^= toggle<<(spot-1);
		temp ^= toggle<<(spot -3);
		temp ^= toggle<< (spot-4);
	}
	return temp;
}


uint64_t findLeft(int spot, uint64_t board){
	int toSpot;
	int spaceSpot;
	uint64_t toggle= 1;
	uint64_t temp=0;
	toSpot = (board>>(spot+2)) & 1;
	spaceSpot = (board >>(spot+1)) & 1;
	if (toSpot ==0 && spaceSpot ==1){
		temp = board;
		temp ^= toggle<<spot;
		temp ^=  toggle<<(spot+1);
		temp ^=  toggle<<(spot+2);
	}
	return temp;
}
uint64_t findDoubleLeft(int spot, uint64_t board){
	int toSpot;
	int spaceSpot;
	int doubleTo;
	int doubleSpace;
	int toCol;
	int spotCol;
	uint64_t toggle =1;
	uint64_t temp = 0;
	toSpot = (board>>(spot+2)) & 1;
	spaceSpot = (board >>(spot+1)) & 1;
	doubleTo = (board >>(spot+4))&1;
	doubleSpace = (board >>(spot+3))&1;
	spotCol = spot /8;
	toCol = (spot+4)/8;
	if (toSpot ==0 && spaceSpot ==1 && doubleTo ==0 && doubleSpace ==1 && toCol == spotCol && (spot+4)<=63){
		temp = board;
		toggle ^= toggle<<spot;
		temp ^= toggle<<(spot+1);
		temp ^= toggle<<(spot +3);
		temp ^= toggle<< (spot+4);
	}
	return temp;
}

uint64_t findUp(int spot, uint64_t board){
	int toSpot;
	int spaceSpot;
	uint64_t toggle= 1;
	uint64_t temp=0;
	toSpot = (board>>(spot+16)) & 1;
	spaceSpot = (board >>(spot+8)) & 1;
	if (toSpot ==0 && spaceSpot ==1){
		temp = board;
		temp ^= toggle<<spot;
		temp ^=  toggle<<(spot+8);
		temp ^=  toggle<<(spot+16);
	}
	return temp;

}
uint64_t findDoubleUp(int spot, uint64_t board){
	int toSpot;
	int spaceSpot;
	int doubleTo;
	int doubleSpace;
	int toRow;
	int spotRow;
	uint64_t toggle =1;
	uint64_t temp = 0;
	toSpot = (board>>(spot+16)) & 1;
	spaceSpot = (board >>(spot+8)) & 1;
	doubleTo = (board >>(spot+32))&1;
	doubleSpace = (board >>(spot+24))&1;
	spotRow = spot % 8;
	toRow = (spot +32) % 8;
	if (toSpot ==0 && spaceSpot ==1 && doubleTo ==0 && doubleSpace ==1 && spotRow == toRow && (spot+32)<=63){
		temp = board;
		toggle ^= toggle<<spot;
		temp ^= toggle<<(spot+8);
		temp ^= toggle<<(spot +24);
		temp ^= toggle<< (spot+32);
	}
	return temp;
}

uint64_t findDown(int spot, uint64_t board){
	int toSpot;
	int spaceSpot;
	uint64_t toggle= 1;
	uint64_t temp=0;
	toSpot = (board>>(spot-16)) & 1;
	spaceSpot = (board >>(spot-8)) & 1;
	if (toSpot ==0 && spaceSpot ==1){
		temp = board;
		temp ^= toggle<<spot;
		temp ^=  toggle<<(spot-8);
		temp ^=  toggle<<(spot-16);
	}
	return temp;
}
uint64_t findDoubleDown(int spot, uint64_t board){
	int toSpot;
	int spaceSpot;
	int doubleTo;
	int doubleSpace;
	int toRow;
	int spotRow;
	uint64_t toggle =1;
	uint64_t temp = 0;
	toSpot = (board>>(spot-16)) & 1;
	spaceSpot = (board >>(spot-8)) & 1;
	doubleTo = (board >>(spot-32))&1;
	doubleSpace = (board >>(spot-24))&1;
	spotRow = spot % 8;
	toRow = (spot-32)% 8;
	if (toSpot ==0 && spaceSpot ==1 && doubleTo ==0 && doubleSpace ==1 && toRow == spotRow && (spot-32)>=0){
		temp = board;
		toggle ^= toggle<<spot;
		temp ^= toggle<<(spot-8);
		temp ^= toggle<<(spot -24);
		temp ^= toggle<< (spot-32);
	}
	return temp;
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
