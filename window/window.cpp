#include "window.h"
window::window()
{
	initscr();
	WINDOW *win = newwin(20, 30, 5, 5);
	box(win, 0, 0);
	wrefresh(win);
}
window::~window()
{
	endwin();
}
