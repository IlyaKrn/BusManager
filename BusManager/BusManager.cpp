#include <iostream>
#include"Manager.h"

using namespace std;

int main()
{
	try {
		Manager m();
	}
	catch (string e) {
		cout << e << endl;
	}
}
