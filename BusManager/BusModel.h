#pragma once
#include<string>

class BusModel
{
private:
	std::string _busNumber;
	std::string _routeNumber;
	std::string _driver;

public:
	BusModel(std::string busNumber, std::string routeNumber, std::string driver);

	std::string getBusNumber();
	std::string getRouteNumber();
	std::string getDriver();

	void setBusNumber(std::string busNumber);
	void setRouteNumber(std::string routeNumber);
	void setDriver(std::string driver);

};

