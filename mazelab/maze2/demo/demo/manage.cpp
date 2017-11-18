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

void manage::update() {
	initgraph(GRAPH_ROW, GRAPH_COL);
	setbkcolor(WHITE);
	cleardevice();
	while (1) {
		draw(data.front());
		if (_kbhit()) {
			char a = _getch();
			switch (a) {
			case 'w':
				data.front().up();
				setfillcolor(WHITE);
				cleardevice();
				break;
			case 'a':
				data.front().left();
				cleardevice();
				break;
			case 'd':
				data.front().right();
				cleardevice();
				break;
			case 's':
				data.front().down();
				cleardevice();
				break;
			}
			if (data.front().success())
				exit(1);
		}
	}
}