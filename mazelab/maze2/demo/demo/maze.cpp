#include"maze.h"
#include<iostream>
#include<array>
/*the construction*/
maze::maze() {
	//std::cout << "the default construction" << std::endl;
	init();
}
/*the copy construction*/
maze::maze(const maze & _arg):row(_arg.row),col(_arg.col),exitpos(_arg.exitpos),entrypos(_arg.entrypos),curpos(_arg.curpos) {
	map = new int*[row];
	for (int i = 0; i < row; i++)
		map[i] = new int[col];
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
			map[i][j] = _arg.map[i][j];

}
/*the move construction*/
maze::maze(maze && _arg)noexcept :row(_arg.row), col(_arg.col), exitpos(_arg.exitpos), entrypos(_arg.entrypos), curpos(_arg.curpos) {
	_arg.map = nullptr;
	this->map = _arg.map;
	//std::cout << "the move construction" << std::endl;
}
/*the initialization function*/
void maze::init() {
	std::array<int, 7>a = { 8,16,10,20,40,64,60 };
	auto one_size = a[rand() % 7];
	row = GRAPH_ROW /one_size;
	col = GRAPH_COL / one_size;
	map = new int*[row];
	for (int i = 0; i < row; i++)
		map[i] = new int[col];
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			auto t = rand() % 2;
			map[i][j] = t;
			if (i == 0 || i == row - 1 || j == 0 || j == col - 1)   //set the random value
				map[i][j] = 1;
		}
	}
	auto t = rand() % row;
	t == 0 ? t += 1 : t == row - 1 ? t -= 1 : t;
	entrypos.first = t;                         //set the random entry position
	t = rand() % col;
	t == 0 ? t += 1 : t == col - 1 ? t -= 1 : t;
	entrypos.second = t;    
	/*there will be low*/
	//
	do {
		t = rand() % row;
		t == 0 ? t += 1 : t == row - 1 ? t -= 1 : t;
		exitpos.first = t;
		t = rand() % col;
		t == 0 ? t += 1 : t == col - 1 ? t -= 1 : t;
		exitpos.second = t;             //set the random exit position  different from the entry position
	} while (exitpos == entrypos);
	curpos = entrypos;        //set the current positon to the entry position
	map[exitpos.first][exitpos.second] = 3;
	map[entrypos.first][entrypos.second] = 2; 
}

void maze::up() {
	if (map[curpos.first][curpos.second-1] == 0 || map[curpos.first][curpos.second-1] == 3) {
		map[curpos.first][curpos.second] = 0;
		curpos.second--;
		map[curpos.first][curpos.second] = 2;
	}
}
void maze::down() {
	if (map[curpos.first][curpos.second + 1] == 0 || map[curpos.first][curpos.second + 1] == 3) {
		map[curpos.first][curpos.second] = 0;
		curpos.second++;
		map[curpos.first][curpos.second] = 2;
	}
}
void maze::right() {
	if (map[curpos.first+1][curpos.second ] == 0 || map[curpos.first+1][curpos.second ] == 3) {
		map[curpos.first][curpos.second] = 0;
		curpos.first++;
		map[curpos.first][curpos.second] = 2;
	}
}
void maze::left() {
	if (map[curpos.first-1][curpos.second] == 0 || map[curpos.first-1][curpos.second] == 3) {
		map[curpos.first][curpos.second] = 0;
		curpos.first--;
		map[curpos.first][curpos.second] = 2;
	}
}
/*the deconstruction*/
maze ::~maze() {
	if (map != nullptr) {
		for (int i = 0; i < row; i++)
			delete[] map[i];
		delete[]map;
	}
}