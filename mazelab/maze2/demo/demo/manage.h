#pragma once
#include<list>
#include"maze.h"
#include"BinaryTree.h"
class manage {
public:
	/*default construction*/
	manage() = default;
	void genete(size_t);
	/*empty*/
	bool empty()const {
		return data.empty();
	}
	/*size*/
	size_t size()const {
		return data.size();
	}
	void output() {
		draw(data.front());
	}
	void update();
private:
	void changeScene();
	/*draw on maze*/
	void draw(const maze &);
	/*copy add*/
	template<typename T>
	void add(const T &_arg) {
		data.push_back(_arg);
	}
	/*data*/
	maze cur;
	std::list<maze>data;
	size_t n = 0;
};
