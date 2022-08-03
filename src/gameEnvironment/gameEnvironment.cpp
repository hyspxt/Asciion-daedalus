#include "gameEnvironment.hpp"

#include <ncurses.h>
#include <iostream>
#include <ctime>
#include <string.h>
#include <unistd.h>

void GameEnvironment::printMenu()
{
    init_pair(1, COLOR_CYAN, 232);
    attron(COLOR_PAIR(1));
    mvprintw(LINES / 2 - 10, COLS / 2 - 54,
             "                                                                   "
             "                                         ");
    mvprintw(LINES / 2 - 9, COLS / 2 - 54,
             "    b    d  P*Y  8b 8 8  d 88888 Yb  dP        A   8**Y  P*Y   "
             "P**b8   b    8     Yb  dP 8**Y .P*Y8 88888   ");
    mvprintw(LINES / 2 - 8, COLS / 2 - 54,
             "    8b  d8 P   Y 8Yb8 8od  8__    YbdP        PY   8__P P   Y P   "
             "`*   PY   8      YbdP  8__P `Yo.* 8__     ");
    mvprintw(LINES / 2 - 7, COLS / 2 - 54,
             "    8Yb P8 b   d 8 Y8 8*Y  8**     8P        P__Y  8**  b   P Y    "
             "   P__Y  8  .o   8P   8**  o.`Y8 8**     ");
    mvprintw(LINES / 2 - 6, COLS / 2 - 54,
             "    8 Y  8  Ybo  8  Y 8  Y 88888  dP        P****Y 8     P*Y   "
             "YoodP P****Y 8ood8  dP    8     8oP* 88888   ");
    mvprintw(LINES / 2 - 5, COLS / 2 - 54,
             "                                                                   "
             "                                         ");
    mvprintw(LINES / 2 - 4, COLS / 2 - 54,
             "     TESING!                    "
             "                                         ");
    mvprintw(LINES / 2 - 3, COLS / 2 - 54,
             "                                                                   "
             "                                         ");
    attroff(COLOR_PAIR(1));
}
