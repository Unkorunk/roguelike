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

    //GameLoop gameLoop(64, 16);
    GameLoop gameLoop("test_map.txt");
    gameLoop.init();

    napms(12);
    refresh();
    nodelay(stdscr, TRUE);

    GameLoop::TickState state = gameLoop.tick();
    while (state == GameLoop::TickState::eContinue) {
        napms(100);
        refresh();

        state = gameLoop.tick();
    }

    clear();

    if (state == GameLoop::TickState::eWin) {
        printw("You win. Press Q to quit.");
    } else if (state == GameLoop::TickState::eLose) {
        printw("You lose. Press Q to quit.");
    }

    while (getch() != 'q') {
        napms(70);
    }

    cleanup();
}
