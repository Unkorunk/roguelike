#include <curses.h>
#include <time.h>

#include "GameLoop.h"

static void cleanup(void) {
    standend();
    refresh();
    curs_set(1);
    endwin();
}

int main(int argc, char* argv[]) {
#ifdef XCURSES
    Xinitscr(argc, argv);
#else
    initscr();
#endif
    srand(time(nullptr));

    noecho();
    cbreak();
    nonl();
    keypad(stdscr, TRUE);

    curs_set(0);

    GameLoop gameLoop("test_map.txt");
    gameLoop.init();

    napms(12);
    refresh();
    nodelay(stdscr, TRUE);

    while (gameLoop.tick()) {
        napms(70);
        refresh();
    }

    cleanup();
}
