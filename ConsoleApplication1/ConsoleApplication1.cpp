#include "hexagon.h"

#include <iostream>

#include<fstream>

//;_CRT_SECURE_NO_WARNINGS

using namespace std;


int main(int argc, char* argv[]) {

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	if (argc < 2)
	{
		cout << "Wrong format" << endl;
		return -1;
	}

	ifstream input_file(argv[1]);

	if (!input_file) {
		cout << "Error writing file" << endl;
		return -3;
	}

	//FILE* input_file = fopen("map.txt", "r");

	//ifstream input_file;

	//input_file.open("map.txt");

	char* map[map_height];
	int mode;
	cout << "Play mode:\n	1 - Computer VS Computer\n	2 - Human VS Computer\n";
	cout << "Input play mode: ";
	cin >> mode;
	Scan_Map(map, input_file);
	Play(mode, map);
	input_file.close();

	//fclose(input_file);

	for (int i = 0; i < map_height; i++)
		delete[] map[i];


	return 0;
}