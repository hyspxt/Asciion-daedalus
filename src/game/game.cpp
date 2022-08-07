#include "game.hpp"
#include "../gameEnvironment/gameEnvironment.hpp"

#include <ncurses.h>
#include <ctime>
#include <cmath>
#include <iostream>
#include <unistd.h>
#include <string.h>

Game::Game() {}
Game::Game(int leftDistance, int rightDistance, int topDistance, int bottomDistance, int maxX, int maxY)
{
    this->leftDistance = leftDistance;
    this->rightDistance = rightDistance;
    this->topDistance = topDistance;
    this->bottomDistance = bottomDistance;
    this->maxX = maxX;
    this->maxY = maxY;
}

void Game::ncursesSetup()
{
    initscr();
    cbreak();
    curs_set(0);
    noecho();
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);
    use_default_colors(); // Not essential, but i noticed in some tests some bug so here it is
    start_color();
}

void Game::ncursesStop()
{
    noraw();
    endwin(); // Remember to delete the Getch and deallocation of ncurses!! TODO
    getch();
}

void Game::movePlayer(Player player)
{

    int direction = getch();
    int y = player.getY();
    int x = player.getX();
    int ch = 0;

    while(direction != 10){       // In future in this while needs to stay all commands available during the play
        if (direction == 258) // Down
        {
            ch = mvinch(y + 1, x) & A_CHARTEXT;
            if (ch != '-')
            {
               
                mvprintw(y, x, " ");
                 y = y + 1;
                move(y, x);
                printw("C");
            }
        }
        if (direction == 259)  // Up
        {
            ch = mvinch(y - 1, x) & A_CHARTEXT;
            if (ch != '-')
            {
                
                mvprintw(y,x, " ");
                y = y - 1;
                move(y, x);
                printw("C");
            }
        }
          if (direction == 260) // Left
        {
            ch = mvinch(y, x - 1) & A_CHARTEXT;
            if (ch != '|')
            {
               
                mvprintw(y, x, " ");
                 x = x - 1;
                move(y, x);
                printw("C");
            }
        }
        if (direction == 261)  // Right
        {
            ch = mvinch(y, x + 1) & A_CHARTEXT;
            if (ch != '|')
            {
                mvprintw(y,x, " ");
                x = x + 1;
                move(y, x);
                printw("C");
            }
        }
        direction = getch();
    }
    
}