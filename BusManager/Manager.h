#pragma once
#include"DrivingBusRepo.h"
#include"StateBusRepo.h"

class Manager
{
private:
	DrivingBusRepo drivingRepo;
	StateBusRepo stateRepo;
public:
	enum Adding {
		FORWARD, BACKWARD, AFTER_OF, BEFORE_OF
	};
	Manager();
	std::list<BusModel> getAll();
	std::list<BusModel> getState();
	std::list<BusModel> getDriving();
	void addBus(BusModel data, Adding adding, std::string num);
	void goBusToState(std::string num);
	void goBusToDriving(std::string num);
};

