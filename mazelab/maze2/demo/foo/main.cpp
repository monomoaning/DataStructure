#include<fstream>
#include<string>
#include<iostream>
using namespace std;
int main() {
	fstream fst;
	fst.open("text.txt", ios::out | ios::app);
	int a = 4, b = 5, c = 6;
	cout << a << ends << b << ends << c << ends;
	fst.close();
	system("pause");
	return 0;
}