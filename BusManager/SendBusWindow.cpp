#include "SendBusWindow.h"
#include "Manager.h"
#include <windows.h>
#include <locale.h>
#include <codecvt>
#include <regex> 

using namespace std;

SendBusWindow::SendBusWindow():window(sf::VideoMode(400, 300), L"Отправить в..."),
    numberBusTextInput(TextInput(50, 25, 300, 50, L"Введите номер автобуса")),
    locationRadioButtonList(RadioButtonList(50, 125, 300)),
    sendBusButton(75, 230, 250, 50, L"Отправить")
{
    locationRadioButtonList.addItem(L"В парк");
    locationRadioButtonList.addItem(L"На маршрут");
}

void SendBusWindow::show()
{
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (sendBusButton.isClicked(sf::Mouse::getPosition(window))) {
                        if (validateData()) {
                            //Твой код

                            using convert_type = codecvt_utf8<wchar_t>;
                            wstring_convert<convert_type, wchar_t> converter;

                            string busNumber = converter.to_bytes(numberBusTextInput.getText());





                            if (!(busNumber.length() == 6 &&
                                regex_match(string(1, busNumber[0]), regex("([A-Z])")) &&
                                regex_match(string(1, busNumber[1]), regex("([0-9])")) &&
                                regex_match(string(1, busNumber[2]), regex("([0-9])")) &&
                                regex_match(string(1, busNumber[3]), regex("([0-9])")) &&
                                regex_match(string(1, busNumber[4]), regex("([A-Z])")) &&
                                regex_match(string(1, busNumber[5]), regex("([A-Z])")))) {
                                MessageBox(NULL, L"Неверно указан номер автобуса", L"Ошибка", MB_ICONERROR | MB_OK);
                            }
                            else {
                                try {
                                    Manager m = Manager();
                                    switch (locationRadioButtonList.getSelectedIndex()) {
                                    case 0:
                                        m.goBusToState(busNumber);
                                        window.close();
                                        break;
                                    case 1:
                                        m.goBusToDriving(busNumber);
                                        window.close();
                                        break;
                                    default:
                                        break;
                                    }
                                }
                                catch (string s) {
                                    wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
                                    wstring wide = converter.from_bytes(s);
                                    MessageBox(NULL, wide.c_str(), L"Ошибка", MB_ICONERROR | MB_OK);
                                }
                            }
                        }
                    }
                }
            }
            else if (event.type == sf::Event::MouseButtonReleased)
                sendBusButton.resetColor();
            numberBusTextInput.handleEvent(event, window);
            locationRadioButtonList.handleEvent(event, window);
        }
        window.clear(sf::Color::White);
        numberBusTextInput.draw(window);
        locationRadioButtonList.draw(window);
        sendBusButton.draw(window);
        window.display();
    }
}

bool SendBusWindow::validateData()
{
    if (numberBusTextInput.isEmpty()){
        MessageBox(NULL, L"Пожалуйста, заполните все поля", L"Ошибка", MB_ICONERROR | MB_OK);
        return false;
    }
    return true;
}
