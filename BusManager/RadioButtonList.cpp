#include "RadioButtonList.h"

RadioButtonList::RadioButtonList(float x, float y, float width, unsigned int characterSize)
    : characterSize(characterSize), selectedIndex(-1), x(x), y(y), width(width) {
    if (!font.loadFromFile("Fonts/Arial.ttf")) {
        std::cout << "Ошибка: Не удалось загрузить шрифт " << std::endl;
        return;
    }
    listBox.setPosition(x, y);
    listBox.setSize(sf::Vector2f(width, 0));
    listBox.setFillColor(sf::Color::White);
    selectedIndex = 0;
}

void RadioButtonList::handleEvent(const sf::Event& event, const sf::RenderWindow& window) {
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

        for (size_t i = 0; i < items.size(); ++i) {
            if (items[i].button.getGlobalBounds().contains(mousePos)) {
                selectedIndex = i;
                updateButtons();
                break;
            }
        }
    }
}

void RadioButtonList::draw(sf::RenderWindow& window) {
    window.draw(listBox);

    for (const auto& item : items) {
        window.draw(item.button);
        window.draw(item.innerCircle);
        window.draw(item.label);
    }
}

void RadioButtonList::addItem(const std::wstring& label) {
    RadioButtonItem item;

    item.button.setRadius(10);
    item.button.setFillColor(sf::Color::White);
    item.button.setOutlineColor(sf::Color::Black);
    item.button.setOutlineThickness(2);
    item.button.setPosition(x + 5, y + items.size() * (characterSize + 10) + 5);

    item.innerCircle.setRadius(10);
    item.innerCircle.setFillColor(sf::Color::Black);
    item.innerCircle.setOrigin(item.innerCircle.getRadius(), item.innerCircle.getRadius());
    item.innerCircle.setPosition(item.button.getPosition().x + 10, item.button.getPosition().y + 10);
    item.innerCircle.setScale(0, 0);

    item.label.setFont(font);
    item.label.setString(label);
    item.label.setCharacterSize(characterSize);
    item.label.setFillColor(sf::Color::Black);
    item.label.setPosition(item.button.getPosition().x + 30, item.button.getPosition().y);

    item.selected = false;

    items.push_back(item);

    listBox.setSize(sf::Vector2f(width, items.size() * (characterSize + 10) + 10));
    updateButtons();
}

int RadioButtonList::getSelectedIndex() const {
    return selectedIndex;
}

void RadioButtonList::updateButtons() {
    for (size_t i = 0; i < items.size(); ++i) {
        if (i == selectedIndex) {
            items[i].innerCircle.setScale(1, 1);
            items[i].selected = true;
        }
        else {
            items[i].innerCircle.setScale(0, 0);
            items[i].selected = false;
        }
    }
}