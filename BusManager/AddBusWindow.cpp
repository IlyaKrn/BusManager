#include "AddBusWindow.h"
#include "Manager.h"
#include <windows.h>
#include <string.h>
#include <locale.h>
#include <codecvt>
#include <regex> 

using namespace std;

AddBusWindow::AddBusWindow() : window(sf::VideoMode(800, 800), L"Добавление автобуса"),
    numberBusTextInput(TextInput(50, 50, 700, 50, L"Введите номер автобуса")),
    numberRouteTextInput(TextInput(50, 150, 700, 50, L"Введите номер маршрута")),
    driverTextInput(TextInput(50, 250, 700, 50, L"Введите ФИО водителя")),
    locationRadioButtonList(RadioButtonList(50, 350, 600)),
    numberNextPrevTextInput(TextInput(50, 550, 700, 50,L"Введите номер пред/след автобуса")),
    addBusButton(250, 650, 300, 100, L"Добавить")
{
    locationRadioButtonList.addItem(L"В начало");
    locationRadioButtonList.addItem(L"В конец");
    locationRadioButtonList.addItem(L"После автобуса");
    locationRadioButtonList.addItem(L"Перед автобусом");
}

void AddBusWindow::show()
{
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (addBusButton.isClicked(sf::Mouse::getPosition(window))) {
                        if (validateData()) {
                            //Твой код
                            using convert_type = codecvt_utf8<wchar_t>;
                            wstring_convert<convert_type, wchar_t> converter;

                            string busNumber = converter.to_bytes(numberBusTextInput.getText());
                            string routeNumber = converter.to_bytes(numberRouteTextInput.getText());
                            string driver = converter.to_bytes(driverTextInput.getText());
                            string parentBusNumber = converter.to_bytes(numberNextPrevTextInput.getText());

                            cout << driver.substr(driver.find(" "), driver.length()) << endl;
                            if (!(busNumber.length() == 6 &&
                                regex_match(string(1, busNumber[0]), regex("([A-Z])")) &&
                                regex_match(string(1, busNumber[1]), regex("([0-9])")) &&
                                regex_match(string(1, busNumber[2]), regex("([0-9])")) &&
                                regex_match(string(1, busNumber[3]), regex("([0-9])")) &&
                                regex_match(string(1, busNumber[4]), regex("([A-Z])")) &&
                                regex_match(string(1, busNumber[5]), regex("([A-Z])")))) {
                                MessageBox(NULL, L"Неверно указан номер автобуса", L"Ошибка", MB_ICONERROR | MB_OK);
                            }
                            else if (!(routeNumber.length() == 3 &&
                                regex_match(string(1, routeNumber[0]), regex("([A-Z])")) &&
                                regex_match(string(1, routeNumber[1]), regex("([0-9])")) &&
                                regex_match(string(1, routeNumber[2]), regex("([0-9])")))) {
                                MessageBox(NULL, L"Неверно указан номер маршрута", L"Ошибка", MB_ICONERROR | MB_OK);
                            }
                            else if (!(
                                driver.find(" ") != -1 &&
                                driver.substr(driver.find(" "), driver.length()).length() == 4 &&
                                string(1, driver.substr(driver.find(" "), driver.length())[0]) == " " &&
                                regex_match(string(1, driver.substr(driver.find(" "), driver.length())[1]), regex("([A-Z])")) &&
                                string(1, driver.substr(driver.find(" "), driver.length())[2]) == " " &&
                                regex_match(string(1, driver.substr(driver.find(" "), driver.length())[3]), regex("([A-Z])"))
                                
                                
                                )) {
                                MessageBox(NULL, L"Неверно указаны данные водителя", L"Ошибка", MB_ICONERROR | MB_OK);
                            }
                            else {
                                try {
                                    Manager m = Manager();
                                    BusModel b = BusModel(busNumber, routeNumber, driver);
                                    switch(locationRadioButtonList.getSelectedIndex()) {
                                    case 0:
                                        m.addBus(b, Manager::Adding::FORWARD, "");
                                        window.close();
                                        break;
                                    case 1:
                                        m.addBus(b, Manager::Adding::BACKWARD, "");
                                        window.close();
                                        break;
                                    case 2:
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
                                            m.addBus(b, Manager::Adding::AFTER_OF, parentBusNumber);
                                            window.close();
                                        }
                                        break;
                                    case 3:
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
                                            m.addBus(b, Manager::Adding::BEFORE_OF, parentBusNumber);
                                            window.close();
                                        }
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
                addBusButton.resetColor();
            numberBusTextInput.handleEvent(event, window);
            numberRouteTextInput.handleEvent(event, window);
            driverTextInput.handleEvent(event, window);
            locationRadioButtonList.handleEvent(event, window);
            numberNextPrevTextInput.handleEvent(event, window);
        }
        window.clear(sf::Color::White);
        numberBusTextInput.draw(window);
        numberRouteTextInput.draw(window);
        driverTextInput.draw(window);
        locationRadioButtonList.draw(window);
        numberNextPrevTextInput.draw(window);
        addBusButton.draw(window);
        window.display();
    }
}

bool AddBusWindow::validateData()
{
    if (numberBusTextInput.isEmpty() ||
        numberRouteTextInput.isEmpty() ||
        driverTextInput.isEmpty() || 
        (numberNextPrevTextInput.isEmpty() && (locationRadioButtonList.getSelectedIndex() == 2 || locationRadioButtonList.getSelectedIndex() == 3))) {
        MessageBox(NULL, L"Пожалуйста, заполните все поля", L"Ошибка", MB_ICONERROR | MB_OK);
        return false;
    }
    return true;
}
