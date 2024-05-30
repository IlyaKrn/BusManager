#include "Manager.h"

using namespace std;

Manager::Manager()
{
    drivingRepo = DrivingBusRepo();
    stateRepo = StateBusRepo();
}

std::list<BusModel> Manager::getAll()
{
    list<BusModel> res = list<BusModel>();
    list<BusModel>::iterator it1;
    list<BusModel> state = stateRepo.getAll();
    for (it1 = state.begin(); it1 != state.end(); ++it1) {
        res.push_back(*it1);
    }

    list<BusModel>::iterator it2;
    list<BusModel> drive = drivingRepo.getAll();
    for (it2 = drive.begin(); it2 != drive.end(); ++it2) {
        res.push_back(*it2);
    }
    return res;
}

std::list<BusModel> Manager::getState()
{
    return stateRepo.getAll();
}

std::list<BusModel> Manager::getDriving()
{
    return drivingRepo.getAll();
}

void Manager::addBus(BusModel data, Adding adding, std::string num)
{
    switch (adding)
    {
    case Manager::FORWARD:
        stateRepo.saveForward(data);
        break;
    case Manager::BACKWARD:
        stateRepo.saveBackward(data);
        break;
    case Manager::AFTER_OF:
        stateRepo.saveAfterOf(data, num);
        break;
    case Manager::BEFORE_OF:
        stateRepo.saveBeforeOf(data, num);
        break;
    default:
        throw string("this type of adding not found");
        break;
    }
}

void Manager::goBusToState(std::string num)
{
    BusModel bus; 
    bool isExists = false;
    list<BusModel>::iterator it1;
    list<BusModel> driving = drivingRepo.getAll();
    for (it1 = driving.begin(); it1 != driving.end(); ++it1) {
        if (it1->getBusNumber() == num) {
            isExists = true;
            bus = *it1;
            break;
        }
    }
    if (!isExists)
        throw string("bus with this number not exists in driving");
    stateRepo.saveBackward(bus);
    drivingRepo.deleteByBusNumber(num);
    
}

void Manager::goBusToDriving(std::string num)
{
    BusModel bus;
    bool isExists = false;
    list<BusModel>::iterator it1;
    list<BusModel> state = stateRepo.getAll();
    for (it1 = state.begin(); it1 != state.end(); ++it1) {
        if (it1->getBusNumber() == num) {
            isExists = true;
            bus = *it1;
            break;
        }
    }
    if (!isExists)
        throw string("bus with this number not exists in state");
    drivingRepo.save(bus);
    stateRepo.deleteByBusNumber(num);
}
