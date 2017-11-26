#include<graphics.h>
#include<conio.h>
#include"manage.h"
/*genete the maze*/
void manage::genete(size_t n) {
	for (size_t i = 0; i < n; i++) {
		maze a;
		add(a);
	}
}
/*the draw function*/
void manage::draw(const maze& _arg) {
	BeginBatchDraw();
	setfillcolor(BLACK);
	setlinecolor(BLACK);
	for (int i = 0; i < _arg.row; i++)
		line(i*(GRAPH_ROW / _arg.row), 0, i*(GRAPH_ROW / _arg.row), GRAPH_COL);
	for (int j = 0; j < _arg.col; j++)
		line(0, j*(GRAPH_COL / _arg.col), GRAPH_ROW, j*(GRAPH_COL / _arg.col));
	for (int i = 0; i < _arg.row; i++) {
		for (int j = 0; j < _arg.col; j++) {
			if (_arg.getValue(i,j) == 1) {
				setfillcolor(BLACK);
				fillrectangle(i*(GRAPH_ROW / _arg.row), j*(GRAPH_COL / _arg.col), (i + 1)*(GRAPH_ROW / _arg.row), (j + 1)*(GRAPH_COL / _arg.col));
			}
			if (_arg.getValue(i,j) == 2) {
				setfillcolor(RED);
				fillcircle((i*(GRAPH_ROW / _arg.row) + (i + 1)*(GRAPH_ROW / _arg.row)) / 2, (j*(GRAPH_COL / _arg.col) + (j + 1)*(GRAPH_COL / _arg.col)) / 2, (GRAPH_COL / _arg.col) / 2);
			}
			if (_arg.getValue(i,j) == 3) {
				setfillcolor(GREEN);
				fillrectangle(i*(GRAPH_ROW / _arg.row), j*(GRAPH_COL / _arg.col), (i + 1)*(GRAPH_ROW / _arg.row), (j + 1)*(GRAPH_COL / _arg.col));
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
	initgraph(GRAPH_ROW, GRAPH_COL);
	setbkcolor(WHITE);
	cleardevice();
	while (1) {
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
			}
			if (cur.pos >= 10)
				changeScene();
			if (data.front().success())
				exit(1);
		}
	}
}