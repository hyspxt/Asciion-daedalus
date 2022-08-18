#include "gameEnvironment.hpp"

#include <ncurses.h>
#include <iostream>
#include <ctime>
#include <string.h>
#include <unistd.h>
#include <cmath>
#include <fstream>
#include <locale.h>

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
             "  PRESS [ENTER] TO CONTINUE       ");
}

void GameEnvironment::printHowToPlay()
{

    int stop = LINES / 2 - 14;
    for (int y = 0; y < 30; y++)
    {
        init_pair(8, COLOR_BLACK, 232);
        attron(COLOR_PAIR(8));
        mvprintw(stop, COLS / 2 - 54,
                 "                                                                 "
                 "                                         ");
        stop++;
        attroff(COLOR_PAIR(8));
    }
    init_pair(3, COLOR_YELLOW, 232);
    attron(COLOR_PAIR(3));
    mvprintw(LINES / 2 - 14, COLS / 2 - 51,
             "                             _  _              _              _           "
             "                           ");
    mvprintw(LINES / 2 - 13, COLS / 2 - 51,
             "                            | || |_____ __ __ | |_ ___   _ __| |__ _ _  _ "
             "                           ");
    mvprintw(LINES / 2 - 12, COLS / 2 - 51,
             "                            | __ / _ \\ V  V / |  _/ _ \\ | '_ \\ / _` | || |"
             "                           ");
    mvprintw(LINES / 2 - 11, COLS / 2 - 51,
             "                            |_||_\\___/\\_/\\_/   \\__\\___/ | .__/_\\__,_|\\_, |"
             "                           ");
    mvprintw(LINES / 2 - 10, COLS / 2 - 51,
             "                                                        |_|          |__/ "
             "                           ");
    attroff(COLOR_PAIR(3));
    
    init_pair(1, COLOR_CYAN, 232);
    attron(COLOR_PAIR(1));
    mvprintw(LINES / 2 - 8, COLS / 2 - 49, "So, a new soul enters the Daedalus, what a rare event!");
    mvprintw(LINES / 2 - 6, COLS / 2 - 49, "I like helping hopeless people like you, so i'll give you some hint to survive a little more here:");
    mvprintw(LINES / 2 - 4, COLS / 2 - 49, "First of all, you can move in the labirinth with [w][a][s][d] keys.");
    mvprintw(LINES / 2 - 3, COLS / 2 - 49, "Use [arrow keys] to shoot in the direction you desire,");
    mvprintw(LINES / 2 - 2, COLS / 2 - 49, "this is mandatory to defeat this place and his inhabitants(E).");
    mvprintw(LINES / 2, COLS / 2 - 49, "Keep attention to the legacies that past adventurers left here: ARTIFACTS and POWERS:");
    mvprintw(LINES / 2 + 1, COLS / 2 - 49, "ARTIFACTS are items that will make you stronger and more resilient. They look like an (A).");
    mvprintw(LINES / 2 + 2, COLS / 2 - 49, "POWERS are less effective, but they can open some doors here. They resemble somehow a (P).");
    mvprintw(LINES / 2 + 3, COLS / 2 - 49, "Rarely, both can appear as (?), thanks to the magic influence of the labirinth.");
    mvprintw(LINES / 2 + 5, COLS / 2 - 49, "To proceed, some doors need to be opened. Some will need a POWER. Some will not. Cool, right?");
    mvprintw(LINES / 2 + 7, COLS / 2 - 49, "It's pretty obvious, but if your lifepoints drop down to 0 and you have no other lives...");
    mvprintw(LINES / 2 + 8, COLS / 2 - 49, "well, hope you understand what I mean.");
    mvprintw(LINES / 2 + 10, COLS / 2 - 49, "That sould be all, I think?");
    mvprintw(LINES / 2 + 11, COLS / 2 - 49, "Oh! In the end, remember to write your name on some wall. The King loves it.");



    attroff(COLOR_PAIR(1));    

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

void GameEnvironment::drawInfo(int rightDistance, int bottomDistance, int startX, int startY, bool noEnemy, Entity entity, int points)
{

    for (int i = rightDistance + 5; i < rightDistance + 30; i++)
    {
        mvprintw(startX, i, "-");
        mvprintw(bottomDistance, i, "-");
    }
    for (int i = startX; i < bottomDistance; i++)
    {
        mvprintw(i, rightDistance + 5, "|");
        mvprintw(i, rightDistance + 30, "|");
    }
    mvprintw(startX, rightDistance + 5, "o");
    mvprintw(startX, rightDistance + 30, "o");
    mvprintw(bottomDistance, rightDistance + 5, "o");
    mvprintw(bottomDistance, rightDistance + 30, "o");

    mvprintw(startX + 1, rightDistance + 6, "Lives: ");
    int hearts = entity.getLifePoints() / 10;

    for (int i = 0; i < hearts; i++)
    {
        move(startX + 1, rightDistance + 13 + i);
        printw("\u2665");
    }
    mvprintw(startX + 2, rightDistance + 6, "Lifepoints: ");
    int actualLp = entity.getLifePoints() - 10 * (hearts - 1);

    init_pair(5, 232, COLOR_CYAN);
    init_pair(6, -1, 232);
    attron(COLOR_PAIR(6));

    for (int i = 0; i < 10; i++)
    {
        mvprintw(startX + 2, rightDistance + 19 + i, " ");
    }
    attroff(COLOR_PAIR(6));
    attron(COLOR_PAIR(5));
    for (int i = 0; i < actualLp; i++)
    {
        mvprintw(startX + 2, rightDistance + 19 + i, " ");
    }
    attroff(COLOR_PAIR(5));
    std::string s = std::to_string(points);
    char const *pchar = s.c_str(); // use char const* as target type

    mvprintw(startX + 4, rightDistance + 6, "Score: ");
    mvprintw(startX + 4, rightDistance + 13, pchar);
}

void GameEnvironment::drawCharacter(int x, int y, char c)
{
    move(y, x);
    printw("%c", c);
}

void GameEnvironment::printScoreboard()
{

    int stop = LINES / 2 - 14;
    for (int y = 0; y < 30; y++)
    {
        init_pair(8, COLOR_BLACK, 232);
        attron(COLOR_PAIR(8));
        mvprintw(stop, COLS / 2 - 54,
                 "                                                                 "
                 "                                         ");
        stop++;
        attroff(COLOR_PAIR(8));
    }
    init_pair(3, COLOR_YELLOW, 232);
    attron(COLOR_PAIR(3));

    mvprintw(
        LINES / 2 - 14, COLS / 2 - 29,
        "                              __                         __");
    mvprintw(
        LINES / 2 - 13, COLS / 2 - 29,
        "   ______________  ________  / /_  ____  ____ __________/ /");
    mvprintw(
        LINES / 2 - 12, COLS / 2 - 29,
        "  / ___/ ___/ __ \\/ ___/ _ \\/ __ \\/ __ \\/ __ `/ ___/ __  / ");
    mvprintw(
        LINES / 2 - 11, COLS / 2 - 29,
        " (__  ) /__/ /_/ / /  /  __/ /_/ / /_/ / /_/ / /  / /_/ /  ");
    mvprintw(
        LINES / 2 - 10, COLS / 2 - 29,
        "/____/\\___/\\____/_/   \\___/_.___/\\____/\\__,_/_/   \\__,_/   ");

    mvprintw(LINES / 2 - 8, COLS / 2 - 46,
             "---------------------------------------------------------------"
             "-------------------------");

    mvprintw(LINES / 2 + 13, COLS / 2 - 14, "Press [ENTER] to continue");
    attroff(COLOR_PAIR(3));

    std::ifstream scoreboard("scoreboard.txt");
    std::string line;

    if (scoreboard.is_open())
    {
        int i = LINES / 2 - 6;
        int nameChar = 0, column = 0;
        init_pair(4, COLOR_WHITE, COLOR_BLACK);
        attron(COLOR_PAIR(4));
        while (column < 4)
        {
            nameChar = 0;
            while ((nameChar <= 10) && (getline(scoreboard, line)))
            {
                mvprintw(i, COLS / 2 - 46 + (column * 25), "%s", line.c_str());
                i += 2;
                nameChar++;
            }
            column++;
        }
        attroff(COLOR_PAIR(4));
        scoreboard.close();
    }
}

void GameEnvironment::escScoreboard(int key)
{
    key = 0;
    while (key != 10)
    {
        printScoreboard();
        key = getch();
    }
}

void GameEnvironment::printLoss(int score)
{
    int stop = LINES / 2 - 14;
    for (int y = 0; y < 20; y++)
    {
        init_pair(8, COLOR_BLACK, 232);
        attron(COLOR_PAIR(8));
        mvprintw(stop, COLS / 2 - 54,
                 "                                                                 "
                 "                                         ");
        stop++;
        attroff(COLOR_PAIR(8));
    }
    init_pair(8, COLOR_RED, 232);
    attron(COLOR_PAIR(8));
    mvprintw(
        LINES / 2 - 14, COLS / 2 - 21,
        " __   __                _ _          _ ");
    mvprintw(
        LINES / 2 - 13, COLS / 2 - 21,
        " \\ \\ / /__  _   _    __| (_) ___  __| |");
    mvprintw(
        LINES / 2 - 12, COLS / 2 - 21,
        "  \\ V / _ \\| | | |  / _` | |/ _ \\/ _` |");
    mvprintw(
        LINES / 2 - 11, COLS / 2 - 21,
        "   | | (_) | |_| | | (_| | |  __/ (_| |");
    mvprintw(
        LINES / 2 - 10, COLS / 2 - 21,
        "   |_|\\___/ \\__,_|  \\__,_|_|\\___|\\__,_|");
    attroff(COLOR_PAIR(8));

    init_pair(9, COLOR_CYAN, 232);
    init_pair(10, COLOR_GREEN, 232);

    attron(COLOR_PAIR(9));
    mvprintw(LINES / 2 - 8, COLS / 2 - 29, "So, in the End, you've meet you're FATE, uh...?");
    mvprintw(LINES / 2 - 7, COLS / 2 - 29, "The DAEDALUS is pretty harsh, but do not fear");
    mvprintw(LINES / 2 - 6, COLS / 2 - 29, "SOMEONE, or maybe something, will take this challenge again,");
    mvprintw(LINES / 2 - 5, COLS / 2 - 29, "SOONER or LATER...");
    attroff(COLOR_PAIR(9));

    attron(COLOR_PAIR(10));
    mvprintw(LINES / 2 - 1, COLS / 2 - 8, "Your score: %i", score);
    attroff(COLOR_PAIR(10));

    attron(COLOR_PAIR(9));
    mvprintw(LINES / 2, COLS / 2 - 14, "Brand your name & Exit [ENTER]");
    mvprintw(LINES / 2 + 1, COLS / 2 - 29, "(or let this score fade in the Daedalus, inserting no name)");
    attroff(COLOR_PAIR(9));
}

void GameEnvironment::escLoss(int key, int score)
{
    key = 0;
    char name[10] = {'\0'};
    char name2[10] = {'\0'};

    init_pair(7, COLOR_YELLOW, 232);

    while (key != 10)
    {
        printLoss(score);
        strcat(name, name2);

        attron(COLOR_PAIR(7));

        attron(COLOR_PAIR(7));
        mvprintw(LINES / 2 + 3, COLS / 2 - 1, "___________");
        mvprintw(LINES / 2 + 3, COLS / 2 - 14, "Insert name: %s ", name);
        attroff(COLOR_PAIR(7));

        refresh();
        key = getnstr(name2, 1);
        if (!strcmp(name2, "\0"))
            key = 10;
    }
    save(name, score); // Save here the play
}

void GameEnvironment::save(char saveName[], int score)
{
    bool flag = nameCheck(saveName);
    int len = strlen(saveName), maxLen = 12;
    std::fstream scoreboard;
    scoreboard.open("scoreboard.txt", std::ios::app);
    if (scoreboard && score > 0 && !flag)
    {
        scoreboard << saveName << ":";
        while (len < maxLen)
        {
            scoreboard << " ";
            len++;
        }
        scoreboard << score << "\n";
    }

    scoreboard.close();
}

bool GameEnvironment::nameCheck(char saveName[])
{
    bool flag = true;
    for (int i = 0; i < 10; i++)
    {
        flag &= ((saveName[i] == ' ') || (saveName[i] == '\0'));
    }
    return flag;
}

void GameEnvironment::drawEnemies(GameEnvironment gameEnvironment, p_EnemyList h_enemyList)
{
    while (h_enemyList != NULL)
    {
        gameEnvironment.drawCharacter(h_enemyList->enemy.getX(), h_enemyList->enemy.getY(), h_enemyList->enemy.getSkin());
        h_enemyList = h_enemyList->next;
    }
}
