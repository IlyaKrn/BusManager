#include "DrivingBusRepo.h"
#include<fstream>
#include"Utils.h"
using namespace std;

std::list<BusModel> DrivingBusRepo::getAll()
{
	std::ifstream input("driving_buses.txt");

	list<BusModel> res = list<BusModel>();
	for (std::string line; getline(input, line); )
	{
		vector<string> params = Utils::split(line, "%");
		if (params.size() != 3)
			throw string("error reading of data");
		res.push_back(BusModel(params[0], params[1], params[2]));
	}
	input.close();
	return res;
}

void DrivingBusRepo::save(BusModel bus)
{
	list<BusModel> buses = getAll();
	list<BusModel>::iterator it;
	for (it = buses.begin(); it != buses.end(); ++it) {
		if (it->getBusNumber() == bus.getBusNumber())
			throw string("driving bus with this number not exists");
	}
	buses.push_back(bus);
	ofstream output("driving_buses.txt");
	output.clear();
	for (it = buses.begin(); it != buses.end(); ++it) {
		output << it->getBusNumber() << "%" << it->getRouteNumber() << "%" << it->getDriver() << endl;
	}
	output.close();
}

void DrivingBusRepo::deleteByBusNumber(std::string num)
{
	list<BusModel> buses = getAll();
	bool isExists = false;
	list<BusModel>::iterator it;
	for (it = buses.begin(); it != buses.end(); ++it) {
		if (it->getBusNumber() == num) {
			isExists = true;
			break;
		}
	}
	if (!isExists) {
		throw string("driving bus with this number not exists");
	}
	buses.erase(it);
	ofstream output("driving_buses.txt");
	output.clear();
	for (it = buses.begin(); it != buses.end(); ++it) {
		output << it->getBusNumber() << "%" << it->getRouteNumber() << "%" << it->getDriver() << endl;
	}
	output.close();
}
