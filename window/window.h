#ifndef __WINDOW_H
#define __WINDOW_H

#include "util.h"

class window
{
public:
	window(int size);
	~window();
	void add_str_to_win(WINDOW *win, int y, int x, std::string &msg);
	void clear_win_line(WINDOW *win, int begin, int num);
	std::string get_str_from_win(WINDOW *win);
	void win_refresh(WINDOW *win);
	void create_header_win();
	void create_output_win();
	void create_friends_list_win();
	void create_input_win();
public:
	WINDOW* get_header()
	{
		return header;
	}
	WINDOW* get_output()
	{
		return output;
	}
	WINDOW* get_friends_list()
	{
		return friends_list;
	}
	WINDOW* get_input()
	{
		return input;
	}
protected:
	void destroy_win(WINDOW *win);
	WINDOW* new_win(int y, int x, int width, int height);
private:
	const int input_size;
	WINDOW *header;
	WINDOW *output;
	WINDOW *friends_list;
	WINDOW *input;
};

#endif	//window.h

