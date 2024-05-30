#include "BusList.h"
using namespace std;

BusList::BusList()
{
	size = 0;
	start = nullptr;
	end = nullptr;
}

BusList::~BusList()
{
	Entry* current = start;
	while (current != nullptr) {
		Entry* next = current->next;
		delete current;
		current = next;
	}
}

BusModel BusList::get(int index)
{
	if (index < 0 && index >= size)
		throw string("index out of bounds");
    Entry* current = start;
	for (int i = 0; i < index; i++) {
		current = current->next;
	}
	return current->data;
}

void BusList::pushForward(BusModel data)
{
	if (size > 0) {
		Entry* next = start;
		start = new Entry(nullptr, next, data);
		next->prev = start;
		size++;
	}
	else
	{
		start = new Entry(nullptr, nullptr, data);
		end = start;
	}
}

void BusList::pushBackward(BusModel data)
{
	if (size > 0) {
		Entry* prev = end;
		end = new Entry(prev, nullptr, data);
		prev->next = end;
		size++;
	}
	else
	{
		start = new Entry(nullptr, nullptr, data);
		end = start;
	}
}

void BusList::pushAfterOf(BusModel data, int index)
{
	//impliment
}

void BusList::pushBeforef(BusModel data, int index)
{
	//impliment
}

void BusList::remove(int index)
{
	if (index < 0 && index >= size)
		throw string("index out of bounds");
	Entry* current = start;
	for (int i = 0; i < index; i++) {
		current = current->next;
	}
	Entry* prev = current->prev;
	Entry* next = current->next;
	if (prev == nullptr) {
		next->prev = nullptr;
		start = next;
		return;
	}
	else if (next == nullptr) {
		prev->next = nullptr;
		end = prev;
		return;
	}
	else {
		prev->next = next;
		next->prev = prev;
	}
	delete current;
	size--;
}

int BusList::getSize()
{
    return size;
}

Entry::Entry()
{
	prev = nullptr;
	next = nullptr;
	data = BusModel();
}

Entry::Entry(Entry* p, Entry* n, BusModel d)
{
	prev = p;
	next = n;
	data = d;
}
