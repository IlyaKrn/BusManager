#include "StateBusRepo.h"
#include<fstream>
#include"Utils.h"
using namespace std;

std::list<BusModel> StateBusRepo::getAll()
{
	std::ifstream input("state_buses.txt");

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

void StateBusRepo::saveForward(BusModel bus)
{
	list<BusModel> buses = getAll();
	list<BusModel>::iterator it;
	for (it = buses.begin(); it != buses.end(); ++it) {
		if (it->getBusNumber() == bus.getBusNumber())
			throw string("state bus with this number is exists");
	}
	buses.push_front(bus);
	ofstream output("state_buses.txt");
	output.clear();
	for (it = buses.begin(); it != buses.end(); ++it) {
		output << it->getBusNumber() << "%" << it->getRouteNumber() << "%" << it->getDriver() << endl;
	}
	output.close();
}

void StateBusRepo::saveBackward(BusModel bus)
{
	list<BusModel> buses = getAll();
	list<BusModel>::iterator it;
	for (it = buses.begin(); it != buses.end(); ++it) {
		if (it->getBusNumber() == bus.getBusNumber())
			throw string("state bus with this number is exists");
	}
	buses.push_back(bus);
	ofstream output("state_buses.txt");
	output.clear();
	for (it = buses.begin(); it != buses.end(); ++it) {
		output << it->getBusNumber() << "%" << it->getRouteNumber() << "%" << it->getDriver() << endl;
	}
	output.close();
}

void StateBusRepo::saveAfterOf(BusModel bus, std::string busNumber)
{
	list<BusModel> buses = getAll();
	list<BusModel> res = list<BusModel>();
	bool isAdded = false;
	list<BusModel>::iterator it;
	for (it = buses.begin(); it != buses.end(); ++it) {
		if(it->getBusNumber() == bus.getBusNumber())
			throw string("state bus with this number exists");
		if (it->getBusNumber() == busNumber) {
			isAdded = true;
			res.push_back(*it);
			res.push_back(bus);
		}
		else {
			res.push_back(*it);
		}
	}
	if(!isAdded)
		throw string("state bus with this number not exists");

	ofstream output("state_buses.txt");
	output.clear();
	list<BusModel>::iterator it2;
	for (it2 = res.begin(); it2 != res.end(); ++it2) {
		output << it2->getBusNumber() << "%" << it2->getRouteNumber() << "%" << it2->getDriver() << endl;
	}
	output.close();
}

void StateBusRepo::saveBeforeOf(BusModel bus, std::string busNumber)
{
	list<BusModel> buses = getAll();
	list<BusModel> res = list<BusModel>();
	bool isAdded = false;
	list<BusModel>::iterator it;
	for (it = buses.begin(); it != buses.end(); ++it) {
		if (it->getBusNumber() == bus.getBusNumber())
			throw string("state bus with this number exists");
		if (it->getBusNumber() == busNumber) {
			isAdded = true;
			res.push_back(bus);
			res.push_back(*it);
		}
		else {
			res.push_back(*it);
		}
	}
	if (!isAdded)
		throw string("state bus with this number not exists");

	ofstream output("state_buses.txt");
	output.clear();
	list<BusModel>::iterator it2;
	for (it2 = res.begin(); it2 != res.end(); ++it2) {
		output << it2->getBusNumber() << "%" << it2->getRouteNumber() << "%" << it2->getDriver() << endl;
	}
	output.close();
}

void StateBusRepo::deleteByBusNumber(std::string num)
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
		throw string("state bus with this number not exists");
	}
	buses.erase(it);
	ofstream output("state_buses.txt");
	output.clear();
	for (it = buses.begin(); it != buses.end(); ++it) {
		output << it->getBusNumber() << "%" << it->getRouteNumber() << "%" << it->getDriver() << endl;
	}
	output.close();
}
