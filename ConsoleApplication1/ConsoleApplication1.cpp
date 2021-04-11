#include "hexagon.h"

#include <iostream>

#include<fstream>

//;_CRT_SECURE_NO_WARNINGS

using namespace std;


int main() {
	//FILE* input_file = fopen("map.txt", "r");

	ifstream input_file;

	input_file.open("map.txt");

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