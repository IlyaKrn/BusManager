#include "ScrollableList.h"

ScrollableList::ScrollableList(float x, float y, float width, float height, unsigned int characterSize)
    : characterSize(characterSize), scrollOffset(0), scrollSpeed(30), viewHeight(height) {

    if (!font.loadFromFile("Fonts/Arial.ttf")) {
        std::cout << "Ошибка: Не удалось загрузить шрифт" << std::endl;
        return;
    }

    listBox.setPosition(x, y);
    listBox.setSize(sf::Vector2f(width, height));
    listBox.setFillColor(sf::Color::White);

    border.setPosition(x, y);
    border.setSize(sf::Vector2f(width, height));
    border.setFillColor(sf::Color::Transparent);
    border.setOutlineThickness(2);
    border.setOutlineColor(sf::Color::Black);

    view.reset(sf::FloatRect(0, 0, width, height));
    view.setViewport(sf::FloatRect(x / 1650.0f, y / 900.0f, width / 1650.0f, height / 900.0f));

    scrollbar.setSize(sf::Vector2f(10, 50));
    scrollbar.setPosition(x + width - scrollbar.getSize().x, y);
    scrollbar.setFillColor(sf::Color(200, 200, 200));
}

void ScrollableList::handleEvent(const sf::Event& event) {
    if (event.type == sf::Event::MouseWheelScrolled) {
        if (event.mouseWheelScroll.delta > 0) {
            scrollOffset -= scrollSpeed;
        }
        else {
            scrollOffset += scrollSpeed;
        }

        scrollOffset = std::max(0.0f, std::min(scrollOffset, maxScrollOffset));
        updateView();
    }
}

void ScrollableList::draw(sf::RenderWindow& window) {
    window.setView(view);
    window.draw(listBox);

    for (const auto& itemRow : items) {
        for (const auto& item : itemRow) {
            window.draw(item);
        }
    }

    window.setView(window.getDefaultView());
    for (const auto& header : headers) {
        window.draw(header);
    }

    window.draw(border);
    window.draw(scrollbar);
}

void ScrollableList::addItem(const std::list<std::string>& item) {
    std::vector<sf::Text> row;
    float x = listBox.getPosition().x + 5;
    float y = listBox.getGlobalBounds().left + headers.size() * (characterSize + 10) + items.size() * (characterSize + 10) - scrollOffset - characterSize;

    for (const auto& cell : item) {
        sf::Text text;
        text.setFont(font);
        text.setString(cell);
        text.setCharacterSize(characterSize);
        text.setFillColor(sf::Color::Black);
        text.setPosition(x, y);

        row.push_back(text);
        x += listBox.getSize().x / item.size();
    }

    items.push_back(row);

    float contentHeight = headers.size() * (characterSize + 10) + items.size() * (characterSize + 10);
    maxScrollOffset = std::max(0.0f, contentHeight - viewHeight);
    updateView();
}

void ScrollableList::setHeaders(const std::vector<std::wstring>& headersText) {
    headers.clear();
    float x = listBox.getPosition().x + 5;
    float y = listBox.getPosition().y - 50;

    for (const auto& header : headersText) {
        sf::Text text;
        text.setFont(font);
        text.setString(header);
        text.setCharacterSize(characterSize);
        text.setFillColor(sf::Color::Black);
        text.setStyle(sf::Text::Bold);
        text.setPosition(x, y);

        headers.push_back(text);
        x += listBox.getSize().x / headersText.size();
    }
}

void ScrollableList::clearItems() {
    items.clear();
    scrollOffset = 0;
    maxScrollOffset = 0;
    updateView();
}

void ScrollableList::updateView() {
    view.setCenter(view.getSize().x / 2, scrollOffset + viewHeight / 2);

    float contentHeight = headers.size() * (characterSize + 10) + items.size() * (characterSize + 10);
    float scrollbarHeight = (viewHeight / contentHeight) * viewHeight;
    scrollbar.setSize(sf::Vector2f(scrollbar.getSize().x, scrollbarHeight));
    scrollbar.setPosition(scrollbar.getPosition().x, listBox.getPosition().y + (scrollOffset / contentHeight) * viewHeight);
}
