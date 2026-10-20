#include "Game.h"
#include <ctime>
#include <cstdlib>

using namespace std;

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));

    Game pongGame;
    pongGame.run();

    return 0;
}
