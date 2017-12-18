#include<iostream>
#include<graphics.h>
#include"manage.h"
#include"BinaryTree.h"
using namespace std;
int main(int argc, char *argv[]) {
	srand((unsigned)time(0));
	manage a;
	a.genete(10);
	a.update();
	return 0;
}