#ifndef H_HEXAGON
#define H_HEXAGON

#include <windows.h>
#include <iostream>

#include <fstream>

using namespace std;
const int map_width = 9;
const int map_height = 17;
const int infinity = 100;
/**
*Scan of the playing field from file
*@param map[] - the playing field
*@param file - pointer on file
*/
void Scan_Map(char* map[], ifstream& file);
/**
*Start game
*@param mode - game mode
*	- 1: Computer VS Computer
*	- 2: Human VS Computer
*@param map[] - the playing field
*/
void Play(int mode, char* map[]);
/**
*Printing the playing field on the screen
*@param map[] - the playing field
*/
void Print_Map(char* map[]);
/**
*Repainting of neighboring cells
*@param map[] - the playing field
*@param x - X coordinate of the cell
*@param y - Y coordinate of the cell
*/
void Paint_Cell(char* map[], int x, int y);
/**
*Check of choice of the cell
*@param map[] - the playing field
*@param x - X coordinate of the cell
*@param y - Y coordinate of the cell
*@param player - current player
*@return 1 - if the cell belongs, 0 - if the cell not belongs
*/
bool Check_Choice(char* map[], int x, int y, int player);
/**
*Check of move
*@param map[] - the playing field
*@param x2 - end X coordinate of the cell
*@param y2 - end Y coordinate of the cell
*@param x1 - initial X coordinate of the cell
*@param y1 - initial Y coordinate of the cell
*@param player - current player
*@return 1 - if can move, 0 - if can't move
*/
bool Check_Move(char* map[], int x2, int y2, int x1, int y1, int player);
/**
*Performing of move
*@param map[] - the playing field
*@param x2 - end X coordinate of the cell
*@param y2 - end Y coordinate of the cell
*@param x1 - initial X coordinate of the cell
*@param y1 - initial Y coordinate of the cell
*@param player - current player
*/
void Move(char* map[], int x2, int y2, int x1, int y1, int player);
/**
*Move of human
*@param map[] - the playing field
*/
void Move_Human(char* map[]);
/**
*Check of continue game
*@param map[] - the playing field
*@param player - current player
*@return 1 - if player can continue game, 0 - if player can't continue game
*/
bool Can_Play(char* map[], int player);
/**
*Scoring
*@param map[] - the playing field
*@param player - number of player
*@return score of player
*/
int Score(char* map[], int player);
/**
*Move of computer
*@param map[] - the playing field
*@param level - current level in the tree
*@param depth - search depth
*@param player - whose turn
*@param current_player - current player
*@param alpha - current maximum "alpha"
*@param beta - current minimum "beta"
*@return evaluation function of the current move
*/
int Move_Computer(char* map[], int level, int depth, int player,
	int current_player, int alpha, int beta);
#endif