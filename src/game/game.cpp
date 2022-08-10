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
    this->playerBullets = NULL;
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

void Game::movePlayer(Entity entity)
{

    int direction = getch();
    int y = entity.getY();
    int x = entity.getX();

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
            entity.setX(x);
            entity.setY(y);
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
            entity.setX(x);
            entity.setY(y);
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
            entity.setX(x);
            entity.setY(y);
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
            entity.setX(x);
            entity.setY(y);
        }
        if (direction == 261 || direction == 260 || direction == 258 || direction == 259)
        {

            int range = entity.getRWeapon().getBulletRange();

            // Correction needed here: the bullet fly but only with the command
            // they should be moving on their own until their range is 0

            // After that, verify the implementation with destroyBullet()

            this->playerBullets = generateBullet(entity, this->playerBullets, direction, false);
            moveBullets(this->playerBullets);
            range--;
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

            RangedWeapon rWp("Luha", 3, '-m', 1, 4);
            Entity entity(20, 29, 'C', 50);
            entity.setRWeapon(rWp);

            movePlayer(entity);
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

p_bullet Game::generateBullet(Entity entity, p_bullet &bulletList, int dir, bool enemyBull)
{
    p_bullet h_bullet = new bullet;
    if (dir == 261)
    { // shooting right
        h_bullet->x = entity.getX() + 1;
        h_bullet->y = entity.getY();
    }
    else if (dir == 260)
    { // shooting left
        h_bullet->x = entity.getX() - 1;
        h_bullet->y = entity.getY();
    }
    else if (dir == 259)
    { // shooting up
        h_bullet->x = entity.getX();
        h_bullet->y = entity.getY() - 1;
    }
    else if (dir == 258)
    { // shooting down
        h_bullet->x = entity.getX();
        h_bullet->y = entity.getY() + 1;
    }

    h_bullet->skin = entity.getRWeapon().getBulletSkin();
    h_bullet->speed = 1;
    h_bullet->direction = dir;
    h_bullet->enemyBullet = enemyBull;
    h_bullet->next = bulletList;

    return h_bullet;
}

void Game::enemyBullets(Player player, p_EnemyList h_enemyList, p_bullet &h_enemyBulletList) // keep attention that Entity is refered to the player
{
    // This function handle the generation of enemy bullets (but not their movements!!)
    int distanceX, distanceY, direction;

    while (h_enemyList != NULL)
    {
        distanceX = player.getX() - h_enemyList->enemy.getX();
        distanceY = player.getY() - h_enemyList->enemy.getY();

        // TODO get an eye on this piece of code

        if (distanceX > distanceY)
        {
            if (distanceX > 0)
                direction = 261; // Shooting right
            else
                direction = 260; // Shooting left
        }
        else
        {
            if (distanceY > 0) // Shooting down
                direction = 258;
            else
                direction = 259; // Shooting up
        }

        h_enemyBulletList = generateBullet(h_enemyList->enemy, h_enemyBulletList, direction, true);

        h_enemyList = h_enemyList->next;
    }
}

void Game::moveBullets(p_bullet h_bulletList)
{
    // This function handle the bullet movements, both for player and enemies
    char b_trail[2]; // Bullet trail keep count of the bullet skins along the firing, one char will be always "" and the other will be the bullet skin
    while (h_bulletList != NULL)
    {
        if ((!h_bulletList->enemyBullet && h_bulletList->direction == 261) || (h_bulletList->enemyBullet && h_bulletList->direction == 260))
            h_bulletList->x += h_bulletList->speed;
        else if ((!h_bulletList->enemyBullet && h_bulletList->direction == 260) || (h_bulletList->enemyBullet && h_bulletList->direction == 261))
            h_bulletList->x -= h_bulletList->speed;
        else if ((!h_bulletList->enemyBullet && h_bulletList->direction == 258) || (h_bulletList->enemyBullet && h_bulletList->direction == 259))
            h_bulletList->y += h_bulletList->speed;
        else if ((!h_bulletList->enemyBullet && h_bulletList->direction == 259) || (h_bulletList->enemyBullet && h_bulletList->direction == 258))
            h_bulletList->y -= h_bulletList->speed;

        move(h_bulletList->y, h_bulletList->x);
        b_trail[0] = h_bulletList->skin;
        if (!h_bulletList->enemyBullet)
        { // If its a bullet enemy, color red the bullet
            init_pair(3, COLOR_RED, -1);
            attron(COLOR_PAIR(3));
            printw(b_trail);
            attroff(COLOR_PAIR(3));
        }
        else
            printw(b_trail);

        h_bulletList = h_bulletList->next;
    }
}

void Game::destroyBullet(p_bullet &h_bulletList, int bulletX, int bulletY)
{
    if (bulletX == this->leftDistance || bulletX == this->rightDistance // if the bullet is shooted against the border
        || bulletY == this->bottomDistance || bulletY == this->topDistance)
        h_bulletList = NULL;
    else
    {
        p_bullet head = h_bulletList, prev = h_bulletList;
        p_bullet tmp;
        bool destroy;

        // qui mettere le direzioni
        while (head != NULL)
        {
            if ((!head->enemyBullet && head->direction == 261) || (head->enemyBullet && head->direction == 260))
            {
                // Right
                destroy = (!isEmpty(head->x + 1, head->y)) &&
                          (!isItem(head->x + 1, head->y)) &&
                          (!isEnemy(head->x + 1, head->y));

                if (head->enemyBullet)
                    destroy &= (!isBullet(head->x + 1, head->y));
            }
            else if ((!head->enemyBullet && head->direction == 260) || (head->enemyBullet && head->direction == 261))
            {
                // Left
                destroy = (!isEmpty(head->x - 1, head->y)) &&
                          (!isItem(head->x - 1, head->y)) &&
                          (!isEnemy(head->x - 1, head->y));

                if (head->enemyBullet)
                    destroy &= (!isBullet(head->x - 1, head->y));
            }
            else if ((!head->enemyBullet && head->direction == 258) || (head->enemyBullet && head->direction == 259))
            {
                // Down
                destroy = (!isEmpty(head->x, head->y + 1)) &&
                          (!isItem(head->x, head->y + 1)) &&
                          (!isEnemy(head->x, head->y + 1));

                if (head->enemyBullet)
                    destroy &= (!isBullet(head->x, head->y - 1));
            }
            else if ((!head->enemyBullet && head->direction == 259) || (head->enemyBullet && head->direction == 258))
            {
                // Up
                destroy = (!isEmpty(head->x, head->y - 1)) &&
                          (!isItem(head->x, head->y - 1)) &&
                          (!isEnemy(head->x, head->y - 1));

                if (head->enemyBullet)
                    destroy &= (!isBullet(head->x, head->y + 1));
            }

            if (destroy || head->x > (rightDistance - 1) || head->x < (leftDistance + 1) || head->y < bottomDistance + 1 || head->y > topDistance - 1)
            {
                if (head == h_bulletList)
                {
                    tmp = h_bulletList;
                    h_bulletList = head->next;
                    delete tmp;
                    prev = h_bulletList;
                    head = h_bulletList;
                }
                else
                {
                    tmp = prev->next;
                    prev->next = head->next;
                    delete tmp;
                    head = prev->next;
                }
            }
            else
            {
                prev = head;
                head = head->next;
            }
        }
    }
}

bool Game::isEmpty(int x, int y)
{
    if (mvinch(y, x) == ' ')
        return true;
}
bool Game::isItem(int x, int y)
{
    if (mvinch(y, x) == 'A' || mvinch(y, x) == 'P' || mvinch(y, x) == '?')
        return true;
}
bool Game::isBullet(int x, int y)
{
    if (mvinch(y, x) == '=' || mvinch(y, x) == '*' || mvinch(y, x) == '0')
        return true;
}
bool Game::isEnemy(int x, int y)
{
    if (mvinch(y, x) == '@')
        ;
}

p_EnemyList Game::destroyEnemy(p_EnemyList h_enemyList, Enemy enemy)
{
    p_EnemyList head = h_enemyList, prev = h_enemyList, tmp;
    char skinReplace[2];
    while (h_enemyList != NULL)
    {
        if ((h_enemyList->enemy.getX() == enemy.getX()) &&
            (h_enemyList->enemy.getY() == enemy.getY()))
        {
            skinReplace[0] = h_enemyList->enemy.getSkin();
            mvprintw(h_enemyList->enemy.getY(), h_enemyList->enemy.getX(), skinReplace);
            if (h_enemyList == head)
            {
                tmp = head;
                head = h_enemyList->next;
                delete tmp;
                prev = head;
                h_enemyList = head;
            }
            else
            {
                tmp = prev->next;
                prev->next = h_enemyList->next;
                delete tmp;
                h_enemyList = prev->next;
            }
        }
        else
        {
            prev = h_enemyList;
            h_enemyList = h_enemyList->next;
        }
    }
    return head;
}
