#include <iostream>
#include"MainWindow.h"

using namespace std;

int main()
{
	try {
		MainWindow window;
		window.show();
	}
	catch (string e) {
		cout << e << endl;
	}
}
