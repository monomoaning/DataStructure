#include<graphics.h>
#include<conio.h>
#include"manage.h"
#include<algorithm>
/*genete the maze*/
int manage::count = 0;
void manage::genete(size_t n) {
	data.reserve(20);
	for (size_t i = 0; i < n; i++) {
		maze * a=new maze;
		data.push_back(a);
	}
}
/*the draw function*/
void manage::draw(const maze& _arg) {
	BeginBatchDraw();
	setfillcolor(YELLOW);
	setlinecolor(WHITE);
	for (int i = 0; i < _arg.row; i++)
		line(i*maze::form, 0, i*maze::form, _arg.col*maze::form);
	for (int j = 0; j < _arg.col; j++)
		line(0, j*maze::form, _arg.row*maze::form, j*maze::form);
	for (int i = 0; i < _arg.row; i++) {
		for (int j = 0; j < _arg.col; j++) {
			if (_arg.getValue(i,j) == 1) {
				setfillcolor(BLACK);
				fillrectangle(i*maze::form, j*maze::form, (i + 1)*maze::form, (j + 1)*maze::form);
			}
			if (_arg.getValue(i,j) == 2) {
				setfillcolor(RED);
				fillcircle((i*maze::form + (i + 1)*maze::form) / 2, (j*maze::form + (j + 1)*maze::form) / 2, maze::form / 2);
			}
			if (_arg.getValue(i,j) == 3) {
				setfillcolor(GREEN);
				fillrectangle(i*maze::form, j*maze::form, (i + 1)*maze::form, (j + 1)*maze::form);
			}
		}
	}
	EndBatchDraw();
	FlushBatchDraw();
}
void manage::changeScene() {
	BinaryTree<int>a;
	a.geneteRandom();
	while (a.canStep()) {
		auto p = a.step();
		switch (p) {
		case 2:
			settextcolor(RED);
			outtextxy(20, 20, _T("checkout scene"));
			Sleep(100);
			break;
		case 1:
			break;
		case 0:
			cur.curpos = cur.entrypos;
			break;
		case 3:
			settextcolor(BLACK);
			outtextxy(40, 20, _T("another action"));
			Sleep(100);
			break;
		}
	}
}
void manage::update() {
	std::sort(data.begin(), data.end(), MazeSort());
	initgraph(cur.row*maze::form, cur.col*maze::form);
	setbkcolor(WHITE);
	cleardevice();
	static int d = 0;
	cur = *data[d];
	while (1) {
		//if (!cur.canMove()) {
		//	cur.release();
		//	cur.init();
		//	continue;
		//}
		Resize(NULL, cur.row*maze::form, cur.col*maze::form);
		draw(cur);
		if (_kbhit()) {
			char a = _getch();
			switch (a) {
			case 'w':
				cur.up();
				setfillcolor(WHITE);
				cleardevice();
				break;
			case 'a':
				cur.left();
				cleardevice();
				break;
			case 'd':
				cur.right();
				cleardevice();
				break;
			case 's':
				cur.down();
				cleardevice();
				break;
			case 'r':
				cur = *data[++d];
				cleardevice();
				break;
			case 'k':
				if (count > 3)
					break;
				cur.writeToFile("maze.txt");
				count++;
				break;
			}
			/*if (cur.pos >= 10)
				changeScene();*/
			if (cur.success())
				cur = *data[++d];
		}
	}
}