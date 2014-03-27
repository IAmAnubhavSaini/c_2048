#include "2048.h"

int GetRandomNumberWeNeed(int n, int m)
{
	int random_number = 0;
	int got_what_we_need = 1;
	// init random numbers generation seed
	srand(time(NULL));

	for(got_what_we_need = 1; got_what_we_need; got_what_we_need = 0 ){
		random_number = rand() % GAMESIZE;
		if(Tiles[random_number] == 0){
			got_what_we_need = 1;
		}
	}
	return random_number;
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
		/* TODO : for(j = mes; j > i + D*(D-1); ++j){
			if(Tiles[j] != 0) continue;

			for(k = j+1; k <= 4*i+D-1; ++k){
				if(Tiles[k] != 0) break;
			}
			if(k <= 4*i+D-1 && Tiles[k] != 0){ // put k >= 0 and boom, bad logic
				Tiles[j] = Tiles[k];
				Tiles[k] = 0;
			}
		}
		*/
	}
}
	/*
	int i = 0;
	int j = 0;
	int left, right;
	int mes = D-1; // most eligible space
	for(i = 0; i < D; ++i){
	// outer for is for rows.
		mes = 4*i + D-1;
		for(j = mes, right = 0, left = 0; j >= 4*i; --j){
			if(right && Tiles[j]>0){
				left = j;
			}
			if(!right && Tiles[j]>0){
				right = j;
			}
		}
		for(j = mes; j > 4*i; --j){
			if(Tiles[mes]==Tiles[mes-1]){
				MergeTiles(mes-1, mes);
				--mes; // mes = mes-1;
				--j;
			}
		}
	}
*/

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

int main()
{
	int i = 0;
	for(i=0; i<GAMESIZE; ++i){
		Tiles[i] = 0;
	}
	Tiles[1] = 2;
	Tiles[3] = 2;
	Tiles[6] = 4;
	Tiles[9] = 8;
	Tiles[12] = 16;

	PrintTiles();
	ShiftRight();
	PrintTiles();
	ShiftLeft();
	PrintTiles();
}