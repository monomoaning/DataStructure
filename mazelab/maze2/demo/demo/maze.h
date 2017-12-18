#pragma once
#include<utility>
#include<time.h>
#include<iostream>
#include<stack>
#include<fstream>
#include<queue>
#define GRAPH_ROW 640
#define GRAPH_COL 480
class MazeSort;
class maze {
public:
	friend class MazeSort;
	friend std::ostream& operator<<(std::ostream & os, const maze &_arg) {
		for (int i = 0; i < _arg.row; i++) {
			for (int j = 0; j < _arg.col; j++)
				os << _arg.map[i][j]<< std::ends;
			std::cout << std::endl;
		}
		return os;
	}
	friend class manage;
	maze();
	maze(const maze &);
	maze(maze &&)noexcept;
	maze & operator=(const maze & _arg);
	maze &operator=(maze && _arg)noexcept;

	int  getValue(int x, int y)const {
		return map[x][y];
	}
	int & getValue(int x, int y) {
		return map[x][y];
	}
	void up();
	void down();
	void right();
	void left();
	static const int form = 20;
	bool canMove();
	static void pushVisited(const maze &, int, int,  std::queue<std::pair<int,int>> &);
	void writeToFile(const std::string &);
	~maze();
private:
	void release() {
		if (map != nullptr) {
			for (int i = 0; i < row; i++)
				delete[] map[i];
			delete[]map;
			map = nullptr;
		}
	}
	bool success() {
		return curpos == exitpos;
	}
	void init();
	size_t pos=0;
	int **map;
	int row;
	int col;
	std::pair<int, int>entrypos;
	std::pair<int, int>curpos;
	std::pair<int, int>exitpos;
	size_t st = 0;
};
class MazeSort {
public:
	bool operator()(const maze *lhs, const maze * rhs) {
		return (*lhs).col*(*lhs).row < (*rhs).col*(*rhs).row;
	}
};