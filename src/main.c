#include <ncurses.h>
#include <stdlib.h>

void loginScreen();

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

// move to external file
void loginScreen()
{

    // Read from file
    char hosts[][10] = {"host_1", "host_2", "host_3", "host_4", "host_5"};
    char host[10];
    int ch, i = 0;

    int yMax, xMax;
    getmaxyx(stdscr,yMax, xMax);

    // create a window for input
    WINDOW * login_win = newwin(9, xMax-12, yMax / 2 - 5, 8);
    box(login_win, 0,0);
    mvwprintw(login_win, 0, 2, "  Select host: ");
    for (i=0; i<=4; i++) {
        sprintf(host, "%s", hosts[i]);
        mvwprintw(login_win, i+2, 2, host);
    }

    keypad(login_win, TRUE);
    refresh();
    wrefresh(login_win);
    curs_set(0);

    // app loop
    while((ch = wgetch(login_win)) != 'q') {
        sprintf(host, "%s",  hosts[i]);
        mvwprintw( login_win, i+2, 2, "%s", host );

        // event keys
        switch( ch ) {
            case KEY_UP:
                i--;
                i = (i<0) ? 4 : i;
                break;
            case KEY_DOWN:
                i++;
                i = (i > 4) ? 0 : i;
                break;
        }
        wattron(login_win, A_STANDOUT);
        sprintf(host, "%s",  hosts[i]);
        mvwprintw( login_win, i+2, 2, "%s", host );
        wattroff(login_win, A_STANDOUT);
        /* refresh(); */
        wrefresh(login_win);
    }

    delwin(login_win);
    endwin();
}

