#include <iostream>
#include"DrivingBusRepo.h"

using namespace std;

int main()
{
	try {
		DrivingBusRepo repo = DrivingBusRepo();
		list<BusModel> buses = repo.getAll();
		list<BusModel>::iterator it;
		for (it = buses.begin(); it != buses.end(); ++it) {
			cout << it->getBusNumber() << " " << it->getRouteNumber() << " " << it->getDriver() << endl;
		}

	}
	catch (string e) {
		cout << e << endl;
	}
}
