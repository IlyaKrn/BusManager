#pragma once
#include<list>
#include"BusModel.h"

class DrivingBusRepo
{
public:
	std::list<BusModel> getAll();
	void save(BusModel bus);
	void deleteByBusNumber(std::string num);

};

