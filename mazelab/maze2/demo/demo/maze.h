#pragma once
#include<utility>
#include<time.h>
#include<iostream>
#define GRAPH_ROW 640
#define GRAPH_COL 480
class maze {
public:
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
	~maze();
private:
	bool success() {
		return curpos == exitpos;
	}
	void init();
	int **map;
	int row;
	int col;
	std::pair<int, int>entrypos;
	std::pair<int, int>curpos;
	std::pair<int, int>exitpos;
};
