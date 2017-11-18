#include<iostream>
#include<fstream>
using namespace std;
int main() {
	FILE *fs;
	fstream fst("foo.txt", ios::out);
	int a = 255;
	fst << a;
	decltype(fgetc(fs))gh;
	cout << typeid(gh).name() << endl;
	system("pause");
	return 0;
}