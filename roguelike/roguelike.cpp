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
    noecho();
    cbreak();
    nonl();
    keypad(stdscr, TRUE);
    
    curs_set(0);

    while (true) {
        GameLoop gameLoop(64, 20);
        //GameLoop gameLoop("test_map.txt");
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
            printw("You win. Press Q to quit or R to restart.");
        } else if (state == GameLoop::TickState::eLose) {
            printw("You lose. Press Q to quit or R to restart.");
        }

        int ch = getch();
        while (ch != 'q' && ch != 'r') {
            napms(70);
            ch = getch();
        }
        if (ch == 'q') {
            break;
        }
    }

    cleanup();
}
