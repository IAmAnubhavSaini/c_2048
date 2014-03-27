#include "2048.h"

int GetRandomNumberWeNeed(int n, int m)
{
	int random_number = 0;
	int got_what_we_need = 1;
	// init random numbers generation seed
	srand(time(NULL));

	for(got_what_we_need = 1; got_what_we_need; got_what_we_need = 0 )
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
	for(i = 0; i < SIZE; ++i){
		Tiles[i] = 0;
	}
}

void ShiftRight(void)
{
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
