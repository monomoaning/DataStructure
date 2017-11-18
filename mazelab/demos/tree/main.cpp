#include<iostream>
using namespace std;
void recusive() {
	char a;
	cin.get(a);
	if (a == '\n')
		return;
	recusive();
	cout.put(a);
}
int main() {
	recusive();

	system("pause");
	return 0;
}