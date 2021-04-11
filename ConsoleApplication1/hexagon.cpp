#include "hexagon.h"
#include <fstream>

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
void Scan_Map(char* map[],ifstream& file) {
	int i, j;
	for (i = 0; i < map_height; i++)
		map[i] = new char[map_height];
	for (i = 0; i < map_height; i++) {
		for (j = 0; j < map_width; j++) {
			//map[i][j] = fgetc(file);
			map[i][j] = file.get();
		}
		//fgetc(file);
		file.get();
	}
}
void Play(int mode, char* map[]) {
	int i, j, level_computer1, count1 = 0, level_computer2;
	const int player1 = 1;
	const int player2 = 2;
	if (mode == 2) {
		cout << "Input the level of Computer: ";
		cin >> level_computer2;
	}
	else {
		cout << "Input the level of Computer(1): ";
		cin >> level_computer1;
		cout << "Input the level of Computer(2): ";
		cin >> level_computer2;
	}
	system("cls");
	Print_Map(map);
	while (true) {
		if (mode == 2) {
			if (Can_Play(map, player1)) {
				Move_Human(map);
				//getchar();
				//getchar();
			}
			else
				break;
		}
		else
			if (Can_Play(map, player1) && mode == 1) {
				Move_Computer(map, 1, level_computer1, 1, player1,
					-infinity, infinity);
			}
			else
				break;
		if (Can_Play(map, player2)) {
			Move_Computer(map, 1, level_computer2, 2, player2,
				-infinity, infinity);
		}
		else
			break;
	}
	if (Score(map, player1) > Score(map, player2)) {
		if (mode == 2)
			cout << "You are WIN!" << endl;
		if (mode == 1)
			cout << "Computer(1) is WIN!" << endl;
	}
	else {
		if (mode == 2)
			cout << "Computer is WIN!" << endl;
		if (mode == 1)
			cout << "Computer(2) is WIN!" << endl;
	}
}
void Print_Map(char* map[]) {
	cout << "      0  1  2  3  4  5  6  7  8 " << endl;
	for (int i = 0; i < map_height; i++) {
		if (i < 10)
			cout << i << "    ";
		else
			cout << i << "   ";
		for (int j = 0; j < map_width; j++) {
			if (map[i][j] == '1') {
				SetConsoleTextAttribute(hConsole, (WORD)((15 << 4) | 1));
				cout << '<' << map[i][j] << '>';
			}
			if (map[i][j] == '2') {
				SetConsoleTextAttribute(hConsole, (WORD)((15 << 4) | 12));
				cout << '<' << map[i][j] << '>';
			}
			SetConsoleTextAttribute(hConsole, (WORD)((15 << 4) | 7));
			if (map[i][j] == '0')
				cout << '<' << map[i][j] << '>';
			if (map[i][j] == ' ')
				cout << "   ";
		}
		cout << endl;
	}
	cout << endl;
}
void Paint_Cell(char* map[], int x, int y) {
	cout << "      0  1  2  3  4  5  6  7  8 " << endl;
	for (int i = 0; i < map_height; i++) {
		if (i < 10)
			cout << i << "    ";
		else
			cout << i << "   ";
		for (int j = 0; j < map_width; j++) {
			if (i == x && j == y) {
				SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 4));
				cout << '<' << map[i][j] << '>';
				SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 15));
			}
			else {
				if (map[i][j] == '1') {
					SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 5));
					cout << '<' << map[i][j] << '>';
				}
				if (map[i][j] == '2') {
					SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 2));
					cout << '<' << map[i][j] << '>';
				}
				SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 15));
				if (map[i][j] == '0')
					cout << '<' << map[i][j] << '>';
				if (map[i][j] == ' ')
					cout << "   ";
			}
		}
		cout << endl;
	}
}

bool Check_Choice(char* map[], int x, int y, int player) {
	if (x >= 0 && y >= 0 && x < map_height && y < map_width &&
		map[x][y] == 48 + player) {
		system("cls");
		Paint_Cell(map, x, y);
		return 1;
	}
	return 0;
}

bool Check_Move(char* map[], int x2, int y2, int x1, int y1, int player) {
	if (x2 >= 0 && y2 >= 0 && x2 < map_height && y2 < map_width &&
		map[x2][y2] == '0' && abs(x1 - x2) <= 4 && abs(y1 - y2) <= 2 &&
		abs(x1 - x2) + abs(y1 - y2) <= 4)
		return 1;
	return 0;
}

void Move(char* map[], int x2, int y2, int x1, int y1, int player) {
	map[x2][y2] = 48 + player;
	if (abs(x2 - x1) + abs(y2 - y1) > 2 || abs(x2 - x1) + abs(y2 - y1) == 2 &&
		abs(y2 - y1) == 2)
		map[x1][y1] = 48;
	//перекрашивание соседних клеток
	if (x2 - 2 >= 0)
		if (map[x2 - 2][y2] != '0' && map[x2 - 2][y2] != ' ')
			map[x2 - 2][y2] = 48 + player;
	if (x2 - 1 >= 0 && y2 + 1 < map_width)
		if (map[x2 - 1][y2 + 1] != '0' && map[x2 - 1][y2 + 1] != ' ')
			map[x2 - 1][y2 + 1] = 48 + player;
	if (x2 + 1 < map_height && y2 + 1 < map_width)
		if (map[x2 + 1][y2 + 1] != '0' && map[x2 + 1][y2 + 1] != ' ')
			map[x2 + 1][y2 + 1] = 48 + player;
	if (x2 + 2 < map_height)
		if (map[x2 + 2][y2] != '0' && map[x2 + 2][y2] != ' ')
			map[x2 + 2][y2] = 48 + player;
	if (y2 - 1 >= 0 && x2 + 1 < map_height)
		if (map[x2 + 1][y2 - 1] != '0' && map[x2 + 1][y2 - 1] != ' ')
			map[x2 + 1][y2 - 1] = 48 + player;
	if (x2 - 1 >= 0 && y2 - 1 >= 0)
		if (map[x2 - 1][y2 - 1] != '0' && map[x2 - 1][y2 - 1] != ' ')
			map[x2 - 1][y2 - 1] = 48 + player;
}

void Move_Human(char* map[]) {
	int x1, y1; //координаы текущей €чейки
	int x2, y2; //координаты перехода
	while (true) {
		cout << "Choose the cell. Coordinates are: ";
		cin >> x1 >> y1;
		if (Check_Choice(map, x1, y1, 1)) {
			cout << "Where to put? Coordinates are: ";
			cin >> x2 >> y2;
			if (Check_Move(map, x2, y2, x1, y1, 1)) {
				Move(map, x2, y2, x1, y1, 1);
				system("cls");
				Print_Map(map);
				break;
			}
			else {
				system("cls");
				Print_Map(map);
				SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 4));
				cout << "Error. Try again." << endl;
				SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 15));
			}
		}
		else {
			system("cls");
			Print_Map(map);
			SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 4));
			cout << "Error. Try again." << endl;
			SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 15));
		}
	}
}

bool Can_Play(char* map[], int player) {
	int x[18] = { -1, 1, 2, 1, -1, -2, -4, -3, -2, 0, 2, 3, 4, 3, 2, 0, -2, -3 };
	int y[18] = { 1, 1, 0, -1, -1, 0, 0, 1, 2, 2,
					   2, 1, 0, -1, -2, -2, -2, -1 };
	const int amount_move = 18;
	for (int i = 0; i < map_height; i++) {
		for (int j = 0; j < map_width; j++) {
			if (map[i][j] == 48 + player) {
				for (int k = 0; k < amount_move; k++)
					if (Check_Move(map, i + x[k], j + y[k], i, j, player))
						return 1;
			}
		}
	}
	return 0;
}

int Score(char* map[], int player) {
	int i, j, score_player1 = 0, score_player2 = 0;
	for (i = 0; i < map_height; i++) {
		for (j = 0; j < map_width; j++) {
			if (map[i][j] == '1')
				score_player1++;
			if (map[i][j] == '2')
				score_player2++;
		}
	}
	if (player == 1)
		return score_player1;
	else
		if (player == 2)
			return score_player2;
		else
			cout << "Score " << score_player1 << " : " << score_player2 << endl;
}

int Move_Computer(char* map[], int level, int depth, int player,
	int current_player, int alpha, int beta) {
	int x[18] = { -1, 1, 2, 1, -1, -2, -4, -3, -2, 0, 2, 3, 4, 3, 2, 0, -2, -3 };
	int y[18] = { 1, 1, 0, -1, -1, 0, 0, 1, 2, 2, 2, 1, 0, -1, -2, -2, -2, -1 };
	char copy[17][9];
	const int all_move = 1100;
	const int amount_move = 18;
	int begin_x[all_move];
	int begin_y[all_move];
	int end_x[all_move];
	int end_y[all_move];
	int value[all_move];
	int counter_move = 0, i, j, optimal;
	if (level % 2 == 0)
		optimal = infinity;
	else
		optimal = -infinity;
	for (i = 0; i < map_height; i++) {
		for (j = 0; j < map_width; j++) {
			copy[i][j] = map[i][j];
		}
	}
	if (level > depth) {
		return Score(map, current_player) - Score(map, (current_player * 2) % 3);
	}
	else {
		for (i = 0; i < map_height; i++) {
			for (j = 0; j < map_width; j++) {
				if (Check_Choice(map, i, j, player)) {
					for (int k = 0; k < amount_move; k++) {
						if (alpha > beta)
							return optimal;
						if (Check_Move(map, i + x[k], j + y[k], i, j, player)) {
							begin_x[counter_move] = i;
							begin_y[counter_move] = j;
							end_x[counter_move] = i + x[k];
							end_y[counter_move] = j + y[k];
							Move(map, end_x[counter_move], end_y[counter_move],
								begin_x[counter_move], begin_y[counter_move], player);
							if (level % 2 == 0) {
								value[counter_move] = Move_Computer(map, level + 1, depth, (player * 2) % 3,
									current_player, alpha, beta);
								optimal = min(optimal, value[counter_move]);
								value[counter_move] = optimal;
								beta = min(beta, optimal);
							}
							else {
								value[counter_move] = Move_Computer(map, level + 1, depth, (player * 2) % 3,
									current_player, alpha, beta);
								optimal = max(optimal, value[counter_move]);
								value[counter_move] = optimal;
								alpha = max(alpha, optimal);
							}
							for (int t1 = 0; t1 < map_height; t1++)
								for (int t2 = 0; t2 < map_width; t2++)
									map[t1][t2] = copy[t1][t2];
							counter_move++;
						}
					}
				}
			}
		}
		if (level != 1)
			return optimal;
		if (level == 1 && i == map_height) {
			int max_value = value[0], max_index = 0;
			for (int k = 1; k < counter_move; k++) {
				if (max_value < value[k]) {
					max_value = value[k];
					max_index = k;
				}
			}
			Move(map, end_x[max_index], end_y[max_index],
				begin_x[max_index], begin_y[max_index], player);
			system("cls");
			Print_Map(map);
		}
	}
}