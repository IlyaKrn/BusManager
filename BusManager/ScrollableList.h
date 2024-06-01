#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>
#include <list>
#include "BusModel.h"

class ScrollableList {
public:
    ScrollableList(float x, float y, float width, float height, unsigned int characterSize = 30);

    void handleEvent(const sf::Event& event);
    void draw(sf::RenderWindow& window);

    void addItem(const std::list<std::string>& item);
    void setHeaders(const std::vector<std::wstring>& headers);
    void clearItems();
private:
    void updateView();

    sf::RectangleShape listBox;
    sf::RectangleShape border;
    sf::View view;
    sf::Font font;
    unsigned int characterSize;
    float scrollOffset;
    float maxScrollOffset;
    float scrollSpeed;
    float viewHeight;
    sf::RectangleShape scrollbar;
    std::vector<sf::Text> headers;
    std::vector<std::vector<sf::Text>> items;
};
