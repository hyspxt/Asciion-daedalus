#include "gameEnvironment.hpp"

#include <ncurses.h>
#include <iostream>
#include <ctime>
#include <string.h>
#include <unistd.h>
#include <cmath>

GameEnvironment::GameEnvironment(){};
void GameEnvironment::printMenuLogo()
{
    initscr();
    start_color();
    init_pair(1, COLOR_CYAN, 232);
    attron(COLOR_PAIR(1));
    mvprintw(LINES / 2 - 12, COLS / 2 - 54,
             "                                                                                                            ");
    mvprintw(LINES / 2 - 11, COLS / 2 - 54,
             "    #     #####   #####  ### ###                   ######                                                   ");
    mvprintw(LINES / 2 - 10, COLS / 2 - 54,
             "   # #   #     # #     #  #   #   ####  #    #     #     #   ##   ###### #####    ##   #      #    #  ####  ");
    mvprintw(LINES / 2 - 9, COLS / 2 - 54,
             "  #   #  #       #        #   #  #    # ##   #     #     #  #  #  #      #    #  #  #  #      #    # #      ");
    mvprintw(LINES / 2 - 8, COLS / 2 - 54,
             " #     #  #####  #        #   #  #    # # #  #     #     # #    # #####  #    # #    # #      #    #  ####  ");
    mvprintw(LINES / 2 - 7, COLS / 2 - 54,
             " #######       # #        #   #  #    # #  # #     #     # ###### #      #    # ###### #      #    #      # ");
    mvprintw(LINES / 2 - 6, COLS / 2 - 54,
             " #     # #     # #     #  #   #  #    # #   ##     #     # #    # #      #    # #    # #      #    # #    # ");
    mvprintw(LINES / 2 - 5, COLS / 2 - 54,
             " #     #  #####   #####  ### ###  ####  #    #     ######  #    # ###### #####  #    # ######  ####   ####  ");
    mvprintw(LINES / 2 - 4, COLS / 2 - 54,
             "                                                                                                            ");
    attroff(COLOR_PAIR(1));
}

void GameEnvironment::printMenuChoices(int choice)
{ // Choice variable colors active button

    init_pair(2, COLOR_BLACK, COLOR_CYAN);

    mvprintw(LINES / 2 - 2, COLS / 2 - 17,
             "                             ");
    mvprintw(LINES / 2 - 1, COLS / 2 - 17,
             "            PLAY!            ");
    mvprintw(LINES / 2, COLS / 2 - 17,
             "                             ");

    mvprintw(LINES / 2 + 1, COLS / 2 - 17,
             "                             ");
    mvprintw(LINES / 2 + 2, COLS / 2 - 17,
             "          HOW TO PLAY        ");
    mvprintw(LINES / 2 + 3, COLS / 2 - 17,
             "                             ");

    mvprintw(LINES / 2 + 4, COLS / 2 - 17,
             "                             ");
    mvprintw(LINES / 2 + 5, COLS / 2 - 17,
             "          SCOREBOARD         ");
    mvprintw(LINES / 2 + 6, COLS / 2 - 17,
             "                             ");

    mvprintw(LINES / 2 + 7, COLS / 2 - 17,
             "                             ");
    mvprintw(LINES / 2 + 8, COLS / 2 - 17,
             "           SETTINGS          ");
    mvprintw(LINES / 2 + 9, COLS / 2 - 17,
             "                             ");

    mvprintw(LINES / 2 + 10, COLS / 2 - 17,
             "                             ");
    mvprintw(LINES / 2 + 11, COLS / 2 - 17,
             "             QUIT            ");
    mvprintw(LINES / 2 + 12, COLS / 2 - 17,
             "                             ");

    switch (choice)
    { // This switch draw the selected colored button
    case 0:
        attron(COLOR_PAIR(2));
        mvprintw(LINES / 2 - 2, COLS / 2 - 17,
                 "                             ");
        mvprintw(LINES / 2 - 1, COLS / 2 - 17,
                 "            PLAY!            ");
        mvprintw(LINES / 2, COLS / 2 - 17,
                 "                             ");
        attroff(COLOR_PAIR(2));
        break;
    case 1:
        attron(COLOR_PAIR(2));
        mvprintw(LINES / 2 + 1, COLS / 2 - 17,
                 "                             ");
        mvprintw(LINES / 2 + 2, COLS / 2 - 17,
                 "          HOW TO PLAY        ");
        mvprintw(LINES / 2 + 3, COLS / 2 - 17,
                 "                             ");
        attroff(COLOR_PAIR(2));
        break;
    case 2:
        attron(COLOR_PAIR(2));
        mvprintw(LINES / 2 + 4, COLS / 2 - 17,
                 "                             ");
        mvprintw(LINES / 2 + 5, COLS / 2 - 17,
                 "          SCOREBOARD         ");
        mvprintw(LINES / 2 + 6, COLS / 2 - 17,
                 "                             ");
        attroff(COLOR_PAIR(2));
        break;
    case 3:
        attron(COLOR_PAIR(2));
        mvprintw(LINES / 2 + 7, COLS / 2 - 17,
                 "                             ");
        mvprintw(LINES / 2 + 8, COLS / 2 - 17,
                 "           SETTINGS          ");
        mvprintw(LINES / 2 + 9, COLS / 2 - 17,
                 "                             ");
        attroff(COLOR_PAIR(2));
        break;
    case 4:
        attron(COLOR_PAIR(2));
        mvprintw(LINES / 2 + 10, COLS / 2 - 17,
                 "                             ");
        mvprintw(LINES / 2 + 11, COLS / 2 - 17,
                 "             QUIT            ");
        mvprintw(LINES / 2 + 12, COLS / 2 - 17,
                 "                             ");
        attroff(COLOR_PAIR(2));
        break;
    }
    mvprintw(LINES / 2 + 14, COLS / 2 - 17,
             "  PRESS [SPACE] TO CONTINUE       ");
}

void GameEnvironment::printHowToPlay()
{
    refresh();
    clear();
    initscr();
    start_color();

    init_pair(3, COLOR_YELLOW, 232);
    attron(COLOR_PAIR(3));
    mvprintw(LINES / 2 - 12, COLS / 2 - 50,
             "                             _  _              _              _           "
             "                           ");
    mvprintw(LINES / 2 - 11, COLS / 2 - 50,
             "                            | || |_____ __ __ | |_ ___   _ __| |__ _ _  _ "
             "                           ");
    mvprintw(LINES / 2 - 10, COLS / 2 - 50,
             "                            | __ / _ \\ V  V / |  _/ _ \\ | '_ \\ / _` | || |"
             "                           ");
    mvprintw(LINES / 2 - 9, COLS / 2 - 50,
             "                            |_||_\\___/\\_/\\_/   \\__\\___/ | .__/_\\__,_|\\_, |"
             "                           ");
    mvprintw(LINES / 2 - 8, COLS / 2 - 50,
             "                                                        |_|          |__/ "
             "                           ");
    mvprintw(LINES / 2 - 7, COLS / 2 - 50,
             "                                                                   "
             "                                  ");
    attroff(COLOR_PAIR(3));
}

void GameEnvironment::escHowToPlay(int key)
{
    key = 0;
    while (key != 10)
    { // spacebar key
        printHowToPlay();
        key = getch();
    }
}

void GameEnvironment::drawRoom(int rightDistance, int bottomDistance, int startX, int startY, bool noEnemy)
{

    refresh();
    clear();
    initscr();
    start_color();

    init_pair(3, COLOR_YELLOW, 232);

    for (int i = startY; i < rightDistance; i++)
    {
        mvprintw(startX, i, "-");
        mvprintw(bottomDistance, i, "-");
    }
    for (int i = startX; i < bottomDistance; i++)
    {
        mvprintw(i, startY, "|");
        mvprintw(i, rightDistance, "|");
    }
    mvprintw(startX, rightDistance, "o");
    mvprintw(startX, startY, "o");
    mvprintw(bottomDistance, startY, "o");
    mvprintw(bottomDistance, rightDistance, "o");
    // COMMANDS TODO
}

void GameEnvironment::drawCharacter(int x, int y, char c){
    move(y, x);
    printw("%c", c);
}

