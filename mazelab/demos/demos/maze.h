#ifndef DEMOS_MAZE_H
#define DEMOS_MAZE_H
#include<stdlib.h>
#include<ctime>
#include<iostream>
#include<fstream>
#include"Stack.h"
#define ROW_MAX 10         
#define COL_MAX 10        
#define WALL_CHAR    'X'
#define BLANK_CHAR   'O'
#define THEOUT_CHAR  '#'
class maze{
public:
    friend  std::ostream &operator<<(std::ostream &,const maze &);
	friend  std::fstream &operator<<(std::fstream &, const maze &);    //write to file by text
    maze();
	maze(const maze &);
	maze(maze &&);
    void visit();
	void recover();
	void clear();
private:
	void random();
    void initExit();
    void initMap();
    void pushUnvisited(const std::pair<size_t ,size_t >&);
    char **map;
    size_t row=0;
    size_t col=0;
    std::pair<size_t ,size_t >cur;
    std::pair<size_t ,size_t >exit;
    Stack<std::pair<size_t ,size_t >>visitmap;
    const char entry='m';
    const char exitchar='e';
    const char curchar='c';
    const char wall=WALL_CHAR;
    const char road=BLANK_CHAR;
    const char visited='.';
	decltype(time(NULL))seed;
};
#endif //DEMOS_MAZE_H
