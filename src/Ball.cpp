#include "Ball.h"
#include <cstdlib>
#include <algorithm>

using namespace std;

Ball::Ball() : speed(INITIAL_SPEED) {
    shape.setRadius(RADIUS);
    shape.setOrigin(RADIUS, RADIUS);
    shape.setFillColor(sf::Color(240, 255, 255));
}

void Ball::reset(float windowWidth, float windowHeight, bool serveTowardsPlayer) {
    speed = INITIAL_SPEED;
    shape.setPosition(windowWidth / 2.0f, windowHeight / 2.0f);

    float initialAngleFactor = ((rand() % 100) / 100.0f - 0.5f) * 0.8f;
    float dirY = serveTowardsPlayer ? 1.0f : -1.0f;

    sf::Vector2f dir(initialAngleFactor, dirY);
    float length = sqrt(dir.x * dir.x + dir.y * dir.y);
    velocity = (dir / length) * speed;
}

void Ball::update(float dt, float windowWidth) {
    shape.move(velocity * dt);

    sf::Vector2f pos = shape.getPosition();

    if (pos.x - RADIUS <= 0.0f) {
        shape.setPosition(RADIUS, pos.y);
        reflectX();
    } else if (pos.x + RADIUS >= windowWidth) {
        shape.setPosition(windowWidth - RADIUS, pos.y);
        reflectX();
    }
}

void Ball::reflectX() {
    velocity.x = -velocity.x;
}

void Ball::reflectY(float paddleCenterX, float paddleWidth) {
    float halfWidth = paddleWidth / 2.0f;
    float offset = (shape.getPosition().x - paddleCenterX) / halfWidth;
    offset = max(-1.0f, min(1.0f, offset));

    speed = min(speed + SPEED_INCREASE, MAX_SPEED);

    float newDirY = (velocity.y > 0.0f) ? -1.0f : 1.0f;
    float newDirX = offset * 1.35f;

    sf::Vector2f newDir(newDirX, newDirY);
    float length = sqrt(newDir.x * newDir.x + newDir.y * newDir.y);
    velocity = (newDir / length) * speed;
}

void Ball::render(sf::RenderWindow& window) {
    sf::Vector2f pos = shape.getPosition();

    sf::CircleShape glow(RADIUS * 1.8f);
    glow.setOrigin(RADIUS * 1.8f, RADIUS * 1.8f);
    glow.setPosition(pos);
    glow.setFillColor(sf::Color(0, 240, 255, 60));
    window.draw(glow);

    sf::CircleShape midGlow(RADIUS * 1.35f);
    midGlow.setOrigin(RADIUS * 1.35f, RADIUS * 1.35f);
    midGlow.setPosition(pos);
    midGlow.setFillColor(sf::Color(0, 240, 255, 120));
    window.draw(midGlow);

    window.draw(shape);
}

sf::FloatRect Ball::getBounds() const {
    return shape.getGlobalBounds();
}

sf::Vector2f Ball::getPosition() const {
    return shape.getPosition();
}
