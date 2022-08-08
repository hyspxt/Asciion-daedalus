#include "game.hpp"


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
    this->pause = true;
}

void Game::ncursesSetup()
{
    initscr();
    cbreak();
    curs_set(0);
    noecho();
    // nodelay(stdscr, TRUE);
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

    while (direction != 10)
    { // In future in this while needs to stay all commands available during the play
        move(3, 3);
        printw("%i", direction);

        if (direction == 115 || direction == 83) // Down
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
        if (direction == 119 || direction == 87) // Up
        {
            ch = mvinch(y - 1, x) & A_CHARTEXT;
            if (ch != '-')
            {

                mvprintw(y, x, " ");
                y = y - 1;
                move(y, x);
                printw("C");
            }
        }
        if (direction == 97 || direction == 65) // Left
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
        if (direction == 100 || direction == 68) // Right
        {
            ch = mvinch(y, x + 1) & A_CHARTEXT;
            if (ch != '|')
            {
                mvprintw(y, x, " ");
                x = x + 1;
                move(y, x);
                printw("C");
            }
        }
        direction = getch();
    }
}

void Game::menuChoice(GameEnvironment gameEnvironment, int *key, int *selection)
{
    // This function select between the menu choices based on the hovered button
    int menuCounter = 0;
    gameEnvironment.printMenuLogo();
    gameEnvironment.printMenuChoices(menuCounter);

    while (*key != 10)
    { // Wait until the ENTER key is pressed
        gameEnvironment.printMenuChoices(menuCounter);
        *key = getch();

        if (*key == 10)
            *selection = menuCounter; // When ENTER is pressed, start the relative section
        else if (*key == 259)
        {
            menuCounter--;
        }
        else if (*key == 258)
        {
            menuCounter++;
        }
        // gameEnvironment.printMenuChoices(menuCounter);

        // The counter can go over the max. number of choice
        // so it turn back to 0 when it happens
        // otherwise for <0

        if (menuCounter > 4)
            menuCounter = 0;
        else if (menuCounter < 0)
            menuCounter = 4;
    }
}

void Game::choiceHandler(GameEnvironment gameEnvironment)
{
    // This function initialize the game based on the choice made in the menu section
    int key, selection;
    ncursesSetup();
    menuChoice(gameEnvironment, &key, &selection);
    refresh();
    clear();
    while (pause)
    {
        switch (selection)
        {
        case 0: // The game here starts
        {
            pause = false;
            clear();

            // Fodder values
            gameEnvironment.drawRoom(71, 20, 7, 22, true);
            gameEnvironment.drawCharacter(30, 19, 'c');

            Weapon weapon("Test", 30);
            Player player(30, 19, 'c', 75, weapon);

            movePlayer(player);
            selection = 5;
            break;
        }
            // TODO FINISH
        case 1: // Prints How to Play
        {
            clear();

            gameEnvironment.escHowToPlay(key);

            selection = 5;
            break;
        }

        case 2: // Scoreboard TODO
        {       // FODDER
            clear();

            gameEnvironment.escHowToPlay(key);

            selection = 5;
            break;
        }
        case 3: // Settings TODO
        {       // FODDER
            clear();

            gameEnvironment.escHowToPlay(key);

            selection = 5;
            break;
        }
        case 4: // QUIT
        {
            refresh();
            clear();
            endwin();
            std::cout << "GG!" << std::endl;
            exit(1);
            break;
        }
        case 5: // When something finish, return to the menu
        {
            refresh();
            clear();
            choiceHandler(gameEnvironment);
            break;
        }
        }
    }
}

p_bullet Game::generateBullet(Entity entity, p_bullet &bulletList, int direction, bool enemyBull)
{
    p_bullet h_bullet = new bullet;
    if (direction == 261)
    { // shooting left
        h_bullet->x = entity.getX() + 1;
        h_bullet->y = entity.getY();
    }
    else if (direction == 260)
    { // shooting right
        h_bullet->x = entity.getX() - 1;
        h_bullet->y = entity.getY();
    }
    else if (direction == 259)
    { // shooting up
        h_bullet->x = entity.getX();
        h_bullet->y = entity.getY() - 1;
    }
    else if (direction == 258)
    { // shooting down
        h_bullet->x = entity.getX();
        h_bullet->y = entity.getY() + 1;
    }

    h_bullet->skin = entity.getRWeapon().getBulletSkin();
    h_bullet->speed = 1;
    h_bullet->enemyBullet = enemyBull;
    h_bullet->next = bulletList;

    return h_bullet;
}

void Game::enemyBullets(Player player, p_EnemyList h_enemyList, p_bullet &h_enemyBulletList) // keep attention that Entity is refered to the player
{
    // This function handle the generation of enemy bullets (but not their movements!!)
    int distanceX, distanceY, direction;

    while (h_enemyList != NULL){
        distanceX = player.getX() - h_enemyList->enemy.getX();
        distanceY = player.getY() - h_enemyList->enemy.getY();

        // TODO get an eye on this piece of code

        if (distanceX > distanceY){
            if (distanceX > 0)
                direction = 260;  // Shooting right
            else direction = 261; // Shooting left
        }
        else  {
            if (distanceY > 0) // Shooting down
                direction = 258;
            else direction = 259;
        }
        
        h_enemyBulletList = generateBullet(h_enemyList->enemy, h_enemyBulletList, direction, true);

        h_enemyList = h_enemyList -> next;
    }
}