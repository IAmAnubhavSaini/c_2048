#ifndef C2048_H
#define C2048_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <ncurses.h>

#if CURSED
#define printf printw
#else
#define printf printf
#endif

// D for Dimension
#define D 4 
#define GAMESIZE D*D

static int Tiles[GAMESIZE];

/* we need randomizer */
//int GetRandomNumberWeNeed(int n, int m);
/* we need movement functionality */

/* tiles functionality */
int NoSpaceAvailable(void);
int SpaceAvailable(void);
int NextStep(void);
void InitTiles(void);
void ShiftRight(void);
void ShiftLeft(void);
void ShiftUp(void);
void ShiftDown(void);
void MergeUp(void);
void MergeDown(void);
void MergeLeft(void);
void MergeRight(void);
void PrintTiles(void);

#endif
