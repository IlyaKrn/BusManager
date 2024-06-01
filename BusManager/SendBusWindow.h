#pragma once
#include "Button.h"
#include "TextInput.h"
#include "RadioButtonList.h"

class SendBusWindow
{
public:
	SendBusWindow();

	void show();

private:
	bool validateData();

	sf::RenderWindow window;

	TextInput numberBusTextInput;

	RadioButtonList locationRadioButtonList;

	Button sendBusButton;
};

