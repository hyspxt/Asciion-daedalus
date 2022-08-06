#include "game.hpp"

#include <ncurses.h>
#include <ctime>
#include <cmath>
#include <unistd.h>

#include "../entity/player.hpp"

Game::Game() {}
Game::Game(int leftDistance, int rightDistance, int topDistance, int bottomDistance, int startX, int startY)
{
    this->leftDistance = leftDistance;
    this->rightDistance = rightDistance;
    this->topDistance = topDistance;
    this->bottomDistance = bottomDistance;
    this->startX = startX;
    this->startY = startY;
}

void Game::ncursesSetup()
{
    initscr();
    cbreak();
    curs_set(0);
    noecho();
    nodelay(stdscr, 1);
    keypad(stdscr, true);
    use_default_colors(); // Not essential, but i noticed in some tests some bug so here it is
    start_color();
}