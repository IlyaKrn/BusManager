#include "Button.h"

Button::Button(float x, float y, float width, float height, const std::wstring& text):buttonText(sf::Text())
{
    if (!font.loadFromFile("Fonts/Arial.ttf")) {
        std::cout << "Ошибка: Не удалось загрузить шрифт " << std::endl;
        return;
    }

    if (!buttonTexture.loadFromFile("Texture/buttonTexture.png")) {
        std::cout << "Ошибка: Не удалось загрузить текстуру " << std::endl;
        return;
    }

    buttonShape.setPosition(sf::Vector2f(x, y));
    buttonShape.setSize(sf::Vector2f(width, height));
    buttonShape.setTexture(&buttonTexture);
    buttonShape.setFillColor(sf::Color(70, 130, 180));

    buttonText.setFont(font);
    buttonText.setString(text);
    buttonText.setCharacterSize(24);
    buttonText.setFillColor(sf::Color::Black);

    sf::FloatRect textRect = buttonText.getLocalBounds();
    buttonText.setOrigin(textRect.left + textRect.width / 2.0f,
        textRect.top + textRect.height / 2.0f);
    buttonText.setPosition(sf::Vector2f(x + width / 2.0f, y + height / 2.0f));
}

Button::Button(float x, float y, float width, float height)
{
    if (!font.loadFromFile("Fonts/Arial.ttf")) {
        std::cout << "Ошибка: Не удалось загрузить шрифт " << std::endl;
        return;
    }

    if (!buttonTexture.loadFromFile("Texture/buttonTexture.png")) {
        std::cout << "Ошибка: Не удалось загрузить текстуру " << std::endl;
        return;
    }
    buttonShape.setPosition(sf::Vector2f(x, y));
    buttonShape.setSize(sf::Vector2f(width, height));
    buttonShape.setTexture(&buttonTexture);
    buttonShape.setFillColor(sf::Color(70, 130, 180));

    buttonText.setFont(font);
    buttonText.setCharacterSize(24);
    buttonText.setFillColor(sf::Color::White);

    sf::FloatRect textRect = buttonText.getLocalBounds();
    buttonText.setOrigin(textRect.left + textRect.width / 2.0f,
        textRect.top + textRect.height / 2.0f);
    buttonText.setPosition(sf::Vector2f(x + width / 2.0f, y + height / 2.0f));
}

void Button::setText(const std::string& text)
{
    buttonText.setString(text);
}

void Button::setPosition(float x, float y)
{
    buttonShape.setPosition(sf::Vector2f(x, y));
    sf::FloatRect textRect = buttonText.getLocalBounds();
    buttonText.setOrigin(textRect.left + textRect.width / 2.0f,
        textRect.top + textRect.height / 2.0f);
    buttonText.setPosition(sf::Vector2f(x + buttonShape.getSize().x / 2.0f, y + buttonShape.getSize().y / 2.0f));
}

void Button::setSize(float width, float height)
{
    buttonShape.setSize(sf::Vector2f(width, height));
}

void Button::draw(sf::RenderWindow& window)
{
    window.draw(buttonShape);
    window.draw(buttonText);
}

void Button::resetColor()
{
    buttonShape.setFillColor(sf::Color(70, 130, 180));
}

bool Button::isClicked(const sf::Vector2i& mousePos)
{
    if (buttonShape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
        buttonShape.setFillColor(sf::Color(120, 120, 120));
        return true;
    }
    return false;
}
