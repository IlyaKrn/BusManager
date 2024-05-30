#pragma once
#include<list>
#include"BusModel.h"

class StateBusRepo
{
public:
	std::list<BusModel> getAll();
	void saveForward(BusModel bus);
	void saveBackward(BusModel bus);
	void saveAfterOf(BusModel bus, std::string busNumber);
	void saveBeforeOf(BusModel bus, std::string busNumber);
	void deleteByBusNumber(std::string num);

};

