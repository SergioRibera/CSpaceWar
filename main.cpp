#include <cstdarg>
#include <string>
#include <ncurses.h>

#include "main.h"

WINDOW* wnd;
struct {
    vec2i pos;
    char disp_char;
} player;

int init() {
    wnd = initscr();
    cbreak();
    noecho();
    clear();
    refresh();
    keypad(wnd, true);
    nodelay(wnd, true);
    curs_set(0);
    if(!has_colors()) {
        endwin();
        printf("ERROR: Terminal does not support color.\n");
        exit(1);
    }
    start_color();
    // Draw border box
    attron(A_BOLD);
    box(wnd, 0, 0);
    attroff(A_BOLD);
    //draw background
    init_pair(1, COLOR_BLACK, COLOR_CYAN);
    wbkgd(wnd, COLOR_PAIR(1));
    return 0;
}

void run() {
    player.disp_char = '0';
    player.pos = { 10, 5 };
    int in_char;
    bool exit_requested = false;

    mvaddch(player.pos.y, player.pos.x, player.disp_char);

    while(1){
        in_char = wgetch(wnd);
        mvaddch(player.pos.y, player.pos.x, ' ');
        switch(in_char) {
            case 'q':
                exit_requested = true;
                break;
            case KEY_UP:
            case 'w':
                player.pos.y -= 1;
                break;
            case KEY_DOWN:
            case 's':
                player.pos.y += 1;
                break;
            case KEY_LEFT:
            case 'a':
                player.pos.x -= 1;
                break;
            case KEY_RIGHT:
            case 'd':
                player.pos.x += 1;
                break;
            default:
                break;
        }

        mvaddch(player.pos.y, player.pos.x, player.disp_char);
        refresh();

        if(exit_requested) break;
    }
}

void close() {
    endwin();
}

int main(){
    int initStatus = init();
    if(initStatus == 0)
        run();
    close();
    return 0;
}
