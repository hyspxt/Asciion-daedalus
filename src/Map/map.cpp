
#include "map.hpp"

#include <ncurses.h>
#include <unistd.h>

#include <cmath>
#include <ctime>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

// Definizione di costanti
int main()
{
    initscr();
    for (int cordX = 1; cordX < 20; cordX++){
        
        mvprintw(1, cordX, "h");
        sleep(1);
        refresh();

    }
    endwin();
    return (0);
    }