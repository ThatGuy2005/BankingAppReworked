#pragma once


#ifndef WINDOW_H
#define WINDOW_H

//------------------------------------------------------------------------------------------------

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Widget.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Text_Buffer.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Shared_Image.H>
#include "HoverButton.h"
#include "Cryptography.h"
#include "account.h"

//------------------------------------------------------------------------------------------------

class UserWindow;

//------------------------------------------------------------------------------------------------

enum class PasswordError;
enum class IDError;

//------------------------------------------------------------------------------------------------

class BankingWindow : public Fl_Window {
public:
    BankingWindow(int w, int h, const char* title);
private:
    HoverButton* close;
    static void close_cb(Fl_Widget* button, void* data);

    static void finish_account_creation_cb(Fl_Widget* button, void* data);
    PasswordError handle_passcheck(std::string pass);
    IDError handle_idcheck(std::string id);
    bool handle_namecheck(std::string name);

    static void create_account_cb(Fl_Widget* button, void* data);
    void handle_create_account();
    static void return_button_cb(Fl_Widget* button, void* data);
    void handle_return_button();
    static void login_cb(Fl_Widget* button, void* data);
    void handle_login_button();
    static void check_cb(Fl_Widget* button, void* data);
    void handle_check_button();

    Fl_Image* bg_img;

    Fl_Input* id;
    Fl_Input* pass;
    Fl_Input* name;

    Fl_Input* get_id;
    Fl_Input* get_pass;

    //Fl_Box* bg;
    Fl_Box* wrong_data;

    Fl_Box* login_sign;
    Fl_Text_Display* error;
    Fl_Text_Buffer* buffer;

    Fl_Choice* currency;

    HoverButton* create_account;
    HoverButton* login;
    HoverButton* finish_account_creation;
    HoverButton* return_button;

    UserWindow* userWindow;

    HoverButton* check;
};

#endif // WINDOW_H

//------------------------------------------------------------------------------------------------
