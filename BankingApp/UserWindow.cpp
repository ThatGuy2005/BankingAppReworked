#include "UserWindow.h"

//------------------------------------------------------------------------------------------------

constexpr int WIDTH = 1200;
constexpr int HEIGHT = 800;
constexpr int AVG_WIDGET_W = 100;
constexpr int AVG_WIDGET_H = 30;
constexpr int BIG_WIDGET_W = 200;
constexpr int BIG_WIDGET_H = 50;
constexpr int NARROW_WIDGET_H = 25;
constexpr int ERROR_H = 70;

//------------------------------------------------------------------------------------------------

UserWindow::UserWindow(int w, int h, const char* title, Account& acc) :
	Fl_Window(w, h, title), account(acc)
{
    add = false;
    windraw = false;

    balance = new Fl_Output(WIDTH / 1.5, HEIGHT / 10 + BIG_WIDGET_H, BIG_WIDGET_W, NARROW_WIDGET_H, "Balance:");
    balance->insert(std::to_string(acc.get_balance()).c_str());
    balance->show();

    currency = new Fl_Box(WIDTH / 1.5 + BIG_WIDGET_W + 10, HEIGHT / 10 + BIG_WIDGET_H, BIG_WIDGET_W, NARROW_WIDGET_H);
    currency->copy_label(acc.get_type().c_str());
    currency->show();

    add_money = new Fl_Button(WIDTH / 1.5, HEIGHT / 10 + BIG_WIDGET_H * 2, BIG_WIDGET_W, NARROW_WIDGET_H, "Add");
    add_money->show();

    windraw_money = new Fl_Button(WIDTH / 1.5, HEIGHT / 10 + BIG_WIDGET_H * 3, BIG_WIDGET_W, NARROW_WIDGET_H, "Windraw");
    windraw_money->show();

    amount = new Fl_Input(WIDTH / 1.5, HEIGHT / 10 + BIG_WIDGET_H * 4, BIG_WIDGET_W, NARROW_WIDGET_H, "Amount");
    amount->hide();

    conform = new Fl_Button(WIDTH / 1.5, HEIGHT / 10 + BIG_WIDGET_H * 5, BIG_WIDGET_W, NARROW_WIDGET_H, "Conform");
    conform->hide();

    add_money->callback(add_amount_cb, this);
    conform->callback(conform_cb, this);
}

//------------------------------------------------------------------------------------------------

void UserWindow::add_amount_cb(Fl_Widget* widget, void* data)
{
    UserWindow* self = static_cast<UserWindow*>(data);
    self->handle_add_amount();
}

//------------------------------------------------------------------------------------------------

void UserWindow::handle_add_amount()
{
    amount->show();
    conform->show();
    add = true;
}

//------------------------------------------------------------------------------------------------

void UserWindow::conform_cb(Fl_Widget* widget, void* data)
{
    UserWindow* self = static_cast<UserWindow*>(data);
    self->handle_conform();
}

//------------------------------------------------------------------------------------------------

void UserWindow::handle_conform()
{
    double money = std::stod(amount->value());
    std::cout << "Old balance: " << balance->value() << '\n';
    if (add)
    {
        add = false;
        account.deposit(money);
    }
    else if (windraw)
    {
        windraw = false;
        account.withdraw(money);
    }
    balance->value(std::to_string(account.get_balance()).c_str());
    std::cout << "New balance: " << balance->value() << '\n';
    amount->value("");
}

//------------------------------------------------------------------------------------------------