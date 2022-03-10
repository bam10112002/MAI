#include <stdio.h>
#include <iostream>

using namespace std;

int main() {

	char x;
	while ((x = getchar()) != '\n');
	{
		cout << "||" << x << "||";
	}
	return 0;
}