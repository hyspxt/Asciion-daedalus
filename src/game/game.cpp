#include "game.hpp"

#include <ncurses.h>
#include <ctime>
#include <cmath>
#include <iostream>
#include <unistd.h>
#include <string.h>
#include <locale.h>
#include <tuple>

#define ROOM_OFFSET 14

int points = 0;

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
    this->enemyBullets = NULL;
    this->timer = 0;
    this->enemyTimer = 0;
}

void Game::ncursesSetup()
{

    // Starts the cursor

    setlocale(LC_ALL, "");
    initscr();
    cbreak();
    curs_set(0);
    noecho();
    // nodelay(stdscr, TRUE);  // decomment here if there are any problem with fluidity
    keypad(stdscr, TRUE);
    use_default_colors(); // Not essential, but i noticed in some tests some bug so here it is
    start_color();
}

void Game::ncursesStop()
{
    // End the cursor and free the memory

    refresh();
    noraw();
    endwin(); // Remember to delete the Getch and deallocation of ncurses!! TODO
}

std::tuple<p_itemList, Entity, int> Game::determineItemEffect(GameEnvironment gameEnvironment, int x, int y, p_itemList h_itemList, Entity entity, int pnt, int keyCounter, RangedWeapon playerWeapon)
{

    /*
    Determine effects of taken items by their id.
    Effects are boost to player's stats.
    K items garant a key, needed to open doors.
    */

    p_itemList tmpItem = h_itemList;
    bool endFlag = false;
    while (tmpItem->item.getX() != x || tmpItem->item.getY() != y)
    {
        tmpItem = tmpItem->next;
    }
    int identifier = tmpItem->item.getId();
    // The actionBox shows what item the player has picked-up
    gameEnvironment.drawActionBox(rightDistance, bottomDistance, maxX, maxY, identifier);

    switch (identifier)
    {
    case 0: // Ruby Necklace
        entity.increaseLifePoints(6);
        points += 350;
        endFlag = true;
        break;
    case 1: // Sapphire Ring
        entity.increaseLifePoints(3);
        entity.increaseCurrentLifePoints(3);
        points += 150;
        endFlag = true;
        break;
    case 2: // Amethyst Bracelet
        entity.increaseLifePoints(2);
        playerWeapon.setBulletRange(playerWeapon.getBulletRange() + 2);
        points += 150;
        endFlag = true;
        break;
    case 3: // Zircon Earrings
        entity.increaseLifePoints(1);
        points += 400;
        endFlag = true;
        break;
    case 4: // Diamond Flower
        entity.increaseLifePoints(2);
        playerWeapon.increaseDamage(5);
        points += 500;
        endFlag = true;
        break;
    case 5: // Pearl Piercing
        entity.increaseLifePoints(1);
        playerWeapon.increaseDamage(1);
        points += 250;
        endFlag = true;
        break;
    case 6: // Onyx Prism
        entity.increaseLifePoints(3);
        points += 250;
        endFlag = true;
        break;
    case 7: // Fire Spirit
        entity.increaseCurrentLifePoints(5);
        keyCounter++;
        points += 100;
        endFlag = true;
        break;
    case 8: // Water Mind
        entity.increaseCurrentLifePoints(3);
        entity.increaseLifePoints(1);
        points += 120;
        keyCounter += 1;
        endFlag = true;
        break;
    case 9: // Wind Fury
        entity.increaseCurrentLifePoints(2);
        playerWeapon.increaseDamage(2);
        keyCounter += 1;
        points += 190;
        endFlag = true;
        break;
    case 10: // Earth Heart
        entity.increaseCurrentLifePoints(10);
        keyCounter += 1;
        points += 200;
        endFlag = true;
        break;
    case 11: // Light Halo
        entity.increaseLifePoints(5);
        entity.increaseCurrentLifePoints(5);
        keyCounter += 1;
        points += 450;
        endFlag = true;
        break;
    case 12: // Dark Crown
        entity.increaseCurrentLifePoints(5);
        entity.getRWeapon().increaseDamage(5);
        keyCounter += 1;
        points += 450;
        endFlag = true;
        break;
    case 13: // Chaos Effigy
        entity.increaseLifePoints(2);
        entity.increaseCurrentLifePoints(2);
        playerWeapon.increaseDamage(3);
        keyCounter += 1;
        points += 750;
        endFlag = true;
        break;
    }

    if (endFlag)
    {
        // After an item is taken, remove it from the Room.
        entity.setRWeapon(playerWeapon);
        h_itemList = deleteItem(tmpItem, h_itemList);
        mvprintw(tmpItem->item.getY(), tmpItem->item.getX(), " ");
    }
    return std::make_tuple(h_itemList, entity, keyCounter);
}

p_itemList Game::deleteItem(p_itemList itemToDelete, p_itemList h_itemList)
{

    /*
    Delete itemToDelete from h_itemList.
    Used after an item is picked-up by the player.
    */

    p_itemList tmpHead = h_itemList, tmpPrev = tmpHead, tmpItem;
    bool flag = false;
    while (h_itemList != NULL && !flag)
    {
        if (h_itemList->item.getX() == itemToDelete->item.getX() && h_itemList->item.getY() == itemToDelete->item.getY() && h_itemList->item.getSkin() == itemToDelete->item.getSkin() && h_itemList->item.getId() == itemToDelete->item.getId())
        {
            if (h_itemList == tmpHead)
            {
                tmpItem = tmpHead;
                tmpHead = h_itemList->next;
                delete tmpItem;
                tmpPrev = tmpHead;
                h_itemList = tmpHead;
            }
            else
            {
                tmpItem = tmpPrev->next;
                tmpPrev->next = h_itemList->next;
                delete tmpItem;
                h_itemList = tmpPrev->next;
            }
            flag = true; // If there are errors remove me due to infinite items generation
        }
        else
        {
            tmpPrev = h_itemList;
            h_itemList = h_itemList->next;
        }
    }
    return tmpHead;
}

std::tuple<Entity, int> Game::gameInputs(GameEnvironment gameEnvironment, Entity entity, int direction, p_Room h_roomList, int points, int keyCounter, bool noEnemy, int &timeCounter)
{
    /*
    Perform some action (only player) after a input is taken with getch().
    Action like movements (in four directions), shooting, opening doors...
    */

    srand(time(0));
    if (direction == 115 || direction == 83) // Down Movement [s] key
    {

        if (isEmpty(entity.getX(), entity.getY() + 1))
        {
            mvprintw(entity.getY(), entity.getX(), " ");
            entity.dirDown();
        }
        else if (isItem(entity.getX(), entity.getY() + 1)) // Check if it's an item
        {
            mvprintw(entity.getY() + 1, entity.getX(), " ");
            std::tie(h_roomList->itemList, entity, keyCounter) = determineItemEffect(gameEnvironment, entity.getX(), entity.getY() + 1,
                                                                                     h_roomList->itemList, entity, points, keyCounter, entity.getRWeapon());
            mvprintw(entity.getY(), entity.getX(), " ");
            entity.dirDown();
        }
    }
    if (direction == 119 || direction == 87) // Up Movement [w] key
    {

        if (isEmpty(entity.getX(), entity.getY() - 1))
        {
            mvprintw(entity.getY(), entity.getX(), " ");
            entity.dirUp();
        }
        else if (isItem(entity.getX(), entity.getY() - 1))
        {
            mvprintw(entity.getY() - 1, entity.getX(), " ");
            std::tie(h_roomList->itemList, entity, keyCounter) = determineItemEffect(gameEnvironment, entity.getX(), entity.getY() - 1,
                                                                                     h_roomList->itemList, entity, points, keyCounter, entity.getRWeapon());
            mvprintw(entity.getY(), entity.getX(), " ");
            entity.dirUp();
        }
    }
    if (direction == 97 || direction == 65) // Left Movement [a] key
    {

        if (isEmpty(entity.getX() - 1, entity.getY()))
        {
            mvprintw(entity.getY(), entity.getX(), " ");
            entity.dirLeft();
        }
        else if (isItem(entity.getX() - 1, entity.getY()))
        {
            mvprintw(entity.getY(), entity.getX() - 1, " ");
            std::tie(h_roomList->itemList, entity, keyCounter) = determineItemEffect(gameEnvironment, entity.getX() - 1, entity.getY(),
                                                                                     h_roomList->itemList, entity, points, keyCounter, entity.getRWeapon());
            mvprintw(entity.getY(), entity.getX(), " ");
            entity.dirLeft();
        }
    }
    if (direction == 100 || direction == 68) // Right Movement [d] key
    {
        if (isEmpty(entity.getX() + 1, entity.getY()))
        {
            mvprintw(entity.getY(), entity.getX(), " ");
            entity.dirRight();
        }
        else if (isItem(entity.getX() + 1, entity.getY()))
        {
            mvprintw(entity.getY(), entity.getX() + 1, " ");
            std::tie(h_roomList->itemList, entity, keyCounter) = determineItemEffect(gameEnvironment, entity.getX() + 1, entity.getY(),
                                                                                     h_roomList->itemList, entity, points, keyCounter, entity.getRWeapon());
            mvprintw(entity.getY(), entity.getX(), " ");
            entity.dirRight();
        }
    }
    if (direction == 261 || direction == 260 || direction == 258 || direction == 259)
    {
        // Shoot a single bullet in one of the four directions
        //  (up, down, left, right) [arrow keys]
        int flag = false;
        int expansion = entity.getRWeapon().getBulletSpeed() + 1;
        while (expansion > 0)
        {
            if (direction == 261 && !isEmpty(entity.getX() + expansion, entity.getY()))
                flag = true;
            if (direction == 260 && !isEmpty(entity.getX() - expansion, entity.getY()))
                flag = true;
            if (direction == 258 && !isEmpty(entity.getX(), entity.getY() + expansion))
                flag = true;
            if (direction == 259 && !isEmpty(entity.getX(), entity.getY() - expansion))
                flag = true;
            expansion--;
        }

        if (!flag)
            this->playerBullets = generateBullet(entity, this->playerBullets, direction, false);
    }
    if (direction == 114 || direction == 82) // Open door pressing [r] key
    {
        gameEnvironment.openDoorWithKey(entity, keyCounter, rightDistance, bottomDistance, maxX, maxY, noEnemy);
    }

    if (timeCounter >= 20) // Auto clear the actionBox
    {
        timeCounter = 0;
        gameEnvironment.cleanActionBox(rightDistance, bottomDistance, maxX, maxY);
    }
    else
        timeCounter++;

    return std::make_tuple(entity, keyCounter);
}

void Game::menuChoice(GameEnvironment gameEnvironment, int *key, int *choice)
{
    /*
     This function select between the menu choices based on the hovered button.
    menuCounter handle the button that should be colored when selected.
    */
    int menuCounter = 0;
    gameEnvironment.printMenuLogo();
    gameEnvironment.printMenuChoices(menuCounter);

    while (*key != 10)
    { // Wait until the ENTER key is pressed
        gameEnvironment.printMenuChoices(menuCounter);
        *key = getch();

        if (*key == 10)
            *choice = menuCounter; // When ENTER is pressed, start the relative section
        else if (*key == 259)
        {
            menuCounter--;
        }
        else if (*key == 258)
        {
            menuCounter++;
        }

        /*
        The counter can go over the max. number of choice
        so it turn back to 0 when it happens
        otherwise for < 0
        */

        if (menuCounter > 4)
            menuCounter = 0;
        else if (menuCounter < 0)
            menuCounter = 4;
    }
}

void Game::choiceHandler(GameEnvironment gameEnvironment)
{
    /*
    This function initialize the game based on the choice made in the menu section.
    */
    int key, choice;
    ncursesSetup();
    menuChoice(gameEnvironment, &key, &choice);
    refresh();
    clear();
    while (pause)
    {
        switch (choice)
        {
        case 0: // The game here starts
        {

            pause = false;
            clear();
            refresh();

            gameHandler(gameEnvironment, key);
            clear();
            refresh();
            gameEnvironment.escLoss(key, points);

            choice = 5;
            break;
        }

        case 1: // Prints How to Play
        {
            clear();
            gameEnvironment.escHowToPlay(key);
            refresh();
            choice = 5;
            break;
        }

        case 2: // Scoreboard
        {

            clear();

            refresh();
            gameEnvironment.escScoreboard(key);
            refresh();

            choice = 5;
            break;
        }
        case 3: // The Plot
        {
            clear();

            refresh();
            gameEnvironment.escLore(key);
            refresh();
            choice = 5;
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

    /*
    Generate a bullet based on the key with it was shooted.
    */

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
    h_bullet->speed = entity.getRWeapon().getBulletSpeed();
    h_bullet->direction = dir;
    h_bullet->enemyBullet = enemyBull;
    h_bullet->next = bulletList;

    return h_bullet;
}

void Game::handleEnemyBullets(Entity player, p_EnemyList h_enemyList, p_bullet &h_enemyBulletList) // keep attention that Entity is refered to the player
{
    /*
     This function handle the generation of enemy bullets (but not their movements!!).
    */
    int distanceX, distanceY, direction;

    while (h_enemyList != NULL)
    {

        distanceX = player.getX() - h_enemyList->enemy.getX();
        distanceY = player.getY() - h_enemyList->enemy.getY();

        if (this->enemyTimer % 22 == 0)
        {
            if (distanceX < distanceY)
            {
                if (distanceX > 0)
                    direction = 260; // Shooting Left
                else
                    direction = 261; // Shooting Right
            }
            else
            {
                if (distanceY > 0) // Shooting Up
                    direction = 259;
                else
                    direction = 258; // Shooting Down
            }
            switch (direction)
            {
            case 260: // Up
                if (isEmpty(h_enemyList->enemy.getX() - 1, h_enemyList->enemy.getY()))
                    h_enemyBulletList = generateBullet(h_enemyList->enemy, h_enemyBulletList, direction, true);
                break;
            case 261: // Down
                if (isEmpty(h_enemyList->enemy.getX() + 1, h_enemyList->enemy.getY()))
                    h_enemyBulletList = generateBullet(h_enemyList->enemy, h_enemyBulletList, direction, true);
                break;
            case 259: // Left
                if (isEmpty(h_enemyList->enemy.getX(), h_enemyList->enemy.getY() - 1))
                    h_enemyBulletList = generateBullet(h_enemyList->enemy, h_enemyBulletList, direction, true);
                break;
            case 258: // Right
                if (isEmpty(h_enemyList->enemy.getX(), h_enemyList->enemy.getY() + 1))
                    h_enemyBulletList = generateBullet(h_enemyList->enemy, h_enemyBulletList, direction, true);
                break;
            }
        }
        h_enemyList = h_enemyList->next;
    }
}

void Game::moveBullets(p_bullet h_bulletList)
{
    /*
    This function handle the bullet movements, both for player and enemies
    */

    char b_trail[2]; // Bullet trail keep count of the bullet skins along the firing, one char will be always "" and the other will be the bullet skin
    while (h_bulletList != NULL)
    {

        mvprintw(h_bulletList->y, h_bulletList->x, " ");

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

        if (isEmpty(h_bulletList->x, h_bulletList->y))
        {
            if (h_bulletList->enemyBullet)
            { // If its a bullet enemy,  the bullet is red

                init_pair(3, COLOR_RED, -1);
                attron(COLOR_PAIR(3));
                printw(b_trail);
                attroff(COLOR_PAIR(3));
            }
            else
                printw(b_trail);
        }
        h_bulletList = h_bulletList->next;
    }
}

void Game::destroyBullet(p_bullet &h_bulletList, int playerX, int playerY)
{
    if (playerX == this->leftDistance || playerX == this->rightDistance // if the bullet is shooted against the border
        || playerY == this->bottomDistance || playerY == this->topDistance)
        h_bulletList = NULL;
    else
    {
        p_bullet head = h_bulletList, prev = h_bulletList;
        p_bullet tmp;
        bool destroy;

        while (head != NULL)
        {
            if ((!head->enemyBullet && head->direction == 261) || (head->enemyBullet && head->direction == 260))
            {
                // Right
                destroy = (!isEmpty(head->x + 1, head->y)) &&
                          (!isItem(head->x + 1, head->y)) &&
                          (!isBullet(head->x + 1, head->y));

                if (head->enemyBullet)
                    destroy &= (!isEnemy(head->x + 1, head->y));
            }
            else if ((!head->enemyBullet && head->direction == 260) || (head->enemyBullet && head->direction == 261))
            {
                // Left
                destroy = (!isEmpty(head->x - 1, head->y)) &&
                          (!isItem(head->x - 1, head->y)) &&
                          (!isBullet(head->x - 1, head->y));

                if (head->enemyBullet)
                    destroy &= (!isEnemy(head->x - 1, head->y));
            }
            else if ((!head->enemyBullet && head->direction == 258) || (head->enemyBullet && head->direction == 259))
            {
                // Down
                destroy = (!isEmpty(head->x, head->y + 1)) &&
                          (!isItem(head->x, head->y + 1)) &&
                          (!isBullet(head->x, head->y + 1));

                if (head->enemyBullet)
                    destroy &= (!isEnemy(head->x, head->y + 1));
            }
            else if ((!head->enemyBullet && head->direction == 259) || (head->enemyBullet && head->direction == 258))
            {
                // Up
                destroy = (!isEmpty(head->x, head->y - 1)) &&
                          (!isItem(head->x, head->y - 1)) &&
                          (!isBullet(head->x, head->y - 1));

                if (head->enemyBullet)
                    destroy &= (!isEnemy(head->x, head->y - 1));
            }

            if (destroy || head->x > 70 || head->x < (leftDistance + 1) || head->y > bottomDistance - 1 || head->y < (topDistance + 1))
            {
                if (head == h_bulletList)
                {
                    mvprintw(head->y, head->x, " ");
                    tmp = h_bulletList;
                    h_bulletList = head->next;
                    delete tmp;

                    prev = h_bulletList;
                    head = h_bulletList;
                }
                else
                {
                    mvprintw(head->y, head->x, " ");
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

void Game::destroySingleBullet(p_bullet &h_bulletList)
{

    /*
    Actually not used, but it should destroy only the first bullet in the bullet list.
    */

    p_bullet head = h_bulletList, prev = h_bulletList;
    p_bullet tmp;
    if (h_bulletList != NULL)
    {
        if (head == h_bulletList)
        {
            mvprintw(head->y, head->x, " ");
            tmp = h_bulletList;
            h_bulletList = head->next;
            delete tmp;

            prev = h_bulletList;
            head = h_bulletList;
        }
        else
        {
            mvprintw(head->y, head->x, " ");
            tmp = prev->next;
            prev->next = head->next;
            delete tmp;
            head = prev->next;
        }
    }
}

bool Game::isEmpty(int x, int y)
{
    if (mvinch(y, x) == ' ')
        return (true);
    else
        return (false);
}
bool Game::isItem(int x, int y)
{
    if (mvinch(y, x) == 'A' || mvinch(y, x) == 'K' || mvinch(y, x) == '?')
        return true;
    else
        return (false);
}
bool Game::isBullet(int x, int y)
{
    if (mvinch(y, x) == '"' || mvinch(y, x) == '#' || mvinch(y, x) == 'o' || mvinch(y, x) == ',')
        return true;
    else
        return (false);
}
bool Game::isEnemy(int x, int y)
{
    if (mvinch(y, x) == '@' || mvinch(y, x) == '$' || mvinch(y, x) == 'l' || mvinch(y, x) == '&')
        return true;
    else
        return (false);
}

p_EnemyList Game::destroyEnemy(p_EnemyList h_enemyList, Enemy enemy)
{

    /*
    Destroy an enemy when is killed.
    The condition is determined in the collision function.
    */

    p_EnemyList head = h_enemyList, prev = h_enemyList, tmp;
    while (h_enemyList != NULL)
    {
        if ((h_enemyList->enemy.getX() == enemy.getX()) &&
            (h_enemyList->enemy.getY() == enemy.getY()))
        {
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

void Game::bulletCollision(p_bullet &h_bulletList, p_EnemyList h_enemyList, Entity &entity, int &points, int &hearts, bool &pause)
{

    /*
    This function handle the various cases when a bullet collides with something.
    */

    bool wallHit = false, enemyHit = false, playerHit = false;
    int enemyX, enemyY, playerX, playerY;
    p_bullet head = h_bulletList;
    p_EnemyList tmpEnemy = h_enemyList;
    while (h_enemyList != NULL && !wallHit && !enemyHit && !playerHit)
    {
        while (h_bulletList != NULL && !wallHit && !enemyHit && !playerHit)
        {
            if (!h_bulletList->enemyBullet)
            {
                enemyX = h_enemyList->enemy.getX();
                enemyY = h_enemyList->enemy.getY();
                if (((enemyX == h_bulletList->x + 1) && (enemyY == h_bulletList->y)) ||
                    ((enemyX == h_bulletList->x - 1) && enemyY == h_bulletList->y) ||
                    ((enemyX == h_bulletList->x) && enemyY == h_bulletList->y - 1) ||
                    ((enemyX == h_bulletList->x) && enemyY == h_bulletList->y + 1))
                    enemyHit = true;
            }
            else
            {
                playerX = entity.getX();
                playerY = entity.getY();
                if (((playerX == h_bulletList->x + 1) && playerY == h_bulletList->y) ||
                    ((playerX == h_bulletList->x - 1) && playerY == h_bulletList->y) ||
                    (playerX == h_bulletList->x && playerY == h_bulletList->y + 1) ||
                    (playerX == h_bulletList->x && playerY == h_bulletList->y - 1) ||
                    (playerX == h_bulletList->x && playerY == h_bulletList->y))
                    playerHit = true;
            }
            if (mvinch(h_bulletList->x, h_bulletList->y + 1) == '-' ||
                mvinch(h_bulletList->x + 1, h_bulletList->y) == '|' ||
                mvinch(h_bulletList->x, h_bulletList->y - 1) == '-' ||
                mvinch(h_bulletList->x - 1, h_bulletList->y) == '|')
            {
                wallHit = true;
            }
            h_bulletList = h_bulletList->next;
        }
        h_bulletList = head;
        if (wallHit || enemyHit || playerHit)
        {
            // So, the bullet must be destroyed.
            break;
        }
        else
            h_enemyList = h_enemyList->next;
    }

    char skinReplace[2];
    init_pair(3, COLOR_RED, -1);
    attron(COLOR_PAIR(3));

    if (enemyHit) // When the enemy take a hit, paint his body red.
    {
        skinReplace[0] = h_enemyList->enemy.getSkin();
        mvprintw(h_enemyList->enemy.getY(), h_enemyList->enemy.getX(), skinReplace);
        h_enemyList->enemy.decreaseCurrentLifePoints(entity.getRWeapon().getDamage());
        if (h_enemyList->enemy.getCurrentLifePoints() <= 0)
        { // kill the enemy

            attroff(COLOR_PAIR(3));
            mvprintw(h_enemyList->enemy.getY(), h_enemyList->enemy.getX(), " ");
            attron(COLOR_PAIR(3));

            h_enemyList = destroyEnemy(tmpEnemy, h_enemyList->enemy);
            increasePoints(points, h_enemyList->enemy.getKillScore());
        }
    }
    else if (playerHit)
    {
        entity.decreaseCurrentLifePoints(h_enemyList->enemy.getMeleeDamage());
        checkPlayerDeath(entity, pause, hearts); // If playerLives > 0, then the player is still alive.
        skinReplace[0] = entity.getSkin();
        mvprintw(entity.getY(), entity.getX(), skinReplace);
    }

    attroff(COLOR_PAIR(3));
}

void Game::checkPlayerDeath(Entity &entity, bool &pause, int &hearts)
{

    /*
    Every time the player take damage, this should trigger.
    Check if the playerLives > 0 and if not make player die and print Lose screen.
    */
    if (entity.getCurrentLifePoints() <= 0)
    {
        if (hearts >= 1)
        {
            entity.setCurrentLifePoints(entity.getLifePoints());
            hearts--;
        }
        else
        {
            pause = true;
        }
    }
}

void Game::increasePoints(int &gamePoints, int p_add)
{
    /*
    This function increase the game points with the specified quantity
    */
    gamePoints += p_add;
}

void Game::increaseTimers(int &timer, int &enemyTimer)
{

    /*
    Increase the two timers that manage the game clock.
    The first handle some time-limited elements like actionBox.
    The second handle enemy actions like bullet shooting.
    */

    timer++;
    enemyTimer++;
}

void Game::setPause(int direction)
{

    /*
    It blocks the game when the condition lead to a lose/win.
    */

    if (direction == 10)
        pause = true;
}
void Game::getInput(int &key)
{
    key = getch();
}

p_EnemyList Game::generateEnemy(GameEnvironment gameEnvironment, int enemyCounter, int roomTracker, p_EnemyList h_enemyList)
{

    /*
    Generate random type enemies, based on which Room the player is.
    */

    srand(unsigned(time(0)));

    int enemyLp, enemyKs, enemyType;
    char enemySkin;
    RangedWeapon enemyWeapon((char *)"Basic Weapon", 3, 'o', 1, 9);
    RangedWeapon fakeWeapon((char *)"FAKE", 0, ' ', 1, 1);

    int x, y;
    bool flag = true;
    while (enemyCounter > 0)
    { // The list here should be not NULL

        if (roomTracker / ROOM_OFFSET <= 2)
            enemyType = 0;
        else if (roomTracker / ROOM_OFFSET <= 6)
            enemyType = rand() % 2;
        else if (roomTracker /  ROOM_OFFSET <= 10)
            enemyType = rand() % 3;
        else
            enemyType = rand() % 4;

        switch (enemyType)
        {
        case 0: // First enemy type -> Snail
            enemySkin = '@';
            enemyWeapon.setBulletSkin('o');
            enemyWeapon.setDamage(3);
            enemyLp = 25, enemyKs = 200;
            break;
        case 1: // Second enemy type -> Smol Lynx
            enemySkin = '$';
            enemyLp = 40, enemyKs = 350;
            enemyWeapon.setBulletSkin(',');
            enemyWeapon.setDamage(5);
            break;
        case 2: // Third enemy type -> Cobra
            enemySkin = 'l';
            enemyLp = 65, enemyKs = 700;
            enemyWeapon.setBulletSkin('"');
            enemyWeapon.setDamage(8);
            break;
        case 3: // Fourth enemy type -> Bear
            enemySkin = '&';
            enemyLp = 100, enemyKs = 1000;
            enemyWeapon.setBulletSkin('#');
            enemyWeapon.setDamage(10);
            break;
        }
        if (roomTracker / ROOM_OFFSET == 2)
        {
            x = gameEnvironment.randomCoordinate(39, 48).x;
            y = gameEnvironment.randomCoordinate(9, 19).y;
        }
        else
        {
            x = gameEnvironment.randomCoordinate(39, 68).x;
            y = gameEnvironment.randomCoordinate(9, 19).y;
        }
        p_EnemyList tmpHead = new EnemyList;

        Enemy enemy(x, y, enemySkin, enemyLp, enemyKs, 1);
        enemy.setRWeapon(enemyWeapon);
        enemy.setMeleeDamage(enemyWeapon.getDamage());

        tmpHead->enemy = enemy;
        tmpHead->next = h_enemyList;
        h_enemyList = tmpHead;

        flag = false;
        enemyCounter--;
    }
    if (!flag)
    { // In case let's create a puppet useless enemy, (for the fake enemy generation, utils for put at least one element in the list)
        p_EnemyList tmpHead = new EnemyList;
        Enemy enemy(0, 0, ' ', enemyLp, enemyKs, 0);
        enemy.setRWeapon(fakeWeapon);

        tmpHead->enemy = enemy;
        tmpHead->next = h_enemyList;
        h_enemyList = tmpHead;

        flag = true;
    }
    return h_enemyList;
}

bool Game::checkIfAllEnemiesAreDead(GameEnvironment gameEnvironment, p_EnemyList h_enemyList)
{

    /*
    Check if a Room is cleared, so the doors (exept the locked one) can be opened.
    */

    if (gameEnvironment.lenghtEnemyList(h_enemyList) == 0)
        return (true);
    else
        return (false);
}

std::tuple<Entity, int> Game::calculateLives(Entity entity, int lives)
{

    /*
    When the player maxLife doubles its original value (10 -> 20)
    the player gains a life. And his currentLife points heal completely.
    */

    if (entity.getLifePoints() >= 20)
    {
        lives++;
        entity.setCurrentLifePoints(10);
        entity.setLifePoints(10);
    }
    return std::make_tuple(entity, lives);
}

void Game::checkMeleeDamage(p_EnemyList h_enemyList, Entity &entity, bool &pause, int &hearts)
{

    /*
    When the player is very close to an enemy, it will deal a certain amount of damage
    depending on the enemy type, to the player.
    */

    while (h_enemyList != NULL)
    {
        if (((entity.getX() == h_enemyList->enemy.getX() + 1) && (entity.getY() == h_enemyList->enemy.getY())) ||
            ((entity.getX() == h_enemyList->enemy.getX() - 1) && (entity.getY() == h_enemyList->enemy.getY())) ||
            ((entity.getX() == h_enemyList->enemy.getX()) && (entity.getY() == h_enemyList->enemy.getY() - 1)) ||
            ((entity.getX() == h_enemyList->enemy.getX()) && (entity.getY() == h_enemyList->enemy.getY() + 1)))
        {
            entity.decreaseCurrentLifePoints(h_enemyList->enemy.getMeleeDamage());
            checkPlayerDeath(entity, pause, hearts);
        }
        h_enemyList = h_enemyList->next;
    }
}

void Game::gameHandler(GameEnvironment gameEnvironment, int direction)
{

    /* 
    Main game engine. Most of the function are called here.
    */

    RangedWeapon startWeapon((char *)"Magic gun", 8, 'o', 1, 10);
    Entity player(46, 18, 'P', 10);
    player.setRWeapon(startWeapon);

    bool passRoomsItems[17], passRoomsEnemies[17];
    for (int i = 0; i < 17; i++)
    {
        passRoomsItems[i] = false;
        passRoomsEnemies[i] = false;
    }
    passRoomsItems[0] = true;
    passRoomsEnemies[0] = true;

    bool noEnemy = true;
    int enemyCounter = 1;
    int hearts = 3;
    int keyCounter = 0;

    p_bullet h_enemyBulletList = NULL;

    p_EnemyList h_enemyList = NULL;
    p_itemList h_itemList = NULL;
    p_Room h_roomList = new Room;

    int roomTracker = 0;
    clear();
    refresh();
    h_roomList = gameEnvironment.mapGenerator(h_roomList);

    gameEnvironment.drawRoom(20, 7, 22, true, 0);
    gameEnvironment.drawInfo(71, 20, 7, 22, true, player, points, keyCounter, hearts, h_enemyList);
    while (!pause)
    {
        refresh();
        // O print the first room
        // 14 print the second room

        std::tie(h_roomList, enemyCounter) = gameEnvironment.roomChange(player, h_enemyList, h_roomList, h_itemList,
                                                                        bottomDistance, rightDistance, maxX, maxY, noEnemy, points,
                                                                        enemyCounter, passRoomsItems);

        if (roomTracker != h_roomList->roomTracker)
        {
            roomTracker = h_roomList->roomTracker;
            gameEnvironment.drawRoom(bottomDistance, maxX, maxY, noEnemy, h_roomList->roomTracker);
            if (!passRoomsEnemies[roomTracker / ROOM_OFFSET])
            {
                h_enemyList = generateEnemy(gameEnvironment, enemyCounter, roomTracker, h_enemyList);
                noEnemy = false;
                gameEnvironment.closeAllDoors(noEnemy, rightDistance, bottomDistance, maxX, maxY);

                passRoomsEnemies[roomTracker / ROOM_OFFSET] = true;
            }
            gameEnvironment.cleanActionBox(rightDistance, bottomDistance, maxX, maxY);
        }

        noEnemy = checkIfAllEnemiesAreDead(gameEnvironment, h_enemyList);
        if (noEnemy)
        {
            gameEnvironment.openAllDoors(rightDistance, bottomDistance, maxX, maxY, roomTracker);
        }

        gameEnvironment.drawCharacter(player.getX(), player.getY(), player.getSkin());

        if (roomTracker / ROOM_OFFSET > 0)
            gameEnvironment.drawItems(h_roomList->itemList);

        gameEnvironment.drawEnemies(gameEnvironment, h_enemyList);

        getInput(direction);

        std::tie(player, keyCounter) = gameInputs(gameEnvironment, player, direction, h_roomList, points, keyCounter, noEnemy, timer);

        gameEnvironment.drawCharacter(player.getX(), player.getY(), player.getSkin());

        std::tie(player, hearts) = calculateLives(player, hearts);
        gameEnvironment.drawInfo(rightDistance, bottomDistance, maxX, maxY, noEnemy, player, points, keyCounter, hearts, h_enemyList);

        gameEnvironment.moveEnemies(h_enemyList);

        increaseTimers(timer, enemyTimer);

        handleEnemyBullets(player, h_enemyList, h_enemyBulletList);

        moveBullets(this->playerBullets);
        moveBullets(h_enemyBulletList);

        bulletCollision(this->playerBullets, h_enemyList, player, points, hearts, pause);
        bulletCollision(h_enemyBulletList, h_enemyList, player, points, hearts, pause);

        destroyBullet(this->playerBullets, player.getX(), player.getY());
        destroyBullet(h_enemyBulletList, player.getX(), player.getY());

        checkMeleeDamage(h_enemyList, player, pause, hearts);
    }
}