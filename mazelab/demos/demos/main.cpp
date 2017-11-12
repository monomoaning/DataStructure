#include<vector>
#include"maze.h"
#include"manage.h"
#include"LinkedList.h"
#include<fstream>
using namespace std;
using namespace mono;

int main() {
	//vector<int>b{ 3,4,5 };
	//list<int>a(b.begin(),b.end());
	//list<int>c{ 3,4,5,6,7,8 };
	//c.clear();
	//c.addToTail(9);
	//auto i = c[2];
	//c.delFromTail();
	//cout << sizeof(maze) << endl;
	srand((unsigned)time(NULL));
	fstream fst;
	manage b;
	b.generate(10);
	fst.open("foo.txt", ios::out);
	b.writeToFileByText(fst);
	fst.close();
	system("pause");
    return 0;
}