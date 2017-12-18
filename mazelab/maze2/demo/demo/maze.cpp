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
	//std::array<int, 7>a = { 8,16,10,20,40,64,60 };
	//auto one_size = a[rand() % 7];
	//row = GRAPH_ROW /one_size;
	//col = GRAPH_COL / one_size;
	row = rand() % 10+20;
	col = rand() % 10+20;
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
	st = 0;
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
		pos++;
	}
}
void maze::down() {
	if (map[curpos.first][curpos.second + 1] == 0 || map[curpos.first][curpos.second + 1] == 3) {
		map[curpos.first][curpos.second] = 0;
		curpos.second++;
		map[curpos.first][curpos.second] = 2;
		pos++;
	}
}
void maze::right() {
	if (map[curpos.first+1][curpos.second ] == 0 || map[curpos.first+1][curpos.second ] == 3) {
		map[curpos.first][curpos.second] = 0;
		curpos.first++;
		map[curpos.first][curpos.second] = 2;
		pos++;
	}
}
void maze::left() {
	if (map[curpos.first-1][curpos.second] == 0 || map[curpos.first-1][curpos.second] == 3) {
		map[curpos.first][curpos.second] = 0;
		curpos.first--;
		map[curpos.first][curpos.second] = 2;
		pos++;
	}
}
maze & maze::operator=(const maze & _arg) {
	if (this != &_arg) {
		this->release();
		curpos = _arg.curpos;
		exitpos = _arg.exitpos;
		entrypos = _arg.entrypos;
		row = _arg.row;
		col = _arg.col;
		map = new int*[row];
		for (int i = 0; i < row; i++)
			map[i] = new int[col];
		for (int i = 0; i < row; i++)
			for (int j = 0; j < col; j++)
				map[i][j] = _arg.getValue(i, j);
	}
	return *this;
}
maze & maze::operator=(maze && _arg)noexcept {
	if (this != &_arg) {
		this->release();
		curpos = _arg.curpos;
		exitpos = _arg.exitpos;
		entrypos = _arg.entrypos;
		row = _arg.row;
		col = _arg.col;
		map = _arg.map;
		_arg.map = nullptr;
	}
	return *this;
}
/*the deconstruction*/
maze ::~maze() {
	if (map != nullptr) {
		for (int i = 0; i < row; i++)
			delete[] map[i];
		delete[]map;
	}
}

void maze::pushVisited(const maze & arg, int x, int y, std::queue <std::pair<int, int>> & rhs) {
	if (arg.getValue(x, y) == 0 || arg.getValue(x, y) == 3)
		rhs.push(std::make_pair(x, y));
}

void maze::writeToFile(const std::string & arg) {
	std::fstream out;
	out.open(arg.c_str(), std::ios::out | std::ios::app);
	if (out.fail()) {
		std::cout << "open file fail" << std::endl;
		return;
	}
	char a = ' ';
	out << row << a << col << a << entrypos.first << a << entrypos.second << a << exitpos.first << a << exitpos.second << a;
	out << curpos.first << a << curpos.second << a;
	for (int i = 0; i < row; ++i)
		for (int j = 0; j < col; ++j)
			out << map[i][j] << a;
}

bool maze::canMove() {
	std::queue<std::pair<int, int>>steps;
	maze temp = *this;
	steps.push(entrypos);
	while (!steps.empty()) {
		temp.curpos = steps.front();
		steps.pop();
		st++;
		temp.getValue(temp.curpos.first, temp.curpos.second) = 1;
		if (temp.curpos == exitpos)
			return true;
		pushVisited(temp, curpos.first-1, curpos.second, steps);
		pushVisited(temp, curpos.first+1, curpos.second, steps);
		pushVisited(temp, curpos.first, curpos.second-1, steps);
		pushVisited(temp, curpos.first, curpos.second+1, steps);
	}
	return false;
}