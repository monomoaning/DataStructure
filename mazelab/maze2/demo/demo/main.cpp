#include<iostream>
#include<graphics.h>
#include"manage.h"
using namespace std;
int main(int argc, char *argv[]) {
	srand((unsigned)time(0));
	manage a;
	a.genete(10);
	a.update();
	system("pause");
	return 0;
}