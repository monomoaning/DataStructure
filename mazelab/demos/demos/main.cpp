#include<vector>
#include<conio.h>
#include"maze.h"
#include"manage.h"
#include"LinkedList.h"
#include<fstream>
using namespace std;
using namespace mono;

int main() {
	srand((unsigned)time(0));
	//initgraph(GRAPH_ROW, GRAPH_COL);
	//setbkcolor(WHITE);
	//cleardevice();
	manage a;
	a.generate(5);
	//a.update();
	while (1) {
		a.display();
	}
    return 0;
}