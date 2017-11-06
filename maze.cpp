#include "maze.h"
std::ostream & operator<<(std::ostream & os,const maze & arg){
    if(arg.map== nullptr)
        return os;
    else{
        for(auto i=0;i<=arg.row;++i) {
            for (int j = 0; j <= arg.col; ++j) {
                std::cout<<arg.map[i][j];
            }
            std::cout<<std::endl;
        }
    }
    return os;
}

maze::maze(){
    initMap();
}

void maze::pushUnvisited(const std::pair<size_t , size_t > &arg) {
    if(map[arg.first][arg.second]==exitchar||map[arg.first][arg.second]==road){
        visitmap.push(arg);
    }
}

void maze::initExit() {
    cur.first=1,cur.second=1;
    map[cur.first][cur.second]=curchar;
    exit.first=row-1;
    exit.second=col-1;
    map[exit.first][exit.second]=exitchar;
}
void maze::initMap() {     //初始化地图
        srand((unsigned)time(nullptr));
        row=rand()%ROW_MAX+10u;    //设置最小地图
        col=rand()%COL_MAX+10u;
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
       // std::cout<<*this;
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

