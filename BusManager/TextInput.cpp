#include "TextInput.h"

TextInput::TextInput(float x, float y, float width, float height) : isActive(false) {
    inputBox.setPosition(sf::Vector2f(x, y));
    inputBox.setSize(sf::Vector2f(width, height));
    inputBox.setFillColor(sf::Color(144, 238, 144));
    inputBox.setOutlineColor(sf::Color::Black);
    inputBox.setOutlineThickness(2);

    if (!font.loadFromFile("Fonts/Arial.ttf")) {
        std::cout << "Ошибка: Не удалось загрузить шрифт " << std::endl;
        return;
    }

    inputText.setFont(font);
    inputText.setCharacterSize(24);
    inputText.setFillColor(sf::Color::Black);
    inputText.setPosition(x + 5, y + (height - inputText.getCharacterSize()) / 2);

    cursor.setSize(sf::Vector2f(2, inputText.getCharacterSize()));
    cursor.setFillColor(sf::Color::Black);
    updateCursor();
}

TextInput::TextInput(float x, float y, float width, float height, const std::wstring& initialText)
{
    inputBox.setPosition(sf::Vector2f(x, y));
    inputBox.setSize(sf::Vector2f(width, height));
    inputBox.setFillColor(sf::Color(144, 238, 144));
    inputBox.setOutlineColor(sf::Color::Black);
    inputBox.setOutlineThickness(2);

    if (!font.loadFromFile("Fonts/Arial.ttf")) {
        std::cout << "Ошибка: Не удалось загрузить шрифт " << std::endl;
        return;
    }

    inputText.setFont(font);
    inputText.setCharacterSize(24);
    inputText.setFillColor(sf::Color::Black);
    inputText.setPosition(x + 5, y + (height - inputText.getCharacterSize()) / 2);

    cursor.setSize(sf::Vector2f(2, inputText.getCharacterSize()));
    cursor.setFillColor(sf::Color::Black);

    this->initialText = initialText;

    updateCursor();
}

void TextInput::handleEvent(const sf::Event& event, const sf::RenderWindow& window) {
    if (event.type == sf::Event::MouseButtonPressed) {
        if (inputBox.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)))) {
            isActive = true;
            if (getText() == initialText)
                inputText.setString("");
        }
        else {
            isActive = false;
        }
    }

    if (isActive && event.type == sf::Event::TextEntered) {
        if (event.text.unicode == 8) {
            if (!inputText.getString().isEmpty()) {
                std::wstring text = inputText.getString();
                text.pop_back();
                inputText.setString(text);
            }
        }
        else {
            inputText.setString(inputText.getString() + static_cast<wchar_t>(event.text.unicode));
        }
        updateCursor();
    }
    else if (!isActive && getText().empty()) {
        inputText.setString(initialText);
    }
}

void TextInput::draw(sf::RenderWindow& window) {
    window.draw(inputBox);
    window.draw(inputText);

    if (isActive) {
        if (cursorTimer.getElapsedTime().asSeconds() >= 0.5f) {
            showCursor = !showCursor;
            cursorTimer.restart();
        }

        if (showCursor) {
            window.draw(cursor);
        }
    }
}

std::wstring TextInput::getText() const {
    return inputText.getString();
}

void TextInput::setText(const std::wstring& text) {
    inputText.setString(text);
    updateCursor();
}

void TextInput::setInitialText(const std::wstring& initialText)
{
    this->initialText = initialText;
}

bool TextInput::isEmpty()
{
    return getText() == initialText;
}

void TextInput::updateCursor() {
    sf::FloatRect textBounds = inputText.getGlobalBounds();
    cursor.setPosition(textBounds.left + textBounds.width + 2, inputText.getPosition().y);
}