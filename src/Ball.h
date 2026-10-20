#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>

using namespace std;

class Ball {
public:
    static constexpr float RADIUS = 10.0f;
    static constexpr float INITIAL_SPEED = 380.0f;
    static constexpr float SPEED_INCREASE = 22.0f;
    static constexpr float MAX_SPEED = 750.0f;

    sf::CircleShape shape;
    sf::Vector2f velocity;
    float speed;

    Ball();

    void reset(float windowWidth, float windowHeight, bool serveTowardsPlayer);
    void update(float dt, float windowWidth);
    void reflectX();
    void reflectY(float paddleCenterX, float paddleWidth);
    void render(sf::RenderWindow& window);

    sf::FloatRect getBounds() const;
    sf::Vector2f getPosition() const;
};
