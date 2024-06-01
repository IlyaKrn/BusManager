#pragma once
#include "ScrollableList.h"
#include "Button.h"

class MainWindow
{
public:
	MainWindow();

	void show();
private:
	sf::RenderWindow window;

	Button allBusButton;

	Button inParkBusButton;

	Button onRouteBusButton;

	Button addBusButton;

	Button sendBusButton;

	ScrollableList infoBusesTable;
};

