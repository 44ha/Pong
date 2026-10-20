#include "Game.h"
#include <iostream>
#include <vector>

using namespace std;

Game::Game()
    : window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Pong", sf::Style::Titlebar | sf::Style::Close),
      state(GameState::PLAYING),
      playerPaddle((WINDOW_WIDTH - Paddle::DEFAULT_WIDTH) / 2.0f, WINDOW_HEIGHT - 48.0f, Paddle::DEFAULT_WIDTH, Paddle::DEFAULT_HEIGHT, sf::Color(0, 240, 255)),
      aiPaddle((WINDOW_WIDTH - Paddle::DEFAULT_WIDTH) / 2.0f, 32.0f, Paddle::DEFAULT_WIDTH, Paddle::DEFAULT_HEIGHT, sf::Color(255, 75, 130)),
      playerScore(0),
      aiScore(0),
      winnerName(""),
      hasFont(false) {

    window.setFramerateLimit(60);

    const vector<string> fontPaths = {
        "assets/font.ttf",
        "assets/arial.ttf",
        "C:/Windows/Fonts/arial.ttf",
        "C:/Windows/Fonts/consola.ttf",
        "C:/Windows/Fonts/segoeui.ttf"
    };

    for (const auto& path : fontPaths) {
        if (font.loadFromFile(path)) {
            hasFont = true;
            break;
        }
    }

    resetRound(true);
}

void Game::resetRound(bool serveTowardsPlayer) {
    ball.reset(static_cast<float>(WINDOW_WIDTH), static_cast<float>(WINDOW_HEIGHT), serveTowardsPlayer);
}

void Game::resetGame() {
    playerScore = 0;
    aiScore = 0;
    winnerName = "";
    state = GameState::PLAYING;
    playerPaddle.shape.setPosition((WINDOW_WIDTH - Paddle::DEFAULT_WIDTH) / 2.0f, WINDOW_HEIGHT - 48.0f);
    aiPaddle.shape.setPosition((WINDOW_WIDTH - Paddle::DEFAULT_WIDTH) / 2.0f, 32.0f);
    resetRound(true);
}

void Game::run() {
    clock.restart();

    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();
        if (dt > 0.05f) dt = 0.05f;

        processEvents();
        handleInput(dt);
        update(dt);
        render();
    }
}

void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::P) {
                if (state == GameState::PLAYING) {
                    state = GameState::PAUSED;
                } else if (state == GameState::PAUSED) {
                    state = GameState::PLAYING;
                }
            }

            if (event.key.code == sf::Keyboard::R) {
                resetGame();
            }

            if (event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
        }
    }
}

void Game::handleInput(float dt) {
    if (state != GameState::PLAYING) return;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        playerPaddle.moveLeft(dt);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        playerPaddle.moveRight(dt, static_cast<float>(WINDOW_WIDTH));
    }
}

void Game::update(float dt) {
    if (state != GameState::PLAYING) return;

    aiPaddle.updateAI(ball.getPosition().x, dt, static_cast<float>(WINDOW_WIDTH));

    ball.update(dt, static_cast<float>(WINDOW_WIDTH));

    sf::FloatRect ballBounds = ball.getBounds();
    sf::FloatRect playerBounds = playerPaddle.getBounds();
    sf::FloatRect aiBounds = aiPaddle.getBounds();

    if (ballBounds.intersects(playerBounds) && ball.velocity.y > 0.0f) {
        ball.reflectY(playerPaddle.getCenterX(), playerPaddle.width);
        ball.shape.setPosition(ball.getPosition().x, playerBounds.top - Ball::RADIUS);
    }

    if (ballBounds.intersects(aiBounds) && ball.velocity.y < 0.0f) {
        ball.reflectY(aiPaddle.getCenterX(), aiPaddle.width);
        ball.shape.setPosition(ball.getPosition().x, aiBounds.top + aiBounds.height + Ball::RADIUS);
    }

    if (ball.getPosition().y - Ball::RADIUS > static_cast<float>(WINDOW_HEIGHT)) {
        aiScore++;
        if (aiScore >= WINNING_SCORE) {
            state = GameState::GAME_OVER;
            winnerName = "AI WINS!";
        } else {
            resetRound(false);
        }
    }
    else if (ball.getPosition().y + Ball::RADIUS < 0.0f) {
        playerScore++;
        if (playerScore >= WINNING_SCORE) {
            state = GameState::GAME_OVER;
            winnerName = "YOU WIN!";
        } else {
            resetRound(true);
        }
    }
}

void Game::drawCourtNet() {
    float midY = WINDOW_HEIGHT / 2.0f;
    float dashWidth = 14.0f;
    float dashHeight = 3.0f;
    float gap = 10.0f;

    for (float x = 15.0f; x < WINDOW_WIDTH - 15.0f; x += (dashWidth + gap)) {
        sf::RectangleShape dash(sf::Vector2f(dashWidth, dashHeight));
        dash.setPosition(x, midY - (dashHeight / 2.0f));
        dash.setFillColor(sf::Color(255, 255, 255, 45));
        window.draw(dash);
    }

    sf::RectangleShape leftBorder(sf::Vector2f(3.0f, static_cast<float>(WINDOW_HEIGHT)));
    leftBorder.setPosition(0.0f, 0.0f);
    leftBorder.setFillColor(sf::Color(0, 220, 255, 60));
    window.draw(leftBorder);

    sf::RectangleShape rightBorder(sf::Vector2f(3.0f, static_cast<float>(WINDOW_HEIGHT)));
    rightBorder.setPosition(WINDOW_WIDTH - 3.0f, 0.0f);
    rightBorder.setFillColor(sf::Color(0, 220, 255, 60));
    window.draw(rightBorder);
}

void Game::drawHUD() {
    if (hasFont) {
        sf::Text aiText;
        aiText.setFont(font);
        aiText.setString(to_string(aiScore));
        aiText.setCharacterSize(44);
        aiText.setFillColor(sf::Color(255, 75, 130, 160));
        sf::FloatRect aiBounds = aiText.getLocalBounds();
        aiText.setOrigin(aiBounds.left + aiBounds.width / 2.0f, aiBounds.top + aiBounds.height / 2.0f);
        aiText.setPosition(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f - 60.0f);
        window.draw(aiText);

        sf::Text playerText;
        playerText.setFont(font);
        playerText.setString(to_string(playerScore));
        playerText.setCharacterSize(44);
        playerText.setFillColor(sf::Color(0, 240, 255, 160));
        sf::FloatRect pBounds = playerText.getLocalBounds();
        playerText.setOrigin(pBounds.left + pBounds.width / 2.0f, pBounds.top + pBounds.height / 2.0f);
        playerText.setPosition(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f + 60.0f);
        window.draw(playerText);

        sf::Text tipText;
        tipText.setFont(font);
        tipText.setString("<- / -> Move   |   P: Pause   |   R: Restart");
        tipText.setCharacterSize(14);
        tipText.setFillColor(sf::Color(120, 150, 180, 140));
        sf::FloatRect tipBounds = tipText.getLocalBounds();
        tipText.setOrigin(tipBounds.left + tipBounds.width / 2.0f, tipBounds.top + tipBounds.height / 2.0f);
        tipText.setPosition(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT - 14.0f);
        window.draw(tipText);
    } else {
        drawDigitProcedural(aiScore, WINDOW_WIDTH / 2.0f - 14.0f, WINDOW_HEIGHT / 2.0f - 75.0f, 28.0f, sf::Color(255, 75, 130, 180));
        drawDigitProcedural(playerScore, WINDOW_WIDTH / 2.0f - 14.0f, WINDOW_HEIGHT / 2.0f + 45.0f, 28.0f, sf::Color(0, 240, 255, 180));
    }
}

void Game::drawDigitProcedural(int digit, float startX, float startY, float size, sf::Color color) {
    if (digit < 0 || digit > 9) return;
    float thick = size * 0.18f;
    float length = size;

    const bool seg[10][7] = {
        {1,1,1,0,1,1,1},
        {0,0,1,0,0,1,0},
        {1,0,1,1,1,0,1},
        {1,0,1,1,0,1,1},
        {0,1,1,1,0,1,0},
        {1,1,0,1,0,1,1},
        {1,1,0,1,1,1,1},
        {1,0,1,0,0,1,0},
        {1,1,1,1,1,1,1},
        {1,1,1,1,0,1,1}
    };

    auto drawSeg = [&](float x, float y, float w, float h) {
        sf::RectangleShape r(sf::Vector2f(w, h));
        r.setPosition(x, y);
        r.setFillColor(color);
        window.draw(r);
    };

    if (seg[digit][0]) drawSeg(startX, startY, length, thick);
    if (seg[digit][1]) drawSeg(startX, startY, thick, length);
    if (seg[digit][2]) drawSeg(startX + length - thick, startY, thick, length);
    if (seg[digit][3]) drawSeg(startX, startY + length - thick / 2, length, thick);
    if (seg[digit][4]) drawSeg(startX, startY + length, thick, length);
    if (seg[digit][5]) drawSeg(startX + length - thick, startY + length, thick, length);
    if (seg[digit][6]) drawSeg(startX, startY + 2 * length - thick, length, thick);
}

void Game::drawOverlay(const string& title, const string& subtitle) {
    sf::RectangleShape dim(sf::Vector2f(static_cast<float>(WINDOW_WIDTH), static_cast<float>(WINDOW_HEIGHT)));
    dim.setFillColor(sf::Color(8, 12, 22, 190));
    window.draw(dim);

    float boxW = 340.0f;
    float boxH = 170.0f;
    sf::RectangleShape box(sf::Vector2f(boxW, boxH));
    box.setPosition((WINDOW_WIDTH - boxW) / 2.0f, (WINDOW_HEIGHT - boxH) / 2.0f);
    box.setFillColor(sf::Color(14, 22, 38, 230));
    box.setOutlineThickness(2.0f);
    box.setOutlineColor(sf::Color(0, 240, 255, 180));
    window.draw(box);

    if (hasFont) {
        sf::Text tText;
        tText.setFont(font);
        tText.setString(title);
        tText.setCharacterSize(36);
        tText.setFillColor(sf::Color(0, 240, 255));
        sf::FloatRect tb = tText.getLocalBounds();
        tText.setOrigin(tb.left + tb.width / 2.0f, tb.top + tb.height / 2.0f);
        tText.setPosition(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f - 24.0f);
        window.draw(tText);

        sf::Text sText;
        sText.setFont(font);
        sText.setString(subtitle);
        sText.setCharacterSize(16);
        sText.setFillColor(sf::Color(220, 235, 250));
        sf::FloatRect sb = sText.getLocalBounds();
        sText.setOrigin(sb.left + sb.width / 2.0f, sb.top + sb.height / 2.0f);
        sText.setPosition(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f + 32.0f);
        window.draw(sText);
    }
}

void Game::render() {
    window.clear(sf::Color(10, 14, 24));

    drawCourtNet();
    drawHUD();

    playerPaddle.render(window);
    aiPaddle.render(window);
    ball.render(window);

    if (state == GameState::PAUSED) {
        drawOverlay("PAUSED", "Press [P] to Resume   |   [R] to Restart");
    } else if (state == GameState::GAME_OVER) {
        drawOverlay(winnerName, "Press [R] to Play Again");
    }

    window.display();
}
