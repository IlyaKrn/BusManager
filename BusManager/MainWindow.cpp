#include "MainWindow.h"
#include "AddBusWindow.h"
#include "Manager.h"
#include "SendBusWindow.h"

MainWindow::MainWindow() :window(sf::VideoMode(1650, 900), L"Управление автобусами"),
                        allBusButton(Button(25, 50, 300, 100, L"Все автобусы")),
                        inParkBusButton(Button(350, 50, 300, 100, L"В парке")),
                        onRouteBusButton(Button(675, 50, 300, 100, L"На маршруте")),
                        addBusButton(Button(1000, 50, 300, 100, L"Добавить автобус")),
                        sendBusButton(Button(1325, 50, 300, 100, L"Отправить автобус в")),
                        infoBusesTable(ScrollableList(25, 250, 1600, 600))
{
 

    infoBusesTable.setHeaders({ L"Номер автобуса",L"Номер маршрута",L"Водитель" });
}

void MainWindow::show()
{
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    Manager m = Manager();
                    if (addBusButton.isClicked(sf::Mouse::getPosition(window))) {
                        AddBusWindow addWindow;
                        addWindow.show();
                    }
                    else if (sendBusButton.isClicked(sf::Mouse::getPosition(window))) {
                        SendBusWindow sendWindow;
                        sendWindow.show();
                    }
                    else if (inParkBusButton.isClicked(sf::Mouse::getPosition(window))) {
                        infoBusesTable.clearItems();
                        for (BusModel& bus : m.getState()) {
                            infoBusesTable.addItem({ bus.getBusNumber(), bus.getRouteNumber(), bus.getDriver() });
                        }
                    }
                    else if (onRouteBusButton.isClicked(sf::Mouse::getPosition(window))) {
                        infoBusesTable.clearItems();
                        for (BusModel& bus : m.getDriving()) {
                            infoBusesTable.addItem({ bus.getBusNumber(), bus.getRouteNumber(), bus.getDriver() });
                        }
                    }
                    else if (allBusButton.isClicked(sf::Mouse::getPosition(window))) {
                        infoBusesTable.clearItems();
                        for (BusModel& bus : m.getAll()) {
                            infoBusesTable.addItem({ bus.getBusNumber(), bus.getRouteNumber(), bus.getDriver() });
                        }
                    }
                }
            }
            else if (event.type == sf::Event::MouseButtonReleased) {
                addBusButton.resetColor();
                inParkBusButton.resetColor();
                onRouteBusButton.resetColor();
                allBusButton.resetColor();
                sendBusButton.resetColor();
            }
            infoBusesTable.handleEvent(event);
        }
        window.clear(sf::Color::White);
        addBusButton.draw(window);
        inParkBusButton.draw(window);
        onRouteBusButton.draw(window);
        allBusButton.draw(window);
        sendBusButton.draw(window);
        infoBusesTable.draw(window);
        window.display();
    }
}
