#include "maze.h"
#include<windows.h>
std::ostream & operator<<(std::ostream & os,const maze & arg){
    if(arg.map== nullptr)
        return os;
    else{
        for(auto i=0;i<=arg.row;++i) {
            for (int j = 0; j <= arg.col; ++j) {
                os<<arg.map[i][j];
            }
            os<<std::endl;
        }
    }
    return os;
}
std::fstream & operator<<(std::fstream & os, const maze & arg) {
	if (arg.map == nullptr)
		return os;
	else {
		for (auto i = 0; i <= arg.row; ++i) {
			for (int j = 0; j <= arg.col; ++j) {
				os << arg.map[i][j] ;
			}
			os << std::endl;
		}
	}
	return os;
}
void maze::random() {
	//seed = time(NULL);
	//srand(unsigned(seed));
	row = rand() % ROW_MAX + 10u;
	col = rand() % COL_MAX + 10u;
}
maze::maze(){
	random();
    initMap();
}
maze::maze(const maze &_arg):entry(_arg.entry),exitchar(_arg.exitchar),curchar(_arg.curchar),wall(_arg.wall)
		,road(_arg.road),visited(_arg.visited){
	if (this == &_arg)
		return;
	row = _arg.row;
	col = _arg.col;
	cur = _arg.cur;
	exit = _arg.exit;
	seed = _arg.seed;
	 srand(unsigned(seed));
	 initMap();
}
maze::maze(maze && _arg) :entry(_arg.entry), exitchar(_arg.exitchar), curchar(_arg.curchar), wall(_arg.wall)
, road(_arg.road), visited(_arg.visited) {
	if (this == &_arg)
		return;
	row = _arg.row;
	col = _arg.col;
	cur = _arg.cur;
	exit = _arg.exit;
	seed = _arg.seed;
	map = _arg.map;
	_arg.map = nullptr;
}

void maze::pushUnvisited(const std::pair<size_t , size_t > &arg) {
    if(map[arg.first][arg.second]==exitchar||map[arg.first][arg.second]==road){
        visitmap.push(arg);
    }
}
void maze::clear() {
	for (auto i = 0; i <= row; ++i)
		delete[] map[i];
	delete []map;
}
void maze::recover() {
	srand((unsigned)seed);
	initMap();
}
void maze::initExit() {
    cur.first=1,cur.second=1;
    map[cur.first][cur.second]=curchar;
    exit.first=row-1;
    exit.second=col-1;
    map[exit.first][exit.second]=exitchar;
}
void maze::initMap() {     
        map=new char*[row+1];
        for(int j=0;j<=row;j++)
            map[j]=new char[col+1];
        for(int i=0;i<=row;++i){
            for(int j=0;j<=col;++j){
                auto flag=rand()%2;
                if(flag)
                    map[i][j]=wall;
                else
                    map[i][j]=road;
                if(i==0||i==row||j==0||j==col)
                    map[i][j]=THEOUT_CHAR;
            }
        }
    initExit();
}

void maze::visit(){
    while(map[cur.first][cur.second]!=exitchar){
        auto t_pair=cur;
        if(map[t_pair.first][t_pair.second]!=entry)
            map[t_pair.first][t_pair.second]=visited;
        pushUnvisited(std::pair<size_t,size_t>(cur.first-1,cur.second));
        pushUnvisited(std::pair<size_t,size_t>(cur.first+1,cur.second));
        pushUnvisited(std::pair<size_t,size_t>(cur.first,cur.second-1));
        pushUnvisited(std::pair<size_t,size_t>(cur.first,cur.second+1));
        if(visitmap.empty()){
            std::cout<<*this;
            std::cout<<"fail"<<std::endl;
            return;
        }
        else {
            auto temp=visitmap.pop();
            cur.first = temp.first;
            cur.second=temp.second;
        }
    }
    std::cout<<*this;
    std::cout<<"success"<<std::endl;
}


