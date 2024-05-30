#include "BusModel.h"

BusModel::BusModel(std::string busNumber, std::string routeNumber, std::string driver)
{
	_busNumber = busNumber;
	_routeNumber = routeNumber;
	_driver = driver;
}

std::string BusModel::getBusNumber()
{
	return _busNumber;
}

std::string BusModel::getRouteNumber()
{
	return _routeNumber;
}

std::string BusModel::getDriver()
{
	return _driver;
}

void BusModel::setBusNumber(std::string busNumber)
{
	_busNumber = busNumber;
}

void BusModel::setRouteNumber(std::string routeNumber)
{
	_routeNumber = routeNumber;
}

void BusModel::setDriver(std::string driver)
{
	_driver = driver;
}
