#pragma once
#include"BusModel.h"

struct Entry {
	Entry();
	Entry(Entry* p, Entry* n, BusModel d);
	Entry* prev;
	Entry* next;
	BusModel data;
};
class BusList
{
private:
	int size;
	Entry* start;
	Entry* end;
public:
	BusList();
	~BusList();
	BusModel get(int index);
	void pushForward(BusModel data);
	void pushBackward(BusModel data);
	void pushAfterOf(BusModel data, int index);
	void pushBeforef(BusModel data, int index);
	void remove(int index);
	int getSize();

};

