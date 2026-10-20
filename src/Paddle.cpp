#include "Paddle.h"
#include <algorithm>
#include <cmath>

using namespace std;

Paddle::Paddle(float startX, float startY, float w, float h, sf::Color color)
    : width(w), height(h), speed(MOVE_SPEED), color(color) {
    shape.setSize(sf::Vector2f(width, height));
    shape.setPosition(startX, startY);
    shape.setFillColor(color);
}

void Paddle::moveLeft(float dt) {
    sf::Vector2f pos = shape.getPosition();
    pos.x -= speed * dt;
    if (pos.x < 0.0f) {
        pos.x = 0.0f;
    }
    shape.setPosition(pos);
}

void Paddle::moveRight(float dt, float windowWidth) {
    sf::Vector2f pos = shape.getPosition();
    pos.x += speed * dt;
    if (pos.x + width > windowWidth) {
        pos.x = windowWidth - width;
    }
    shape.setPosition(pos);
}

void Paddle::updateAI(float targetX, float dt, float windowWidth) {
    float currentCenter = getCenterX();
    float diff = targetX - currentCenter;
    float deadZone = 10.0f;

    float aiSpeed = speed * 0.85f;

    if (abs(diff) > deadZone) {
        if (diff < 0) {
            sf::Vector2f pos = shape.getPosition();
            pos.x -= aiSpeed * dt;
            if (pos.x < 0.0f) pos.x = 0.0f;
            shape.setPosition(pos);
        } else {
            sf::Vector2f pos = shape.getPosition();
            pos.x += aiSpeed * dt;
            if (pos.x + width > windowWidth) pos.x = windowWidth - width;
            shape.setPosition(pos);
        }
    }
}

void Paddle::render(sf::RenderWindow& window) {
    sf::Vector2f pos = shape.getPosition();

    sf::RectangleShape glow(sf::Vector2f(width + 8.0f, height + 8.0f));
    glow.setPosition(pos.x - 4.0f, pos.y - 4.0f);
    glow.setFillColor(sf::Color(color.r, color.g, color.b, 65));
    window.draw(glow);

    window.draw(shape);
}

sf::FloatRect Paddle::getBounds() const {
    return shape.getGlobalBounds();
}

sf::Vector2f Paddle::getPosition() const {
    return shape.getPosition();
}

float Paddle::getCenterX() const {
    return shape.getPosition().x + (width / 2.0f);
}
