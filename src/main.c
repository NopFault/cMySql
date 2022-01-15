#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

#include "login_screen.h"

int main(void)
{

    /* NCURSES START */
    initscr();
    noecho();
    cbreak();

    loginScreen();
    /* NCURSES END */

    return EXIT_SUCCESS;
}


