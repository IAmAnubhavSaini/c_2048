#include "2048.h"

int isNoSpaceAvailable(void)
{
	int i = 0;
	int full = 1;

	for(i = 0, full = 1; i < GAMESIZE && full; ++i){
		if(Tiles[i] == 0){
			full = 0;
		}
	}

	return full;
}

int isSpaceAvailable(void)
{
	return !isNoSpaceAvailable();
}

int NextStep(void)
/* This function is bonkers. Look at the got_what_we_need thingy.
 * It doesn't make sense at all.
 */
{
	int random_loc = 0;
	int got_what_we_need = 1;
	// init random numbers generation seed

	if(isNoSpaceAvailable()) return 0;

	srand(time(NULL));


	for(got_what_we_need = 1; got_what_we_need; got_what_we_need = 0 ){
		random_loc = rand() % GAMESIZE;
		if(Tiles[random_loc] == 0){
			Tiles[random_loc] = 2;
			got_what_we_need = 1;
		}
	}
	return 1; // yes, we got what we need.
}

void InitTiles(void)
{
	int i = 0;
	for(i = 0; i < GAMESIZE; ++i){
		Tiles[i] = 0;
	}
}

void ShiftRight(void)
{
	int i = 0;
	int j = 0;
	int k = 0;
	int mostEligibleSpace = 0;

	for(i = 0; i < D; ++i){
		mostEligibleSpace = 4 * i + D - 1;
		for(j = mostEligibleSpace; j > 4 * i; --j){
			if(Tiles[j] != 0) continue;

			for(k = j - 1; k >= 4 * i; --k){
				if(Tiles[k] != 0) break;
			}
			if(k >= 4 * i && Tiles[k] != 0){ // put k >= 0 and boom, bad logic
				Tiles[j] = Tiles[k];
				Tiles[k] = 0;
			}
		}
	}
}

void ShiftLeft(void)
{
	int i = 0;
	int j = 0;
	int k = 0;
	int mostEligibleSpace = 0;

	for(i = 0; i < D; ++i){
		mostEligibleSpace = 4 * i + 0;
		for(j = mostEligibleSpace; j < 4 * i + D - 1; ++j){
			if(Tiles[j] != 0) continue;

			for(k = j + 1; k <= 4 * i + D - 1; ++k){
				if(Tiles[k] != 0) break;
			}
			if(k <= 4 * i + D - 1 && Tiles[k] != 0){ // put k >= 0 and boom, bad logic
				Tiles[j] = Tiles[k];
				Tiles[k] = 0;
			}
		}
	}
}

void ShiftDown(void)
{
	int i = 0;
	int j = 0;
	int k = 0;
	int mostEligibleSpace = 0;

	for(i = 0; i < D; ++i){
		mostEligibleSpace = i + D * (D - 1);
		for(j = mostEligibleSpace; j >  i; j -= 4){
			if(Tiles[j] != 0) continue;

			for(k = j - 4; k >= i; k -= 4){
				if(Tiles[k] != 0) break;
			}
			if(k >= i && Tiles[k] != 0){ // put k >= 0 and boom, bad logic
				Tiles[j] = Tiles[k];
				Tiles[k] = 0;
			}
		}
	}
}

void ShiftUp(void)
{
	int i = 0;
	int j = 0;
	int k = 0;

	for(i = 0; i < D; ++i){
		for(j = i; j < D * (D - 1) + i; j += 4){
			if(Tiles[j] != 0) continue;
			for(k = j + 4; k <= D * (D - 1) + i; k += 4){
				if(Tiles[k] != 0) break;
			}
			if(k <= D * (D - 1) + i && Tiles[k]!= 0){
				Tiles[j] = Tiles[k];
				Tiles[k] = 0;
			}
		}
	}
}

void MergeRight(void)
{
	int i = 0;
	int j = 0;
	int k = 0;

	for(i = 0; i < D; ++i){
		for(j = 4 * i + D - 1; j > 4 * i; --j){
			if(Tiles[j] == 0) continue;
			for(k = j - 1; k >= 4 * i; --k){
				if(Tiles[k] == 0) continue;
				if(Tiles[k] == Tiles[j]){
					Tiles[j] *= 2;
					Tiles[k] = 0;
					j = k;
				}
				break;
			}
		}
	}

}

void MergeLeft(void)
{
	int i = 0;
	int j = 0;
	int k = 0;

	for(i = 0; i < D; ++i){
		for(j = 4 * i; j < 4 * i + D - 1; ++j){
			if(Tiles[j] == 0) continue;
			for(k = j + 1; k <= 4 * i + D - 1; ++k){
				if(Tiles[k] == 0) continue;
				if(Tiles[j] == Tiles[k]){
					Tiles[j] *= 2;
					Tiles[k] = 0;
					j = k;
				}
				break;
			}
		}
	}

}

void MergeDown(void)
{
	int i = 0;
	int j = 0;
	int k = 0;

	for(i = 0; i < D; ++i){
		for(j = D * (D - 1) + i; j > i; j -= D){
			if(Tiles[j] == 0) continue;
			for(k = j - D; k >= i; k -= D){
				if(Tiles[k] == 0) continue;
				if(Tiles[j] == Tiles[k]){
					Tiles[j] *= 2;
					Tiles[k] = 0;
					j = k;
				}
				break;
			}
		}
	}
}

void MergeUp(void)
{
	int i = 0;
	int j = 0;
	int k = 0;

	for(i = 0; i < D; ++i){
		for(j = i; j < D * (D - 1) + i; j += D){
			if(Tiles[j] == 0) continue;
			for(k = j + D; k <= D * (D - 1) + i; k += D){
				if(Tiles[k] == 0) continue;
				if(Tiles[j] == Tiles[k]){
					Tiles[j] *= 2;
					Tiles[k] = 0;
					j = k;
				}
				break;
			}
		}
	}


}

void PrintTiles()
{
	int i = D, j = D;
	int val = 0, pair = 0;
	start_color();
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_YELLOW, COLOR_BLACK);

	for(i = 0; i < D; ++i){
		for(j = 0; j < D; ++j){
			val = Tiles[D * i + j];
			pair = 0;
			if(val >= 512){
				pair = 2;
			} else if(val >= 32){
				pair = 1;
			}
			if(pair)
			attron(COLOR_PAIR(pair));
			printf("%6d", val);
			if(pair)
			attroff(COLOR_PAIR(pair));

		}
		printf("\n\n");
	}
}

void PlayGame()
{
	char userChoice = 'k';
	printf("Going to start game. Use AD for left, right. WS for up, down.\n");
	printf("k to kill game.\n");
	InitTiles();
	NextStep();
	do{

		if(!NextStep()){
			break;
		}
		PrintTiles();
		refresh();	// printing on screen - via ncurses.
		userChoice = getch();
//		if(userChoice=='\n') userChoice = getchar();
		switch(userChoice){
		case 'a':
		case 'A':
			MergeLeft(); ShiftLeft(); break;
		case 'd':
		case 'D':
			MergeRight(); ShiftRight(); break;
		case 'w':
		case 'W':
			MergeUp(); ShiftUp(); break;
		case 's':
		case 'S':
			MergeDown(); ShiftDown(); break;
		}
		clear();
	}
	while(isSpaceAvailable() && userChoice != 'k');
	printf("\nGame over.\n");

}

int main()
{
	initscr();

	noecho();

	PlayGame();
	endwin();
}
