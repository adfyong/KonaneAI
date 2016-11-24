#include "board.h"
#include "search.h"
#include "heuristic.h"

int main(int argc, char **argv){
	uint64_t board =0;
	FILE *boardf;

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
	if (argv[2][0] == 'B'){     
		board = makeInitialMove(board, 28, 'W');
		char fletter;
		int fnumb;
		char tletter;
		int tnumb;
		uint64_t temp =0;
		printBoard(board);
		while(temp ==0){
			printf("Enter your desired initial move(e4, d5): ");
			scanf(" %c %d", &fletter, &fnumb);
			temp = makeInitialMove(board, findValue(fletter, fnumb), argv[2][0]);
		}
		board = temp;
		printBoard(board);
		temp =0;
		int i;
		for(i = 0; i<10; i++){
			board = alpha_beta_search(board, count_movable, 0);
			printBoard(board);
			
			while(temp ==0){
				printf("Enter your desired  move(from to): ");
				scanf(" %c %d %c %d", &fletter, &fnumb, &tletter, &tnumb);
				//printf("%c %d %c %d\n", fletter, fnumb, tletter, tnumb);
				
				//int from = findValue(fletter, fnumb);
				//int to = findValue(tletter, tnumb);
				//printf("%d %d\n", from, to);
				temp = makeMove(board, findValue(fletter, fnumb), findValue(tletter, tnumb), argv[2][0]);
				
				printf("\n\n");
			}
			board = temp;
			temp =0;
			printBoard(board);
		}
	
	}
	else if(argv[2][0] == 'W'){
		char fletter;
		int fnumb;
		char tletter;
		int tnumb;
		uint64_t temp =0;
		while(temp ==0){
			printBoard(board);
			printf("Enter your desired initial move(d4, e5): ");
			scanf(" %c %d", &fletter, &fnumb);
			temp = makeInitialMove(board, findValue(fletter, fnumb), argv[2][0]);
		}
		board = temp;
		printBoard(board);
		board = makeInitialMove(board, 27, 'B');
		printBoard(board);
		temp =0;
		int i;
		for(i = 0; i<3; i++){
			while(temp ==0){
				printf("Enter your desired  move(from to): ");
				scanf(" %c %d %c %d", &fletter, &fnumb, &tletter, &tnumb);
				//printf("%c %d %c %d\n", fletter, fnumb, tletter, tnumb);
				
				//int from = findValue(fletter, fnumb);
				//int to = findValue(tletter, tnumb);
				//printf("%d %d\n", from, to);
				temp = makeMove(board, findValue(fletter, fnumb), findValue(tletter, tnumb), argv[2][0]);
				
				printf("\n\n");
			}
			board = temp;
			temp =0;
			printBoard(board);
			board = alpha_beta_search(board, count_movable, 1);
			printBoard(board);
		}
	}

	
//printf("%" PRIx64 "\n", alpha_beta_search(board, count_movable, 1));
	
}
