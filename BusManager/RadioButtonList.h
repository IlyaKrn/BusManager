#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>

class RadioButtonList {
public:
    RadioButtonList(float x, float y, float width, unsigned int characterSize = 24);

    void handleEvent(const sf::Event& event, const sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);

    void addItem(const std::wstring& label);
    int getSelectedIndex() const;

private:
    struct RadioButtonItem {
        sf::CircleShape button;
        sf::CircleShape innerCircle;
        sf::Text label;
        bool selected;
    };

    void updateButtons();

    sf::RectangleShape listBox;
    sf::Font font;
    unsigned int characterSize;
    std::vector<RadioButtonItem> items;
    int selectedIndex;
    float x;
    float y;
    float width;
};

