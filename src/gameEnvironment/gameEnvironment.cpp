#include "gameEnvironment.hpp"

#include <ncurses.h>
#include <iostream>
#include <ctime>
#include <string.h>
#include <unistd.h>
#include <cmath>
#include <fstream>
#include <locale.h>
#include <tuple>

#define ROOM_OFFSET 14 // Room height
#define LEFT_DISTANCE 22
#define RIGHT_DISTANCE 71
#define TOP_DISTANCE 7
#define BOTTOM_DISTANCE 20
#define START_X 7
#define START_Y 22

GameEnvironment::GameEnvironment(){};
void GameEnvironment::printMenuLogo()
{
    /*
    This function print the title logo on the first window in game.
    */
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
{
    /*
    Draw buttons (and colored hover button) in the logo window.
    Each button lead to a different option of the game (Quit option included).
    */

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
             "           THE LORE          ");
    mvprintw(LINES / 2 + 9, COLS / 2 - 17,
             "                             ");

    mvprintw(LINES / 2 + 10, COLS / 2 - 17,
             "                             ");
    mvprintw(LINES / 2 + 11, COLS / 2 - 17,
             "             QUIT            ");
    mvprintw(LINES / 2 + 12, COLS / 2 - 17,
             "                             ");

    // This switch draw the selected / active button
    switch (choice)
    {
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
                 "           THE LORE          ");
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

    /*
    This function draws the HtP screen.
    Things like controls, gamemodes, user guide are written here.
    (BUT NON DEFINED).
    */
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
    mvprintw(LINES / 2 - 14, COLS / 2 - 52,
             "                             _  _              _              _           "
             "                           ");
    mvprintw(LINES / 2 - 13, COLS / 2 - 52,
             "                            | || |_____ __ __ | |_ ___   _ __| |__ _ _  _ "
             "                           ");
    mvprintw(LINES / 2 - 12, COLS / 2 - 52,
             "                            | __ / _ \\ V  V / |  _/ _ \\ | '_ \\ / _` | || |"
             "                           ");
    mvprintw(LINES / 2 - 11, COLS / 2 - 52,
             "                            |_||_\\___/\\_/\\_/   \\__\\___/ | .__/_\\__,_|\\_, |"
             "                           ");
    mvprintw(LINES / 2 - 10, COLS / 2 - 52,
             "                                                        |_|          |__/ "
             "                           ");
    attroff(COLOR_PAIR(3));

    init_pair(1, COLOR_CYAN, 232);
    attron(COLOR_PAIR(1));
    mvprintw(LINES / 2 - 8, COLS / 2 - 49, "So, a new soul enters the Daedalus, what a rare event!");
    mvprintw(LINES / 2 - 6, COLS / 2 - 49, "I like helping hopeless people like you, so I'll give you some hints to survive a little more here:");
    mvprintw(LINES / 2 - 4, COLS / 2 - 49, "First of all, you can move in the labirinth with [w][a][s][d] keys.");
    mvprintw(LINES / 2 - 3, COLS / 2 - 49, "Use [arrow keys] to shoot in the direction you desire,");
    mvprintw(LINES / 2 - 2, COLS / 2 - 49, "this is mandatory to defeat this place and his inhabitants (very evil folks).");
    mvprintw(LINES / 2, COLS / 2 - 49, "Keep attention to the legacies past adventurers left here: ARTIFACTS and POWERS:");
    mvprintw(LINES / 2 + 1, COLS / 2 - 49, "ARTIFACTS are items that will make you stronger and more resilient. They look like an (A).");
    mvprintw(LINES / 2 + 2, COLS / 2 - 49, "POWERS are less effective, but they can open some doors here. They resemble somehow a (K).");
    mvprintw(LINES / 2 + 3, COLS / 2 - 49, "Rarely, both can appear as (?), thanks to the magic influence of the labirinth.");
    mvprintw(LINES / 2 + 5, COLS / 2 - 49, "To proceed, some doors need to be opened with [r] key. Cool, right?");
    mvprintw(LINES / 2 + 7, COLS / 2 - 49, "It's pretty obvious, but if your lifepoints drop down to 0 and you have no other lives...");
    mvprintw(LINES / 2 + 8, COLS / 2 - 49, "well, hope you understand what I mean.");
    mvprintw(LINES / 2 + 10, COLS / 2 - 49, "That sould be all, I think?");
    mvprintw(LINES / 2 + 11, COLS / 2 - 49, "Oh! In the end, remember to write your name on some wall. The King LOVES it.");
    attroff(COLOR_PAIR(1));

    attron(COLOR_PAIR(3));
    mvprintw(LINES / 2 + 13, COLS / 2 - 15, "Press [ENTER] to continue");
    attron(COLOR_PAIR(3));
}

void GameEnvironment::escHowToPlay(int key)
{
    key = 0;
    while (key != 10) // 10 = getch() chtype of ENTER key
    {
        printHowToPlay();
        key = getch();
    }
}

void GameEnvironment::escLore(int key)
{
    key = 0;
    while (key != 10)
    {
        printLore();
        key = getch();
    }
}

void GameEnvironment::printLore()
{
    // This function draws the Lore screen.

    int stop = LINES / 2 - 13;
    for (int y = 0; y < 23; y++)
    {
        init_pair(8, COLOR_BLACK, 232);
        attron(COLOR_PAIR(8));
        mvprintw(stop, COLS / 2 - 54,
                 "                                                                 "
                 "                                         ");
        stop++;
        attroff(COLOR_PAIR(8));
    }

    init_pair(1, COLOR_CYAN, 232);
    attron(COLOR_PAIR(1));
    mvprintw(LINES / 2 - 8, COLS / 2 - 49, "The evil king ASCIION for some unknown reasons, captured and imprisoned you");
    mvprintw(LINES / 2 - 7, COLS / 2 - 49, "in his dangerous labyrinth: THE DAEDALUS. According to the kingdom bards,");
    mvprintw(LINES / 2 - 6, COLS / 2 - 49, "the king's hobby is to recreate WILD animals in an ascii-art version: ");
    mvprintw(LINES / 2 - 5, COLS / 2 - 49, "the Deadalus contains all his works.");

    mvprintw(LINES / 2 - 3, COLS / 2 - 49, "To keep the kindom safe from these strange creatures,");
    mvprintw(LINES / 2 - 2, COLS / 2 - 49, "the labyinth was made to be completely UNESCAPABLE.");
    mvprintw(LINES / 2 - 1, COLS / 2 - 49, "Your end is near, but since we're here you'll want to");
    mvprintw(LINES / 2, COLS / 2 - 49, "at least become the STRONGEST in the Deadalus, right? ");
    mvprintw(LINES / 2 + 1, COLS / 2 - 49, "Then take your weapons and make HIS labyrinth YOUR labyrinth!");

    mvprintw(LINES / 2 + 3, COLS / 2 - 49, "...");
    attroff(COLOR_PAIR(1));

    init_pair(3, COLOR_YELLOW, 232);
    attron(COLOR_PAIR(3));
    mvprintw(LINES / 2 + 6, COLS / 2 - 14, "Press [ENTER] to continue");
    attron(COLOR_PAIR(3));
}

void GameEnvironment::drawRoom(int bottomDistance, int startX, int startY, bool noEnemy, int lineCounter)
{

    /*
    This function draws the room based on lines in .../assets/map.txt
    Each line is drawn one per time.
    The offset for every room = 14 -> 'cause room_height = 14;
    */

    std::string s;
    for (int i = startX; i <= bottomDistance; i++)
    {
        s = readNthLine(lineCounter);
        mvprintw(i, startY, "%s", s.c_str());
        lineCounter++;
    }
}

void GameEnvironment::clearInfo(int rightDistance, int bottomDistance, int startX, int startY)
{

    /*
    This function serves to refresh the Info window.
    (clear and then write info updated, quite basic).
    */

    for (int i = startX; i < bottomDistance; i++)
    {
        for (int j = rightDistance + 5; j < rightDistance + 32; j++)
        {
            mvprintw(i, j, " ");
        }
    }
}

void GameEnvironment::drawInfo(int rightDistance, int bottomDistance, int startX, int startY, bool noEnemy, Entity entity, int points, int keyCounter, int hearts, p_EnemyList h_enemyList)
{

    /*
    This function print the infoBox and information after it has been cleared.
    This contains Player Stats (LP, Lives,Damage, etc) and RoomInfo (enemies remaining).
    */

    // Clear the box
    clearInfo(rightDistance, bottomDistance, startX, startY);

    // Draw borders
    for (int i = rightDistance + 5; i < rightDistance + 32; i++)
    {
        mvprintw(startX, i, "-");
        mvprintw(bottomDistance, i, "-");
    }
    for (int i = startX; i < bottomDistance; i++)
    {
        mvprintw(i, rightDistance + 5, "|");
        mvprintw(i, rightDistance + 32, "|");
    }
    // Corners
    mvprintw(startX, rightDistance + 5, "+");
    mvprintw(startX, rightDistance + 32, "+");
    mvprintw(bottomDistance, rightDistance + 5, "+");
    mvprintw(bottomDistance, rightDistance + 32, "+");

    // Draw Stats
    mvprintw(startX + 1, rightDistance + 6, "Lives: ");
    for (int i = 0; i < hearts; i++)
    {
        move(startX + 1, rightDistance + 13 + i);
        printw("\u2665");
    }

    init_pair(5, 232, COLOR_CYAN);
    init_pair(6, -1, 232);
    init_pair(7, 232, COLOR_YELLOW);
    init_pair(8, 232, COLOR_RED);

    mvprintw(startX + 2, rightDistance + 6, "Lifepoints: ");
    int actualLp = entity.getCurrentLifePoints();

    // Draw the colored lifebar based on how much LP player has (currently, not max).

    attron(COLOR_PAIR(6)); // Draw the black bar behind the colored one
    for (int i = 0; i < 10; i++)
    {
        mvprintw(startX + 2, rightDistance + 19 + i, " ");
    }
    attroff(COLOR_PAIR(6));

    if (actualLp >= 6) // Cyan bar
    {
        if (actualLp > 10)
        {
            actualLp = 10;
        }
        attron(COLOR_PAIR(5));
        for (int i = 0; i < actualLp; i++)
        {
            mvprintw(startX + 2, rightDistance + 19 + i, " ");
        }
        attroff(COLOR_PAIR(5));
    }
    else if (actualLp < 6 && actualLp >= 3) // Yellow bar
    {
        attron(COLOR_PAIR(7));
        for (int i = 0; i < actualLp; i++)
        {
            mvprintw(startX + 2, rightDistance + 19 + i, " ");
        }
        attroff(COLOR_PAIR(7));
    }
    else if (actualLp < 3) // Red bar
    {
        attron(COLOR_PAIR(8));
        for (int i = 0; i < actualLp; i++)
        {
            mvprintw(startX + 2, rightDistance + 19 + i, " ");
        }
        attroff(COLOR_PAIR(8));
    }

    std::string s = std::to_string(points);
    char const *pchar = s.c_str();
    mvprintw(startX + 5, rightDistance + 6, "Score: ");
    mvprintw(startX + 5, rightDistance + 13, pchar);

    mvprintw(startX + 3, rightDistance + 21, "%i", entity.getCurrentLifePoints());
    mvprintw(startX + 3, rightDistance + 23, "%s", "/");
    mvprintw(startX + 3, rightDistance + 25, "%i", entity.getLifePoints());

    if (actualLp > 10) // Draw the "shield" bar -> currentLP > LP
    {
        attron(COLOR_PAIR(7));
        mvprintw(startX + 2, rightDistance + 29, " ");
        attroff(COLOR_PAIR(7));
    }
    else
        mvprintw(startX + 2, rightDistance + 29, " ");

    mvprintw(startX + 7, rightDistance + 6, "Keys: ");
    mvprintw(startX + 7, rightDistance + 18, "%i", keyCounter);

    mvprintw(startX + 8, rightDistance + 6, "Damage: ");
    mvprintw(startX + 8, rightDistance + 18, "%i", entity.getRWeapon().getDamage());

    mvprintw(startX + 9, rightDistance + 6, "Weapon: ");
    if (entity.getRWeapon().getDamage() < 15)
        mvprintw(startX + 9, rightDistance + 14, "Basic Weapon");
    else if (entity.getRWeapon().getDamage() >= 15 && entity.getRWeapon().getDamage() < 23)
        mvprintw(startX + 9, rightDistance + 14, "Advanced Weapon");
    else
        mvprintw(startX + 9, rightDistance + 14, "Ultima Weapon");

    // Prints how many enemies remain to defeat to clear the current room
    int enemyLeft = lenghtEnemyList(h_enemyList);
    if (enemyLeft > 0)
    {
        mvprintw(startX + 11, rightDistance + 6, "                        ");
        mvprintw(startX + 11, rightDistance + 6, "Enemy left: ");
        mvprintw(startX + 11, rightDistance + 18, "%i", enemyLeft);
    }
    else
    {
        mvprintw(startX + 11, rightDistance + 6, "                        ");
        mvprintw(startX + 11, rightDistance + 6, "Room cleared!");
    }
}

void GameEnvironment::drawCharacter(int x, int y, char c)
{
    /*
    This function print a single character in a position determined by the cursor.
    Useful and used in many other functions (see for example movements).
    */
    move(y, x);
    printw("%c", c);
}

void GameEnvironment::printScoreboard()
{

    /*
    This function print the scoreboard based on the scoreboard.txt file.
    The leaderboard is made with the top 9 scores.
    */

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

    std::string line;
    int i = 0;
    for (int nameChar = 0; nameChar < 9; nameChar++)
    {
        line = readScoreboard(nameChar);
        mvprintw(LINES / 2 - 6 + i, COLS / 2 - 46, "%s", line.c_str());
        i += 2;
    }
}

std::string GameEnvironment::readScoreboard(int n)
{
    /*
    This function reads the Nth line of scoreboard.txt.
    */
    std::ifstream sb("scoreboard.txt");
    std::string s;

    s.reserve(22); // Prior to boost performance a little

    // Skip N lines
    for (int i = 0; i < n; ++i)
        std::getline(sb, s);

    // Read N+1 line
    std::getline(sb, s);
    return s;
}

void GameEnvironment::escScoreboard(int key)
{
    key = 0;
    while (key != 10)
    {
        printScoreboard();
        // in case of error put refresh here
        key = getch();
        refresh();
    }
}

void GameEnvironment::printLoss(int score)
{

    /*
    When the player dies, print this screen.
    */

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
    mvprintw(LINES / 2 - 8, COLS / 2 - 29, "So, in the End, you've meet your FATE, uh...?");
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

    /*
    This function save in scoreboard.txt name and score.
    */

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
    save(name, score); // Save here the play in scoreboard.txt
}

void GameEnvironment::escWin(int key, int score)
{

    /*
    This function save in scoreboard.txt name and score.
    */

    key = 0;
    char name[10] = {'\0'};
    char name2[10] = {'\0'};

    init_pair(7, COLOR_YELLOW, 232);
    while (key != 10)
    {
        printWin(score);
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
    save(name, score); // Save here the play in scoreboard.txt
}

void GameEnvironment::printWin(int score)
{

    /*
    This function print this screen when the player escapes the Deadalus.
    Only possible in Room n.17.
    */

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

    init_pair(11, COLOR_BLUE, 232);
    attron(COLOR_PAIR(11));
    mvprintw(
        LINES / 2 - 14, COLS / 2 - 35,
        " ___ ___                                                         __ __ ");
    mvprintw(
        LINES / 2 - 13, COLS / 2 - 35,
        "|   |   |.-----.--.--.    .-----.-----.----.---.-.-----.-----.--|  |  |");
    mvprintw(
        LINES / 2 - 12, COLS / 2 - 35,
        " \\     / |  _  |  |  |    |  -__|__ --|  __|  _  |  _  |  -__|  _  |__|");
    mvprintw(
        LINES / 2 - 11, COLS / 2 - 35,
        "  |___|  |_____|_____|    |_____|_____|____|___._|   __|_____|_____|__|");
    mvprintw(
        LINES / 2 - 10, COLS / 2 - 35,
        "                                                 |__|                  ");
    attroff(COLOR_PAIR(11));

    init_pair(9, COLOR_CYAN, 232);
    init_pair(10, COLOR_GREEN, 232);

    attron(COLOR_PAIR(9));
    mvprintw(LINES / 2 - 8, COLS / 2 - 37, "Unbelievable...! You actually managed to ESCAPE this labirynth!");
    mvprintw(LINES / 2 - 7, COLS / 2 - 37, "At least for now... *laughs disturbingly");
    mvprintw(LINES / 2 - 6, COLS / 2 - 37, "What do I mean by that? You're CURSED from the moment you entered this place.");
    mvprintw(LINES / 2 - 5, COLS / 2 - 37, "You will come back, again and again, proving yourself in the DAEDALUS.");
    mvprintw(LINES / 2 - 4, COLS / 2 - 37, "Try breaking it if you would, for that is OUR curse.");
    attroff(COLOR_PAIR(9));

    attron(COLOR_PAIR(10));
    mvprintw(LINES / 2 - 1, COLS / 2 - 8, "Your score: %i", score);
    attroff(COLOR_PAIR(10));

    attron(COLOR_PAIR(9));
    mvprintw(LINES / 2, COLS / 2 - 14, "Brand your name & Exit [ENTER]");
    mvprintw(LINES / 2 + 1, COLS / 2 - 29, "(or let this score fade in the Daedalus, inserting no name)");
    attroff(COLOR_PAIR(9));
}

void GameEnvironment::save(char saveName[], int score)
{

    /*
    After a Win / Lose, this function saves name and score in
    scoreboard.txt.
    */

    bool flag = nameCheck(saveName);
    int len = strlen(saveName), maxLen = 12;
    std::fstream scoreboard;
    scoreboard.open("scoreboard.txt", std::ios::app);
    if (scoreboard && score > 0 && !flag)
    {
        scoreboard << saveName;
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
    /*
    This function check if the name in input respects costraints before being saved.
    */
    bool flag = true;
    for (int i = 0; i < 10; i++)
    {
        flag &= ((saveName[i] == ' ') || (saveName[i] == '\0'));
    }
    return flag;
}

void GameEnvironment::drawEnemies(GameEnvironment gameEnvironment, p_EnemyList h_enemyList)
{
    /*
    Draw all enemies in the list in thei respective positions with cursor (based on x and y).
    */
    while (h_enemyList != NULL)
    {
        if (h_enemyList->enemy.getLifePoints() != h_enemyList->enemy.getCurrentLifePoints())
        {
            init_pair(3, COLOR_RED, -1);
            attron(COLOR_PAIR(3));
            gameEnvironment.drawCharacter(h_enemyList->enemy.getX(), h_enemyList->enemy.getY(), h_enemyList->enemy.getSkin());
            attroff(COLOR_PAIR(3));
        }
        else
            gameEnvironment.drawCharacter(h_enemyList->enemy.getX(), h_enemyList->enemy.getY(), h_enemyList->enemy.getSkin());
        h_enemyList = h_enemyList->next;
    }
}

std::string GameEnvironment::readNthLine(int n)
{

    /*
    This function read and return as a string the Nth line of map.txt,
    that contains all maps (rooms) -> offset between Room 0 and Room 1 = 14
    Ex. N = 0 means the first line of the first room
        N = 14 means the first line of the second room
        N = 15 meand the second line of the second room
        ...
    */

    std::ifstream map("assets/map.txt");
    std::string s;

    s.reserve(22); // Prior to boost performance a little

    // skip N lines
    for (int i = 0; i < n; ++i)
        std::getline(map, s);

    std::getline(map, s);
    return s;
}

p_Room GameEnvironment::saveRoomState(p_itemList h_itemList, p_Room h_roomList, int roomTracker)
{

    // Actually not used, but it should modify the state of the room.

    p_Room tmpHead = new Room;
    tmpHead->down = h_roomList->down;
    tmpHead->up = h_roomList->up;
    tmpHead->left = h_roomList->left;
    tmpHead->right = h_roomList->right;
    tmpHead->itemList = h_itemList;
    tmpHead->roomTracker = roomTracker;
    return tmpHead;
}

p_Room GameEnvironment::mapGenerator(p_Room h_roomList)
{

    /*
    This function create the logical structure of the various Rooms.
    This is mandatory to do almost everything related to roomChange.
    RoomTracker is meant to reprent the id of the Room (determined by position in map.txt)
    and it has to be evaluated considering the offset constant (14).

    The pointers represents the four direction where it can be another Room accessible through door, or not.
    Ex. map[0] is the first room in the file. It has only a Door placed up-> that leads to map[1].
    When a pointer point NULL, it means there are no Door (and so no Room) in that direction.
    */

    p_Room map[17];
    for (int i = 0; i < 17; i++)
    {
        map[i] = new Room;
        map[i]->roomTracker = i * ROOM_OFFSET;
    }

    map[0]->up = map[1];
    map[0]->down = NULL;
    map[0]->right = NULL;
    map[0]->left = NULL;

    map[1]->up = map[12];
    map[1]->down = map[0];
    map[1]->right = map[2];
    map[1]->left = map[8];

    map[2]->up = map[3];
    map[2]->down = NULL;
    map[2]->right = map[4];
    map[2]->left = map[1];

    map[3]->up = NULL;
    map[3]->down = map[2];
    map[3]->right = map[5];
    map[3]->left = NULL;

    map[4]->up = map[5];
    map[4]->down = map[7];
    map[4]->right = NULL;
    map[4]->left = map[2];

    map[5]->up = map[6];
    map[5]->down = map[4];
    map[5]->right = NULL;
    map[5]->left = map[3];

    map[6]->up = NULL;
    map[6]->down = map[5];
    map[6]->right = NULL;
    map[6]->left = NULL;

    map[7]->up = map[4];
    map[7]->down = NULL;
    map[7]->right = NULL;
    map[7]->left = NULL;

    map[8]->up = map[10];
    map[8]->down = map[9];
    map[8]->right = map[1];
    map[8]->left = NULL;

    map[9]->up = map[8];
    map[9]->down = NULL;
    map[9]->right = NULL;
    map[9]->left = NULL;

    map[10]->up = NULL;
    map[10]->down = map[9];
    map[10]->right = NULL;
    map[10]->left = map[11];

    map[11]->up = NULL;
    map[11]->down = NULL;
    map[11]->right = map[10];
    map[11]->left = NULL;

    map[12]->up = map[13];
    map[12]->down = map[1];
    map[12]->right = NULL;
    map[12]->left = NULL;

    map[13]->up = NULL;
    map[13]->down = map[12];
    map[13]->right = map[14];
    map[13]->left = map[15];

    map[14]->up = NULL;
    map[14]->down = NULL;
    map[14]->right = NULL;
    map[14]->left = map[13];

    map[15]->up = map[16];
    map[15]->down = NULL;
    map[15]->right = map[13];
    map[15]->left = NULL;

    map[16]->up = NULL;
    map[16]->down = map[15];
    map[16]->right = NULL;
    map[16]->left = NULL;

    return (map[0]);
}

std::tuple<p_Room, int> GameEnvironment::roomChange(Entity &entity, p_EnemyList &h_enemyList, p_Room h_roomList, p_itemList h_itemList,
                                                    int bottomDistance, int rightDistance, int startX, int startY, bool noEnemy,
                                                    int points, int enemyCounter, bool passRooms[])
/*
 This function handle the events that happen when the player pass through a Door, changing Room.
*/

{
    if (entity.getX() >= RIGHT_DISTANCE) // Right Door
    {
        entity.setX(LEFT_DISTANCE + 1);
        h_roomList = h_roomList->right;
    }
    if (entity.getX() <= LEFT_DISTANCE) // Left Door
    {
        entity.setX(RIGHT_DISTANCE - 1);
        h_roomList = h_roomList->left;
    }
    if (entity.getY() <= TOP_DISTANCE) // Up Door
    {
        if (h_roomList->roomTracker / ROOM_OFFSET == 16) // if it is the last Room, the player win
        {
            clear();
            escWin(11, points);

            refresh();
            clear();
            endwin();
            std::cout << "Thank you for playing! Hope you enjoyed this game!" << std::endl;
            exit(1);
        }
        else
        {
            entity.setY(BOTTOM_DISTANCE - 1);
            h_roomList = h_roomList->up;
        }
    }
    if (entity.getY() >= BOTTOM_DISTANCE) // Down Door
    {
        entity.setY(TOP_DISTANCE + 1);
        h_roomList = h_roomList->down;
    }

    int itemCounter = 1;
    // Determine how many Items should spawn in the Room
    if ((h_roomList->roomTracker) / ROOM_OFFSET <= 1 || (h_roomList->roomTracker) / ROOM_OFFSET == 16)
        itemCounter = 0;
    else
    {
        srand(time(0));
        itemCounter = rand() % 2 + 2;
    }

    // This array block some generations more than once per Room, once per game
    if (!passRooms[h_roomList->roomTracker / ROOM_OFFSET])
    {
        h_roomList->itemList = generateItem(itemCounter, h_itemList);
        calculateEnemyNumber(h_roomList->roomTracker, enemyCounter);
        passRooms[h_roomList->roomTracker / ROOM_OFFSET] = true;
    }
    return std::make_tuple(h_roomList, enemyCounter);
}

void GameEnvironment::drawItems(p_itemList h_itemList)
{

    /*
    This function print all items in the list based on their position.
    */

    while (h_itemList != NULL)
    {
        drawCharacter(h_itemList->item.getX(), h_itemList->item.getY(), h_itemList->item.getSkin());
        h_itemList = h_itemList->next;
    }
}

int GameEnvironment::lenghtItemList(p_itemList h_itemList)
{

    /*
    Returns the number of items in the current Room.
    */

    int i = 0;
    while (h_itemList != NULL)
    {
        i += 1;
        h_itemList = h_itemList->next;
    }
    return (i);
}

void GameEnvironment::moveEnemies(p_EnemyList h_enemyList)
{

    /*
    Move all enemies in the list randomly.
    Keep in mind that shooting != movement.
    */

    srand(unsigned(time(0)));
    while (h_enemyList != NULL)
    {
        int enemyDirection = rand() % 9;

        switch (enemyDirection)
        {
        case 0: // Move up
            if (mvinch(h_enemyList->enemy.getY() - 1, h_enemyList->enemy.getX()) == ' ')
            {
                mvprintw(h_enemyList->enemy.getY(), h_enemyList->enemy.getX(), " ");
                h_enemyList->enemy.dirUp();
            }
            break;
        case 1: // Move down
            if (mvinch(h_enemyList->enemy.getY() + 1, h_enemyList->enemy.getX()) == ' ')
            {
                mvprintw(h_enemyList->enemy.getY(), h_enemyList->enemy.getX(), " ");
                h_enemyList->enemy.dirDown();
            }
            break; // Move left
        case 2:
            if (mvinch(h_enemyList->enemy.getY(), h_enemyList->enemy.getX() - 1) == ' ')
            {
                mvprintw(h_enemyList->enemy.getY(), h_enemyList->enemy.getX(), " ");
                h_enemyList->enemy.dirLeft();
            }
            break;
        case 3: // Move right
            if (mvinch(h_enemyList->enemy.getY(), h_enemyList->enemy.getX() + 1) == ' ')
            {
                mvprintw(h_enemyList->enemy.getY(), h_enemyList->enemy.getX(), " ");
                h_enemyList->enemy.dirRight();
            }
            break;
        case 4:
            // Do nothing
            break;
        case 5:
            break;
        case 6:
            // Do nothing
            break;
        case 7:
            break;
        case 8:
            break;
        }
        h_enemyList = h_enemyList->next;
    }
}

void GameEnvironment::openAllDoors(int rightDistance, int bottomDistance, int startX, int startY, int lineCounter)
{
    /*
    This function open all doors that are not locked by a key when the Room is cleared.
    The check is done by map.txt.
    */

    std::string map1, map2;
    bool flag1 = true, flag2 = true;
    int j = 0;

    map1 = readNthLine(lineCounter + 13);
    map2 = readNthLine(lineCounter);
    const char *cmap1 = map1.c_str();
    const char *cmap2 = map2.c_str();

    for (int i = startY; i <= rightDistance; i++) // Horizontal
    {
        if (cmap1[j] != signed(mvinch(bottomDistance, i)))
            flag1 = false;
        if (cmap2[j] != signed(mvinch(startX, i)))
            flag2 = false;
        j++;
    }
    if (!flag1)
    {
        for (int i = startY; i < rightDistance; i++)
        {
            if (mvinch(bottomDistance, i) == 'X')
                mvprintw(bottomDistance, i, " ");
        }
    }
    if (!flag2)
    {
        for (int i = startY; i < rightDistance; i++)
        {

            if (mvinch(startX, i) == 'X')
                mvprintw(startX, i, " ");
        }
    }

    flag1 = true;
    flag2 = true;

    j = 0; // Vertical
    for (int i = startX; i <= bottomDistance; i++)
    {
        map1 = readNthLine(lineCounter + j);
        cmap1 = map1.c_str();
        // 49th is the last char of the string
        if (cmap1[0] != signed(mvinch(i, startY)))
        {
            flag1 = false;
        }
        if (cmap1[49] != signed(mvinch(i, rightDistance)))
        {
            flag2 = false;
        }
        j++;
    }

    if (!flag1)
    {
        for (int i = startX; i < bottomDistance; i++)
        {
            if (mvinch(i, startY) == 'X')
                mvprintw(i, startY, " ");
        }
    }
    if (!flag2)
    {
        for (int i = startX; i < bottomDistance; i++)
        {
            if (mvinch(i, rightDistance) == 'X')
                mvprintw(i, rightDistance, " ");
        }
    }
}

int GameEnvironment::lenghtEnemyList(p_EnemyList h_enemyList)
{

    /*
    Returns the number of enemies in the current Room.
    */

    int i = 0;
    while (h_enemyList != NULL)
    {
        if (h_enemyList->enemy.getSkin() != ' ')
        {
            i += 1;
        }
        h_enemyList = h_enemyList->next;
    }
    return (i);
}

p_itemList GameEnvironment::generateItem(int itemCounter, p_itemList h_itemList)
{

    /*
    Handle the item generation in the Room when is entered,
    determines the type of item that is generated (A, K or ?)
    and its effect (based on id, but not applied here!).
    */

    srand(time(0));
    p_itemList tmpItem = NULL;
    int skinTracker, idTracker, prevItemId = 15;
    char skin;
    while (itemCounter > 0)
    {
        tmpItem = new itemList;
        tmpItem->item.setX(randomCoordinate(39, 68).x);
        tmpItem->item.setY(randomCoordinate(9, 19).y);

        while (!checkItemPosition(h_itemList, tmpItem))
        {
            tmpItem->item.setX(randomCoordinate(39, 68).x);
            tmpItem->item.setY(randomCoordinate(9, 19).y);
        }

        skinTracker = rand() % 3;

        switch (skinTracker)
        {
        case 0:
            skin = 'A';
            idTracker = rand() % 7;
            while (idTracker == prevItemId)
                idTracker = rand() % 7;
            prevItemId = idTracker;
            break;
        case 1:
            skin = 'K';
            idTracker = (rand() % 7) + 7;
            while (idTracker == prevItemId)
                idTracker = (rand() % 7) + 7;
            prevItemId = idTracker;
            break;
        case 2:
            skin = '?';
            idTracker = rand() % 14;
            while (idTracker == prevItemId)
                idTracker = rand() % 14;
            prevItemId = idTracker;
            break;
        }
        tmpItem->item.setSkin(skin);
        tmpItem->item.setId(idTracker);

        if (idTracker < 7)
            tmpItem->item.setIsArtifact(true);
        else
            tmpItem->item.setIsArtifact(false);

        switch (idTracker)
        {
        case 0:
            tmpItem->item.setItemName((char *)"Ruby Necklace");
            break;
        case 1:
            tmpItem->item.setItemName((char *)"Sapphire Ring");
            break;
        case 2:
            tmpItem->item.setItemName((char *)"Amethyst Bracelet");
            break;
        case 3:
            tmpItem->item.setItemName((char *)"Zircon Earrings");
            break;
        case 4:
            tmpItem->item.setItemName((char *)"Diamond Flower");
            break;
        case 5:
            tmpItem->item.setItemName((char *)"Pearl Piercing");
            break;
        case 6:
            tmpItem->item.setItemName((char *)"Onyx Prism");
            break;
        case 7:
            tmpItem->item.setItemName((char *)"Fire Spirit");
            break;
        case 8:
            tmpItem->item.setItemName((char *)"Water Mind");
            break;
        case 9:
            tmpItem->item.setItemName((char *)"Wind Fury");
            break;
        case 10:
            tmpItem->item.setItemName((char *)"Earth Heart");
            break;
        case 11:
            tmpItem->item.setItemName((char *)"Light Halo");
            break;
        case 12:
            tmpItem->item.setItemName((char *)"Dark Crown");
            break;
        case 13:
            tmpItem->item.setItemName((char *)"Chaos Effigy");
            break;
        }
        tmpItem->next = h_itemList;
        h_itemList = tmpItem;
        itemCounter--;
    }
    return (h_itemList);
}

void GameEnvironment::calculateEnemyNumber(int &roomTracker, int &enemyCounter)
{

    /*
    Considering the roomId (roomTracker), it evaluate how many enemy spawn in that Room.
    */

    srand(time(0));
    int roomId = roomTracker / ROOM_OFFSET;
    if (roomId == 0 || roomId == 16)
        enemyCounter = 0;
    else if (roomId == 1)
        enemyCounter = 3;
    else if (roomId < 6)
        enemyCounter = (roomId - 1) + (rand() % 2);
    else
        enemyCounter = 2 + (rand() % 4);
}

Position GameEnvironment::randomCoordinate(int start, int end)
{

    /*
    Generate random values between range in input.
    Serves to generate random position of Enemies and Items.
    */

    Position tmpPos;
    tmpPos.x = start + (std::rand() % (end - start + 1));
    tmpPos.y = start + (std::rand() % (end - start + 1));
    while (mvinch(tmpPos.y, tmpPos.x) != ' ')
    {
        tmpPos.x = start + (std::rand() % (end - start + 1));
        tmpPos.y = start + (std::rand() % (end - start + 1));
    }
    return tmpPos;
}

void GameEnvironment::cleanActionBox(int rightDistance, int bottomDistance, int startX, int startY)
{

    /*
    It clears the action box (items pick-up screen, opened door screen...).
    */

    for (int i = startY; i < rightDistance; i++)
    {
        mvprintw(bottomDistance + 2, i, " ");
        mvprintw(bottomDistance + 3, i, " ");
        mvprintw(bottomDistance + 4, i, " ");
    }
    for (int i = bottomDistance + 2; i <= bottomDistance + 4; i++)
    {
        mvprintw(i, startY, " ");
        mvprintw(i, rightDistance, " ");
    }
}

void GameEnvironment::drawActionBox(int rightDistance, int bottomDistance, int startX, int startY, int actionId)
{

    /*
    Based on actionId, it draws the box along with a variable text line.
    */

    cleanActionBox(rightDistance, bottomDistance, startX, startY);
    for (int i = startY; i < rightDistance; i++)
    {
        mvprintw(bottomDistance + 2, i, "-");
        mvprintw(bottomDistance + 4, i, "-");
    }
    for (int i = bottomDistance + 2; i < bottomDistance + 4; i++)
    {
        mvprintw(i, startY, "|");
        mvprintw(i, rightDistance, "|");
    }

    mvprintw(bottomDistance + 2, startY, "+");
    mvprintw(bottomDistance + 2, rightDistance, "+");
    mvprintw(bottomDistance + 4, startY, "+");
    mvprintw(bottomDistance + 4, rightDistance, "+");

    switch (actionId)
    {
    case 0:
        mvprintw(bottomDistance + 3, startY + 2, "%s", "You picked up Ruby Necklace!");
        break;
    case 1:
        mvprintw(bottomDistance + 3, startY + 2, "%s", "You picked up Sapphire Ring!");
        break;
    case 2:
        mvprintw(bottomDistance + 3, startY + 2, "%s", "You picked up Amethyst Bracelet!");
        break;
    case 3:
        mvprintw(bottomDistance + 3, startY + 2, "%s", "You picked up Zircon Earrings!");
        break;
    case 4:
        mvprintw(bottomDistance + 3, startY + 2, "%s", "You picked up Diamond Flower!");
        break;
    case 5:
        mvprintw(bottomDistance + 3, startY + 2, "%s", "You picked up Pearl Piercing!");
        break;
    case 6:
        mvprintw(bottomDistance + 3, startY + 2, "%s", "You picked up Onyx Prism!");
        break;
    case 7:
        mvprintw(bottomDistance + 3, startY + 2, "%s", "You picked up Fire Spirit!");
        break;
    case 8:
        mvprintw(bottomDistance + 3, startY + 2, "%s", "You picked up Water Mind!");
        break;
    case 9:
        mvprintw(bottomDistance + 3, startY + 2, "%s", "You picked up Wind Fury!");
        break;
    case 10:
        mvprintw(bottomDistance + 3, startY + 2, "%s", "You picked up Earth Heart!");
        break;
    case 11:
        mvprintw(bottomDistance + 3, startY + 2, "%s", "You picked up Light Halo!");
        break;
    case 12:
        mvprintw(bottomDistance + 3, startY + 2, "%s", "You picked up Dark Crown!");
        break;
    case 13:
        mvprintw(bottomDistance + 3, startY + 2, "%s", "You picked up Chaos Effigy!");
        break;
    case 14:
        mvprintw(bottomDistance + 3, startY + 2, "%s", "Your majestic powers opened the door!");
        break;
    case 15:
        mvprintw(bottomDistance + 3, startY + 2, "%s", "You killed a Snail!");
        break;
    case 16:
        mvprintw(bottomDistance + 3, startY + 2, "%s", "You killed a smol Lynx!");
        break;
    case 17:
        mvprintw(bottomDistance + 3, startY + 2, "%s", "You killed a Cobra!");
        break;
    case 18:
        mvprintw(bottomDistance + 3, startY + 2, "%s", "You killed a Bear!");
        break;
    }
}

void GameEnvironment::closeAllDoors(bool noEnemy, int rightDistance, int bottomDistance, int startX, int startY)
{

    /*
    When entering a Room, close all the doors in the Room if there are any enemy.
    The Doors re-open when all enemies in the Room are defeated.
    */
    if (!noEnemy)
    {
        for (int i = startY; i < rightDistance; i++)
        {
            if (mvinch(startX, i) == ' ')
                mvprintw(startX, i, "X");
            if (mvinch(bottomDistance, i) == ' ')
                mvprintw(bottomDistance, i, "X");
        }
        for (int i = startX; i < bottomDistance; i++)
        {
            if (mvinch(i, startY) == ' ')
                mvprintw(i, startY, "X");
            if (mvinch(i, rightDistance) == ' ')
                mvprintw(i, rightDistance, "X");
        }
    }
}

void GameEnvironment::openDoorWithKey(Entity entity, int &keyCounter, int rightDistance, int bottomDistance, int startX, int startY, bool noEnemy)
{

    /*
    When the player press the 'open door' command, check the closest door and it opens it.
    Note that the command can be pressed only against a door.
    Using this command spends a key in the player inventory.
    */

    if (noEnemy)
    {
        if (keyCounter >= 1)
        {
            if (mvinch(entity.getY() + 1, entity.getX()) == 'X')
            { // Down
                for (int i = startY; i < rightDistance; i++)
                {
                    if (mvinch(entity.getY() + 1, i) == 'X')
                        mvprintw(entity.getY() + 1, i, " ");
                }
                keyCounter--;
                drawActionBox(rightDistance, bottomDistance, startX, startY, 14);
            }
            else if (mvinch(entity.getY() - 1, entity.getX()) == 'X')
            { // Up
                for (int i = startY; i < rightDistance; i++)
                {
                    if (mvinch(entity.getY() - 1, i) == 'X')
                        mvprintw(entity.getY() - 1, i, " ");
                }
                keyCounter--;
                drawActionBox(rightDistance, bottomDistance, startX, startY, 14);
            }
            else if (mvinch(entity.getY(), entity.getX() - 1) == 'X')
            { // Left
                for (int i = startX; i < bottomDistance; i++)
                {
                    if (mvinch(i, startY) == 'X')
                        mvprintw(i, startY, " ");
                }
                keyCounter--;
                drawActionBox(rightDistance, bottomDistance, startX, startY, 14);
            }
            else if (mvinch(entity.getY(), entity.getX() + 1) == 'X')
            { // Right
                for (int i = startX; i < bottomDistance; i++)
                {
                    if (mvinch(i, rightDistance) == 'X')
                        mvprintw(i, rightDistance, " ");
                }
                keyCounter--;
                drawActionBox(rightDistance, bottomDistance, startX, startY, 14);
            }
        }
    }
}

bool GameEnvironment::checkItemPosition(p_itemList h_itemList, p_itemList tmpItem)
{

    /*
    This function check the correct position of the items.
    Not really a fundamental check, but helps preventing some bugs during
    the item drawing.
    */

    // If true, there are no duplicates
    bool flag = true;
    p_itemList tmpHead = h_itemList;
    while (tmpHead != NULL)
    {
        if (tmpItem->item.getX() == tmpHead->item.getY() || tmpItem->item.getX() == tmpHead->item.getY())
            flag = false;
        tmpHead = tmpHead->next;
    }
    return (flag);
}