#ifndef __MANAGE_H__
#define __MANAGE_H__
#include<fstream>
#include<graphics.h>
#include"LinkedList.h"
#include"maze.h"
#define GRAPH_ROW 640
#define GRAPH_COL 480
class manage {
public:
	manage() = default;
	void generate(size_t _arg) {
		for (uint32_t i = 0; i < _arg; ++i) {
			maze_value.addToTail(maze());
		}
	}
	void display() {
		for (uint32_t i = 0; i < maze_value.size(); ++i) {
			std::cout << maze_value[i] << std::endl;
		}
	}
	void writeToFileByText(std::fstream &_arg) {
		try{
			if (!_arg.is_open())
				throw std::runtime_error("open file failed");
			maze_value.writeToFileByText(_arg);
		}
		catch (const std::runtime_error& a){
			std::cout << a.what() << std::endl;
		}
	}                     // the function is not useful because the pointer is invalid

	void writeToFileByBinary(std::fstream &_arg) {
		try {
			if (!_arg.is_open())
				throw std::runtime_error("open file failed");
			maze_value.writeToFileByBinary(_arg);

		}
		catch (const std::runtime_error& a) {
			std::cout << a.what() << std::endl;
		}

	}
	void readFromFileByBinary(std::fstream &_arg) {
		try {
			if (!_arg.is_open())
				throw std::runtime_error("open file fatiled");
			_arg.seekg(0, std::ios::end);
			auto fstsize = _arg.tellg();
			if (fstsize == static_cast<decltype(fstsize)>(0))
				throw std::runtime_error("the file is empty");
			_arg.seekg(0, std::ios::beg);
			maze_value.clear();
			while (!_arg.eof()) {
				maze *p=new maze();
				p->clear();
				_arg.read(reinterpret_cast<char *>(p), sizeof(maze));
				p->recover();
				maze_value.addToTail(std::move(*p));
			}
			maze_value.delFromTail();
		}
		catch (std::runtime_error &a) {
			std::cout << a.what() << std::endl;
		}
	}
	int getCurRow()const {
		return maze_value[cur].row;
	}
	int getCurCol()const {
		return maze_value[cur].col;
	}
	void init() {
		BeginBatchDraw();
		setlinecolor(BLACK);
		int one_size = GRAPH_ROW / getCurRow();
		for(int i=0;i<getCurRow();i++)
			line(i*one_size, 0, i*one_size, GRAPH_COL);
		for (int j = 0; j < getCurCol(); j++)
			line(0, j*one_size, GRAPH_ROW, j*one_size);
		for (int i = 0; i < getCurRow(); i++) {
			for (int j = 0; j < getCurCol(); j++) {
				if (maze_value[cur].map[i][j] == WALL_CHAR) {
					setfillcolor(BLACK);
					fillrectangle(i*one_size, j*one_size, (i + 1)*one_size, (j + 1)*one_size);
				}
				if (maze_value[cur].map[i][j] == CUR_CHAR) {
					setfillcolor(YELLOW);
					fillcircle((i*one_size + (i + 1)*one_size) / 2, (j*one_size + (j + 1)*one_size) / 2, one_size/2);
				}
			}
		}
		EndBatchDraw();
		FlushBatchDraw();
	}
	void update() {
		while (1) {
			init();
			if (_kbhit()) {
				char a = _getch();
				switch (a) {
				case 'w':
					maze_value[cur].up();
					//cleardevice();
					break;
				case 'd':
					maze_value[cur].right();
					//cleardevice();
					break;
				}
			}
		}
	}
private:
	mono::list<maze >maze_value;
	int cur = 0;
	//std::fstream & fst;
};
#endif //!__MANAGE_H__