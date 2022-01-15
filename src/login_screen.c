#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

#include "login_screen.h"
#include "string.h"

void hostList(Database *hosts, int *size_of_hosts)
{
    FILE * fp;
    char line[(MAX_STR_HOSTNAME + MAX_STR_LOGIN + MAX_STR_PASS) + 1]; // struct sizes plus 3 bytes for delimeter (make constants)

    fp = fopen("/home/nopfault/git/sql/config.cmysql", "r");

    while (fgets(line, sizeof(line), fp) && (*size_of_hosts) <= PER_PAGE) {

        char **split_line = split(line, ":");
        if (strlen(split_line[0]) <= MAX_STR_HOSTNAME && strlen(split_line[1]) <= MAX_STR_LOGIN && strlen(split_line[2]) <= MAX_STR_PASS) {
            hosts[(*size_of_hosts)] = (Database){ split_line[0], split_line[1], split_line[2] };
            (*size_of_hosts)++;
        }
        free(split_line);
    }
    (*size_of_hosts)--;
}

void loginScreen()
{

    // Read from file and generate this:
    Database hosts[PER_PAGE];
    int size_of_hosts = 0;

    hostList(hosts, &size_of_hosts);

    int ch, i = 0;

    int yMax, xMax;
    getmaxyx(stdscr,yMax, xMax);

    // create a window for input
    WINDOW * login_win = newwin(size_of_hosts+5, xMax-12, yMax / 2, size_of_hosts);
    box(login_win, 0,0);
    mvwprintw(login_win, 0, 2, "  Select host: ");

    for (int x = 0; x < (size_of_hosts + 1); ++x) {
        mvwprintw(login_win, x+2, 2, *hosts[x].hostname);
    }

    keypad(login_win, TRUE);
    refresh();
    wrefresh(login_win);
    curs_set(0);

    // app loop
    while((ch = wgetch(login_win)) != 'q') {
        mvwprintw( login_win, i+2, 2, "%.*s", (int)strlen(*hosts[i].hostname), *hosts[i].hostname);

        // event keys
        switch( ch ) {
            case KEY_UP:
                i--;
                i = (i < 0) ? (size_of_hosts) : i;
                break;
            case KEY_DOWN:
                i++;
                i = (i > size_of_hosts) ? 0 : i;
                break;
            case KEY_ENTER:
                // Make new window alert
                break;
        }

        wattron(login_win, A_STANDOUT);
        mvwprintw( login_win, i+2, 2, "%.*s", (int)strlen(*hosts[i].hostname), *hosts[i].hostname);
        wattroff(login_win, A_STANDOUT);
        refresh();
        wrefresh(login_win);
    }

    delwin(login_win);
    endwin();
}
