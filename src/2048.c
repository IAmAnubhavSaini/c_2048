#include "2048.h"

int NoSpaceAvailable(void)
{
	int i = 0;
	int allFill = 1;

	for(i = 0, allFill = 1; i < GAMESIZE && allFill; ++i){
		if(Tiles[i] == 0){
			allFill = 0;
		}
	}

	return allFill;
}

int SpaceAvailable(void)
{
	return !NoSpaceAvailable();
}

int NextStep(void)
{
	int random_loc = 0;
	int got_what_we_need = 1;
	// init random numbers generation seed

	if(NoSpaceAvailable()) return 0;

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
	// most eligible space
	int mes = 0;
	
	for(i = 0; i < D; ++i){
		mes = 4*i + D-1;
		for(j = mes; j > 4*i; --j){
			if(Tiles[j] != 0) continue;

			for(k = j-1; k >= 4*i; --k){
				if(Tiles[k] != 0) break;
			}
			if(k >= 4*i && Tiles[k] != 0){ // put k >= 0 and boom, bad logic
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
	// most eligible space
	int mes = 0;
	
	for(i = 0; i < D; ++i){
		mes = 4*i + 0;
		for(j = mes; j < 4*i + D-1; ++j){
			if(Tiles[j] != 0) continue;

			for(k = j+1; k <= 4*i+D-1; ++k){
				if(Tiles[k] != 0) break;
			}
			if(k <= 4*i+D-1 && Tiles[k] != 0){ // put k >= 0 and boom, bad logic
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
	// most eligible space
	int mes = 0;
	
	for(i = 0; i < D; ++i){
		mes = i + D*(D-1);
		for(j = mes; j >  i; j-=4){
			if(Tiles[j] != 0) continue;

			for(k = j-4; k >= i; k-=4){
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
		for(j = i; j < D*(D-1) + i; j += 4){
			if(Tiles[j] != 0) continue;
			for(k = j+4; k <= D*(D-1)+i; k += 4){
				if(Tiles[k] != 0) break;
			}
			if(k <= D*(D-1)+i && Tiles[k]!= 0){
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
		for(j = 4*i + D-1; j > 4*i; --j){
			if(Tiles[j]==0) continue;
			for(k = j-1; k >= 4*i; --k){
				if(Tiles[k]==0) continue;
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
		for(j = 4*i; j < 4*i + D-1; ++j){
			if(Tiles[j] == 0) continue;
			for(k = j+1; k <= 4*i + D-1; ++k){
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
		for(j = D*(D-1) + i; j > i; j -= D){
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
		for(j = i; j < D*(D-1) + i; j += D){
			if(Tiles[j] == 0) continue;
			for(k = j + D; k <= D*(D-1) + i; k += D){
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
	for(i = 0; i < D; ++i){
		for(j = 0; j < D; ++j){
			printf("%6d", Tiles[D*i+j]);
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
		printf("\n\n\n");
		if(!NextStep()){
			break;
		}
		PrintTiles();
		userChoice = getchar();
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
		printf("\n\n\n");
	}
	while(SpaceAvailable() && userChoice != 'k');
	printf("\nGame over.\n");
}

int main()
{
	PlayGame();
}
