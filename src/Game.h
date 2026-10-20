#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "Ball.h"
#include "Paddle.h"

using namespace std;

enum class GameState {
    PLAYING,
    PAUSED,
    GAME_OVER
};

class Game {
public:
    static constexpr unsigned int WINDOW_WIDTH = 520;
    static constexpr unsigned int WINDOW_HEIGHT = 800;
    static constexpr int WINNING_SCORE = 7;

    Game();
    void run();

private:
    sf::RenderWindow window;
    GameState state;

    Paddle playerPaddle;
    Paddle aiPaddle;
    Ball ball;

    int playerScore;
    int aiScore;
    string winnerName;

    sf::Font font;
    bool hasFont;

    sf::Clock clock;

    void processEvents();
    void handleInput(float dt);
    void update(float dt);
    void render();

    void resetGame();
    void resetRound(bool serveTowardsPlayer);
    void drawCourtNet();
    void drawHUD();
    void drawOverlay(const string& title, const string& subtitle);
    void drawDigitProcedural(int digit, float startX, float startY, float size, sf::Color color);
};
