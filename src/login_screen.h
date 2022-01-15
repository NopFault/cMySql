#define PER_PAGE 10
#define MAX_STR_HOSTNAME 50
#define MAX_STR_LOGIN 50
#define MAX_STR_PASS 50

typedef struct {
    char *hostname[MAX_STR_HOSTNAME];
    char *login[MAX_STR_LOGIN];
    char *pass[MAX_STR_PASS];
} Database;


void hostList();
void loginScreen();


