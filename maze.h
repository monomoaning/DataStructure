#ifndef DEMOS_MAZE_H
#define DEMOS_MAZE_H
#include<stdlib.h>
#include <iostream>
#include"Stack.h"
#define ROW_MAX 5         //设置最大列
#define COL_MAX 5         //设置最大行
#define WALL_CHAR    'X'
#define BLANK_CHAR   'O'
#define THEOUT_CHAR  '#'
class maze{
public:
    friend  std::ostream &operator<<(std::ostream &,const maze &);
    maze();
    void visit();
private:
    void initExit();
    void initMap();
    void pushUnvisited(const std::pair<size_t ,size_t >&);
    char **map= nullptr;
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
};
#endif //DEMOS_MAZE_H
