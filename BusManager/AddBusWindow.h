#pragma once
#include "Button.h"
#include "TextInput.h"
#include "RadioButtonList.h"

class AddBusWindow
{
public:
	AddBusWindow();

	void show();

private:
	bool validateData();

	sf::RenderWindow window;

	TextInput numberBusTextInput;

	TextInput numberRouteTextInput;

	TextInput driverTextInput;

	RadioButtonList locationRadioButtonList;

	TextInput numberNextPrevTextInput;

	Button addBusButton;
};

