#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Button
{
public:
    Button(float x, float y, float width, float height, const std::wstring& text);

    Button(float x, float y, float width, float height);

    void setText(const std::string& text);

    void setPosition(float x, float y);

    void setSize(float width, float height);

    void draw(sf::RenderWindow& window);

    void resetColor();

    bool isClicked(const sf::Vector2i& mousePos);
private:
    sf::RectangleShape buttonShape;

    sf::Text buttonText;

    sf::Font font;

    sf::Texture buttonTexture;
};

