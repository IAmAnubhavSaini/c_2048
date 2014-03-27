#ifndef 2048_H
#define 2048_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

// D for Dimension
#define D 4 
#define GAMESIZE D*D

static int Tiles[GAMESIZE];

/* we need randomizer */
int GetRandomNumberWeNeed(int n, int m);
/* we need movement functionality */

/* tiles functionality */
void InitTiles(void);
void ShiftRight(void);
void ShiftLeft(void);
void ShiftUp(void);
void ShiftDown(void);
void MergeTiles(int this, int tothis);
void PrintTiles(void);

#endif
