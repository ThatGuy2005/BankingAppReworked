#pragma once
#ifndef USERWINDOW_H
#define USERWINDOW_H

//------------------------------------------------------------------------------------------------

#include "window.h"

//------------------------------------------------------------------------------------------------

class UserWindow : public Fl_Window
{
public:
	UserWindow(int w, int h, const char* title, Account& a);

private:
	static void add_amount_cb(Fl_Widget* widget, void* data);
	void handle_add_amount();
	static void conform_cb(Fl_Widget* widget, void* data);
	void handle_conform();
	Fl_Window* win;

	Fl_Box* currency;
	Fl_Output* balance;
	Fl_Input* amount;
	
	Fl_Button* add_money;
	Fl_Button* windraw_money;
	Fl_Button* conform;

	Account& account;

	bool add;
	bool windraw;

};

#endif // !USERWINDOW_H

//------------------------------------------------------------------------------------------------
