#include "hexagon.h"
#include <fstream>
#include <Windows.h>
#include <cmath>
using namespace std;

HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

	const int x[18] = { -1, 1, 2, 1, -1, -2, -4, -3, -2, 0, 2, 3, 4, 3, 2, 0, -2, -3 };
	const int y[18] = { 1, 1, 0, -1, -1, 0, 0, 1, 2, 2, 2, 1, 0, -1, -2, -2, -2, -1 };

	const int player1 = 1;
	const int player2 = 2;

//Считывание файла, генерация игрового поля
void scanField(char** field, ifstream& file)
{
	for (int i = 0; i < map_height; i++)
	{
		field[i] = new char[map_height];
	}

	for (int i = 0; i < map_height; i++)
	{
		for (int j = 0; j < map_width; j++) 
		{
			field[i][j] = file.get();
		}
		file.get();
	}
}

void isWin(char** field, int mode)
{
	if (Score(field, 1) > Score(field, 2))
	{
		if (mode == 2)
			cout << "You are WIN!\n" <<"Score : "<<Score(field, 1) <<endl;
		if (mode == 1)
			cout << "Computer(1) is WIN!\n" << "Score : " << Score(field, 1) << endl;
	}
	else if (Score(field, 1) < Score(field, 2))
	{
		if (mode == 2)
			cout << "Computer is WIN!\n" << "Score : " << Score(field, 2) << endl;
		if (mode == 1)
			cout << "Computer(2) is WIN!\n" << "Score : " << Score(field, 2) << endl;
	}

	else 
	{
		cout << "Standoff\n" << Score(field, 1) <<" : " << Score(field, 1) << endl;
	}
}

void playProcess(char** field, int mode)
{
	int compLevel_1 = 1;
	int compLevel_2 = 1;

	if (mode == 2) 
	{
		cout << "Enter the computer level: ";
		cin >> compLevel_2;
	}

	else
	{
		cout << "Enter the computer level(1): ";
		cin >> compLevel_1;
		cout << "Enter the computer level(2): ";
		cin >> compLevel_2;
	}

	system("cls");

	printField(field);

	while (true) 
	{
		if (mode == 2)
		{
			if (generateMoves(field, player1))
			{
				moveHuman(field);
			}
			else
			{
				break;
			}
		}

		else if (generateMoves(field, player1) && mode == 1)
		{
			Move_Computer(field, 1, compLevel_1, 1, player1, -infinity, infinity);
		}

		else
		{
			break;
		}

		if (generateMoves(field, player2))
		{
			Move_Computer(field, 1, compLevel_2, 2, player2, -infinity, infinity);
		}

		else
		{
			break;
		}
	}

	isWin(field, mode);
}

void colorField(char** field, int& i, int& j)
{
		if (field[i][j] == '1')
		{
			SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			cout << '<' << field[i][j] << '>';
		}
		if (field[i][j] == '2')
		{
				SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_INTENSITY);
				cout << '<' << field[i][j] << '>';
		}

		SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);

		if (field[i][j] == '0')
		{
				SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_BLUE);
				cout << '<' << field[i][j] << '>';
		}

		if (field[i][j] == ' ')
		{
				cout << "   ";
		}
}

void printField(char** field) 
{
	cout << "\n       0  1  2  3  4  5  6  7  8 " << endl;
	for (int i = 0; i < map_height; i++) 
	{
		SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);

		if (i < 10)
		{
			cout << "  " << i << "   ";
		}
		else
		{
			cout << " " << i << "   ";
		}
		for (int j = 0; j < map_width; j++)
		{
			colorField(field, i, j);
		}

		cout << endl;
	}
	cout << endl;
}

void paintCell(char** field, int x, int y)
{

	cout << "\n       0  1  2  3  4  5  6  7  8 " << endl;
	for (int i = 0; i < map_height; i++)
	{
		SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		if (i < 10)
		{
			cout << "  " << i << "   ";
		}
		else
		{
			cout <<" "<< i << "   ";
		}
		for (int j = 0; j < map_width; j++)
		{
			if (i == x && j == y) 
			{
				SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);
				cout << '<' << field[i][j] << '>';

				SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			}
			else 
			{
				colorField(field, i, j);
			}
		}
		cout << endl;
	}
	cout << endl;
}

bool checkChoice(char** field, int x, int y, int player)
{
	if (x >= 0 && y >= 0 && x < map_height && y < map_width && field[x][y] == 48 + player)
	{
		system("cls");
		paintCell(field, x, y);
		return true;
	}
	return false;
}

bool checkMove(char** field,  int x1, int y1, int x2, int y2,int player) 
{
	if (x2 >= 0 && y2 >= 0 && x2 < map_height && y2 < map_width && field[x2][y2] == '0' && abs(x1 - x2) <= 4 && abs(y1 - y2) <= 2 && abs(x1 - x2) + abs(y1 - y2) <= 4)
	{
		return true;
	}
	return false;
}

void movePlayer(char** field, int x1, int y1, int x2, int y2, int player)
{
	field[x2][y2] = 48 + player;

	if (abs(x2 - x1) + abs(y2 - y1) > 2 || abs(x2 - x1) + abs(y2 - y1) == 2 && abs(y2 - y1) == 2)
	{
		field[x1][y1] = 48;
	}
	//перекрашивание соседних клеток
	if (x2 - 2 >= 0)
	{
		if (field[x2 - 2][y2] != '0' && field[x2 - 2][y2] != ' ')
			field[x2 - 2][y2] = 48 + player;
	}

	if (x2 - 1 >= 0 && y2 + 1 < map_width)
	{
		if (field[x2 - 1][y2 + 1] != '0' && field[x2 - 1][y2 + 1] != ' ')
		{
			field[x2 - 1][y2 + 1] = 48 + player;
		}
	}

	if (x2 + 1 < map_height && y2 + 1 < map_width)
	{
		if (field[x2 + 1][y2 + 1] != '0' && field[x2 + 1][y2 + 1] != ' ')
		{
			field[x2 + 1][y2 + 1] = 48 + player;
		}
	}

	if (x2 + 2 < map_height)
	{
		if (field[x2 + 2][y2] != '0' && field[x2 + 2][y2] != ' ')
		{
			field[x2 + 2][y2] = 48 + player;
		}
	}

	if (y2 - 1 >= 0 && x2 + 1 < map_height)
	{
		if (field[x2 + 1][y2 - 1] != '0' && field[x2 + 1][y2 - 1] != ' ')
		{
			field[x2 + 1][y2 - 1] = 48 + player;
		}
	}

	if (x2 - 1 >= 0 && y2 - 1 >= 0)
	{
		if (field[x2 - 1][y2 - 1] != '0' && field[x2 - 1][y2 - 1] != ' ')
		{
			field[x2 - 1][y2 - 1] = 48 + player;
		}
	}
}

void moveHuman(char** field) {
	//координаы текущей ячейки
	int x1 = 0 , y1 = 0; 
	//координаты перехода
	int x2 = 0, y2 = 0; 
	while (true) 
	{
		puts("\tSelect the cell coordinates: ");
		cout<<"x = ";
		cin >> x1;
		cout<<"y = ";
		cin >> y1;
		if (checkChoice(field, x1, y1, 1))
		{
			puts("\tMovement coordinates");
			cout<<"x = ";
			cin >> x2;
			cout<<"y = ";
			cin >> y2;
			if (checkMove(field,  x1, y1, x2, y2, 1))
			{
				movePlayer(field, x1, y1, x2, y2, 1);
				system("cls");
				printField(field);
				break;
			}
			else
			{
				system("cls");
				printField(field);

				SetConsoleTextAttribute(hStdOut, FOREGROUND_RED);
				puts( "\tWrong! Try again.");

				SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			}
		}
		else 
		{
			system("cls");
			printField(field);

			SetConsoleTextAttribute(hStdOut, FOREGROUND_RED);
			puts("\tWrong! Try again.");

			SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		}
	}
}

//Проходимся по клеткам и находим возможные ходы
bool generateMoves(char** field, int player)
{

//	int x[18] = { -1, 1, 2, 1, -1, -2, -4, -3, -2, 0, 2, 3, 4, 3, 2, 0, -2, -3 };
//	int y[18] = { 1, 1, 0, -1, -1, 0, 0, 1, 2, 2,  2, 1, 0, -1, -2, -2, -2, -1 };

//	const int amount_move = 18;

	for (int i = 0; i < map_height; i++)
	{
		for (int j = 0; j < map_width; j++) 
		{
			if (field[i][j] == 48 + player)
			{
				for (int k = 0; k < 18; k++)
				{
					if (checkMove(field, i, j, i + x[k], j + y[k], player))
					{
						return true;
					}
				}
			}
		}
	}
	return false;

}

int Score(char** field, int player)
{
	int score = 0;

	for (int i = 0; i < map_height; i++)
	{
		for (int j = 0; j < map_width; j++)
		{
			if (field[i][j] == player + 48)
				score++;
		}
	}

	return score;
}


/*	int score_player1 = 0, score_player2 = 0;
	for (int i = 0; i < map_height; i++)
	{
		for (int j = 0; j < map_width; j++)
		{
			if (field[i][j] == '1')
				score_player1++;
			if (field[i][j] == '2')
				score_player2++;
		}
	}
	if (player == 1)
	{
		return score_player1;
	}
	else if (player == 2)
	{
		return score_player2;
	}
	*/

//		else
//			cout << "Score " << score_player1 << " : " << score_player2 << endl;
//}

int Move_Computer(char* map[], int level, int depth, int player,
	int current_player, int alpha, int beta) {

//	int x[18] = { -1, 1, 2, 1, -1, -2, -4, -3, -2, 0, 2, 3, 4, 3, 2, 0, -2, -3 };
//	int y[18] = { 1, 1, 0, -1, -1, 0, 0, 1, 2, 2,  2, 1, 0, -1, -2, -2, -2, -1 };

	char copy[map_height][map_width];

	const int all_move = 1100;

	const int amount_move = 18;

	int begin_x[all_move];

	int begin_y[all_move];

	int end_x[all_move];

	int end_y[all_move];

	int value[all_move];

	int counter_move = 0, i, j, optimal;

	if (level % 2 == 0)
	{
		optimal = infinity;
	}
	else
	{
		optimal = -infinity;
	}

	for (i = 0; i < map_height; i++)
	{
		for (j = 0; j < map_width; j++)
		{
			copy[i][j] = map[i][j];
		}
	}

	if (level > depth) 
	{
		return Score(map, current_player) - Score(map, (current_player * 2) % 3);
	}

	else
	{
		for (i = 0; i < map_height; i++)
		{
			for (j = 0; j < map_width; j++)
			{
				if (checkChoice(map, i, j, player))
				{
					for (int k = 0; k < amount_move; k++)
					{
						if (alpha > beta)
							return optimal;
						if (checkMove(map,  i, j, i + x[k], j + y[k], player)) 
						{
							begin_x[counter_move] = i;

							begin_y[counter_move] = j;

							end_x[counter_move] = i + x[k];

							end_y[counter_move] = j + y[k];

							movePlayer(map, begin_x[counter_move], begin_y[counter_move], end_x[counter_move], end_y[counter_move], player);

							if (level % 2 == 0)
							{
								value[counter_move] = Move_Computer(map, level + 1, depth, (player * 2) % 3,
									current_player, alpha, beta);
								//optimal = min(optimal, value[counter_move]);

								optimal = ((optimal < value[counter_move]) ? optimal : value[counter_move]);

								value[counter_move] = optimal;
								//beta = min(beta, optimal);

								beta = ((beta < optimal) ? beta : optimal);
							}

							else
							{
								value[counter_move] = Move_Computer(map, level + 1, depth, (player * 2) % 3,
									current_player, alpha, beta);
								//optimal = max(optimal, value[counter_move]);

								optimal = ((optimal > value[counter_move]) ? optimal : value[counter_move]);

								value[counter_move] = optimal;
								//alpha = max(alpha, optimal);

								alpha = ((alpha > optimal) ? alpha : optimal);

							}
							for (int t1 = 0; t1 < map_height; t1++)
							{
								for (int t2 = 0; t2 < map_width; t2++)
								{
									map[t1][t2] = copy[t1][t2];
								}
							}
							counter_move++;
						}
					}
				}
			}
		}

		if (level != 1)
		{
			return optimal;
		}

		if (level == 1 && i == map_height)
		{
			int max_value = value[0], max_index = 0;
			for (int k = 1; k < counter_move; k++)
			{
				if (max_value < value[k]) 
				{
					max_value = value[k];
					max_index = k;
				}
			}
			movePlayer(map, begin_x[max_index], begin_y[max_index], end_x[max_index], end_y[max_index], player);
			system("cls");
			printField(map);
		}
	}
}