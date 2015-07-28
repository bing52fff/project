#include "window.h"
window::window(int size) : input_size(size)
{
	initscr();
	header = NULL;
	output = NULL;
	friends_list = NULL;
	input = NULL;
	curs_set(0);
}
window::~window()
{
	if (NULL != header)
		destroy_win(header);
	if (NULL != output)
		destroy_win(output);
	if (NULL != friends_list)
		destroy_win(friends_list);
	if (NULL != input)
		destroy_win(input);
	endwin();
}
void window::destroy_win(WINDOW *win)
{
	delwin(win);
}
void window::add_str_to_win(WINDOW *win, int y, int x, std::string &msg)
{
	mvwaddstr(win, y, x, msg.c_str());
}
void window::clear_win_line(WINDOW *win, int begin, int num)
{
	while (num--)
	{
		wmove(win, begin++, 0);
		wclrtoeol(win);
	}
}
std::string window::get_str_from_win(WINDOW *win)
{
	char buf[input_size];
	memset(buf, 0, sizeof(input_size));
	wgetnstr(win, buf, sizeof(buf));
	return buf;
}
void window::win_refresh(WINDOW *win)
{
	refresh();
	box(win, 0, 0);
	wrefresh(win);
}
WINDOW* window::new_win(int y, int x, int width, int height)
{
	WINDOW *win = newwin(height, width, y, x);
	return win;
}
void window::create_header_win()
{
	header = new_win(0, 0, COLS, LINES/5);
}
void window::create_output_win()
{
	output = new_win(LINES/5, 0, COLS*3/4, LINES*3/5);
}
void window::create_friends_list_win()
{
	int x = COLS*3/4;
	int y = LINES/5;
	int width = COLS/4;
	int height = LINES*3/5;
	friends_list = new_win(y, x, width, height);
}
void window::create_input_win()
{
	input = new_win(LINES*4/5, 0, COLS, LINES/5);
	std::string msg = "Enter$ ";
	add_str_to_win(input, 1, 1, msg);
}
