#include <ncurses.h>
#include <stdlib.h>

// Maybe to model files or something
typedef struct Database {
    char hostname[50];
    char login[50];
    char pass[50];
} Database;

Database * hostList();
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
Database * hostList( Database * hosts )
{
    // From file to hosts array
    for (int x=0; x<=5; x++) {
        hosts[x] = (struct Database){"rferf","erferf","erferfe"};
    }

    return hosts;
}

void loginScreen()
{

    // Read from file and generate this:
    Database h[100];
    Database * hosts = hostList(h);

    char host[50];
    int ch, i = 0;

    int yMax, xMax;
    getmaxyx(stdscr,yMax, xMax);

    // create a window for input
    WINDOW * login_win = newwin(sizeof(hosts)+2, xMax-12, yMax / 2 - 5, 8);
    box(login_win, 0,0);
    mvwprintw(login_win, 0, 2, "  Select host: ");

    for (i=0; i<=(sizeof(hosts)-1); i++) {
        sprintf(host, "%.*s",  (int)sizeof(hosts[i].hostname), hosts[i].hostname);
        mvwprintw(login_win, i+2, 2, host);
    }

    keypad(login_win, TRUE);
    refresh();
    wrefresh(login_win);
    curs_set(0);

    // app loop
    while((ch = wgetch(login_win)) != 'q') {
        sprintf(host, "%.*s",  (int)sizeof(hosts[i].hostname), hosts[i].hostname);
        mvwprintw( login_win, i+2, 2, "%.*s", (int)sizeof(host), host );

        // event keys
        switch( ch ) {
            case KEY_UP:
                i--;
                i = (i<0) ? (sizeof(hosts)-3) : i;
                break;
            case KEY_DOWN:
                i++;
                i = (i >= (sizeof(hosts)-2)) ? 0 : i;
                break;
            case KEY_ENTER:
                // Make new window alert
                break;
        }

        wattron(login_win, A_STANDOUT);
        sprintf(host, "%.*s",  (int)sizeof(hosts[i].hostname), hosts[i].hostname);
        mvwprintw( login_win, i+2, 2, "%.*s", (int)sizeof(host), host );
        wattroff(login_win, A_STANDOUT);
        refresh();
        wrefresh(login_win);
    }

    delwin(login_win);
    endwin();
}

