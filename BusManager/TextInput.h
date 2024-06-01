#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

class TextInput {
public:
    TextInput(float x, float y, float width, float height);

    TextInput(float x, float y, float width, float height, const std::wstring& initialText);

    void handleEvent(const sf::Event& event, const sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);

    std::wstring getText() const;
    void setText(const std::wstring& text);

    void setInitialText(const std::wstring& initialText);

    bool isEmpty();
private:
    sf::RectangleShape inputBox;
    sf::Text inputText;
    sf::Font font;

    std::wstring initialText;

    sf::RectangleShape cursor;
    bool isActive;
    bool showCursor;
    sf::Clock cursorTimer;

    void updateCursor();
};
