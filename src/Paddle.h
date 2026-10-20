#pragma once
#include <SFML/Graphics.hpp>

using namespace std;

class Paddle {
public:
    static constexpr float DEFAULT_WIDTH = 110.0f;
    static constexpr float DEFAULT_HEIGHT = 16.0f;
    static constexpr float MOVE_SPEED = 480.0f;

    sf::RectangleShape shape;
    float width;
    float height;
    float speed;
    sf::Color neonColor;

    Paddle(float startX, float startY, float w = DEFAULT_WIDTH, float h = DEFAULT_HEIGHT, sf::Color color = sf::Color(0, 229, 255));

    void moveLeft(float dt);
    void moveRight(float dt, float windowWidth);
    void updateAI(float targetX, float dt, float windowWidth);
    void render(sf::RenderWindow& window);

    sf::FloatRect getBounds() const;
    sf::Vector2f getPosition() const;
    float getCenterX() const;
};
