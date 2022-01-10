#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

#define PER_PAGE 5

// Maybe to model files or something
typedef struct {
    char hostname[50];
    char login[50];
    char pass[50];
} Database;

void hostList();
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

// Generate Database typedef with data from file
void hostList(Database * hosts)
{
    // From file to hosts array
    for (int x = 0; x < PER_PAGE; ++x) {
        hosts[x] = (Database){"hostname", "loginname", "password"};
    }
}

void loginScreen()
{

    // Read from file and generate this:
    Database hosts[PER_PAGE];
    hostList(hosts);

    int ch, i = 0;
    int size_of_hosts = sizeof(hosts) / sizeof(Database);

    int yMax, xMax;
    getmaxyx(stdscr,yMax, xMax);

    // create a window for input
    WINDOW * login_win = newwin(size_of_hosts*2, xMax-12, yMax / 2 - 5, 8);
    box(login_win, 0,0);
    mvwprintw(login_win, 0, 2, "  Select host: ");

    for (int x = 0; x < size_of_hosts; ++x) {
        mvwprintw(login_win, x+2, 2, hosts[x].hostname);
    }

    keypad(login_win, TRUE);
    refresh();
    wrefresh(login_win);
    curs_set(0);

    // app loop
    while((ch = wgetch(login_win)) != 'q') {
        mvwprintw( login_win, i+2, 2, "%.*s", (int)strlen(hosts[i].hostname), hosts[i].hostname);

        // event keys
        switch( ch ) {
            case KEY_UP:
                i--;
                i = (i < 0) ? (size_of_hosts) : i;
                break;
            case KEY_DOWN:
                i++;
                i = (i >= size_of_hosts) ? 0 : i;
                break;
            case KEY_ENTER:
                // Make new window alert
                break;
        }

        wattron(login_win, A_STANDOUT);
        mvwprintw( login_win, i+2, 2, "%.*s", (int)strlen(hosts[i].hostname), hosts[i].hostname);
        wattroff(login_win, A_STANDOUT);
        refresh();
        wrefresh(login_win);
    }

    delwin(login_win);
    endwin();
}

