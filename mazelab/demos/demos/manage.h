#ifndef __MANAGE_H__
#define __MANAGE_H__
#include<fstream>
#include"LinkedList.h"
#include"maze.h"
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
private:
	mono::list<maze >maze_value;
	//std::fstream & fst;
};
#endif //!__MANAGE_H__