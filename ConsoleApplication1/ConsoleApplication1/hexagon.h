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
void scanField(char** field, ifstream& file);

void isWin(char** field, int mode);
/**
*Start game
*@param mode - game mode
*	- 1: Computer VS Computer
*	- 2: Human VS Computer
*@param map[] - the playing field
*/
void playProcess(char** field, int mode);
/**
*Printing the playing field on the screen
*@param map[] - the playing field
*/
void printField(char** field);
/**
*Repainting of neighboring cells
*@param map[] - the playing field
*@param x - X coordinate of the cell
*@param y - Y coordinate of the cell
*/
void paintCell(char** field, int x, int y);
/**
*Check of choice of the cell
*@param map[] - the playing field
*@param x - X coordinate of the cell
*@param y - Y coordinate of the cell
*@param player - current player
*@return 1 - if the cell belongs, 0 - if the cell not belongs
*/
bool checkChoice(char** field, int x, int y, int player);
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
bool checkMove(char** field, int x1, int y1, int x2, int y2, int player);
/**
*Performing of move
*@param map[] - the playing field
*@param x2 - end X coordinate of the cell
*@param y2 - end Y coordinate of the cell
*@param x1 - initial X coordinate of the cell
*@param y1 - initial Y coordinate of the cell
*@param player - current player
*/
void movePlayer(char** field, int x1, int y1, int x2, int y2, int player);
/**
*Move of human
*@param map[] - the playing field
*/
void moveHuman(char** field);
/**
*Check of continue game
*@param map[] - the playing field
*@param player - current player
*@return 1 - if player can continue game, 0 - if player can't continue game
*/
bool generateMoves(char** field, int player);
/**
*Scoring
*@param map[] - the playing field
*@param player - number of player
*@return score of player
*/
int Score(char** field, int player);
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