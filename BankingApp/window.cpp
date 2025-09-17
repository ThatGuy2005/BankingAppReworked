#include "window.h"
#include "usermanager.h"
#include <FL/Fl_Image.H>
#include <FL/Fl_PNG_Image.H>
#include <cstdio>
#include <string>
#include <string_view>
#include <array>
#include "Query.h"
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

UserManager banking_manager;    // Global instance for storage

//------------------------------------------------------------------------------------------------

enum class PasswordError {
    None,
    TooShort,
    NoUppercase,
    NoLowercase,
    NoDigit,
    NoSpecialChar
};

//------------------------------------------------------------------------------------------------

enum class IDError {
    None,
    InvalidLenght,
    Invalid
};

//------------------------------------------------------------------------------------------------

enum class Currency {
    USD = 0,
    EUR,
    CHF,
    COUNT
};

//------------------------------------------------------------------------------------------------

BankingWindow::BankingWindow(int w, int h, const char* title)
    : Fl_Window(w, h, title)
{
    //-------------------------------------MAIN_PAGE--------------------------------------------------

    //bg_img = new Fl_PNG_Image("banking_background_1.png");

    //bg = new Fl_Box(0, 0, WIDTH, HEIGHT);
    //bg->image(bg_img);
    //bg->box(FL_NO_BOX);

    close = new HoverButton(10, 10, AVG_WIDGET_W, AVG_WIDGET_H, "Quit");
    close->labelcolor(FL_WHITE);

    login_sign = new Fl_Box(WIDTH/2, HEIGHT/10, AVG_WIDGET_W, AVG_WIDGET_H, "Welcome to MyBank");
    login_sign->labelfont(FL_HELVETICA_BOLD);
    login_sign->labelsize(Fl_Fontsize(30));

    create_account = new HoverButton(WIDTH / 2, HEIGHT / 4, AVG_WIDGET_W, BIG_WIDGET_H, "New Account");
    create_account->labelfont(FL_HELVETICA_BOLD);
    create_account->labelcolor(FL_WHITE);

    login = new HoverButton(WIDTH / 2, HEIGHT / 2, AVG_WIDGET_W, BIG_WIDGET_H, "Login");
    login->labelfont(FL_HELVETICA_BOLD);
    login->labelcolor(FL_WHITE);

    //------------------------------------CREATE_ACCOUNT----------------------------------------------

    id = new Fl_Input(WIDTH / 2, HEIGHT / 10 + BIG_WIDGET_H, BIG_WIDGET_W, NARROW_WIDGET_H, "ID:");
    id->hide();

    pass = new Fl_Input(WIDTH / 2, HEIGHT / 10 + BIG_WIDGET_H *2, BIG_WIDGET_W, NARROW_WIDGET_H, "Password:");
    pass->hide();

    name = new Fl_Input(WIDTH / 2, HEIGHT / 10 + BIG_WIDGET_H * 3, BIG_WIDGET_W, NARROW_WIDGET_H, "Name:");
    name->hide();

    finish_account_creation = new HoverButton(WIDTH / 2, HEIGHT / 10 + BIG_WIDGET_H * 4, BIG_WIDGET_W, NARROW_WIDGET_H, "Finish");
    finish_account_creation->labelcolor(FL_WHITE);
    finish_account_creation->hide();

    error = new Fl_Text_Display(WIDTH / 2, HEIGHT / 10 + BIG_WIDGET_H * 6, BIG_WIDGET_W, ERROR_H);
    buffer = new Fl_Text_Buffer();
    error->buffer(buffer);
    error->hide();

    currency = new Fl_Choice(WIDTH / 1.5, HEIGHT / 10 + BIG_WIDGET_H, AVG_WIDGET_W * 1.2, NARROW_WIDGET_H);
    currency->add("USD");
    currency->add("EUR");
    currency->add("CHF");
    currency->value(0);
    currency->hide();

    //----------------------------------------LOGIN---------------------------------------------------

    get_id = new Fl_Input(WIDTH / 2, HEIGHT / 10 + BIG_WIDGET_H * 2, BIG_WIDGET_W, NARROW_WIDGET_H, "ID:");
    get_id->hide();

    get_pass = new Fl_Input(WIDTH / 2, HEIGHT / 10 + BIG_WIDGET_H * 3, BIG_WIDGET_W, NARROW_WIDGET_H, "Password:");
    get_pass->hide();

    wrong_data = new Fl_Box(WIDTH / 2, HEIGHT / 10 + BIG_WIDGET_H * 4, BIG_WIDGET_W, NARROW_WIDGET_H, "THE ID OR THE PASSWORD IS WRONG!");
    wrong_data->labelsize(Fl_Fontsize(16));
    wrong_data->hide();

    check = new HoverButton(WIDTH / 2, HEIGHT / 10 + BIG_WIDGET_H * 4, BIG_WIDGET_W, NARROW_WIDGET_H, "Check");
    check->labelcolor(FL_WHITE);
    check->hide();

    //---------------------------------------BACK_TO_MAIN---------------------------------------------

    return_button = new HoverButton(WIDTH / 2, HEIGHT / 10 + BIG_WIDGET_H * 5, BIG_WIDGET_W, NARROW_WIDGET_H, "Return");
    return_button->labelfont(FL_HELVETICA_BOLD);
    return_button->labelcolor(FL_WHITE);
    return_button->hide();

    //--------------------------------------CALLBACKS-------------------------------------------------

    close->callback(close_cb, this);
    create_account->callback(create_account_cb, this);
    finish_account_creation->callback(finish_account_creation_cb, this);
    return_button->callback(return_button_cb, this);
    login->callback(login_cb, this);
    check->callback(check_cb, this);
}

//------------------------------------------------------------------------------------------------

void BankingWindow::handle_create_account()
{
	this->login_sign->hide();
	this->create_account->hide();
	this->id->show();
	this->pass->show();
    this->finish_account_creation->show();
    this->name->show();
    this->currency->show();
    this->login->hide();
    this->return_button->show();
}

//------------------------------------------------------------------------------------------------

void BankingWindow::handle_return_button()
{
    this->login_sign->show();
    this->create_account->show();
    this->id->hide();
    this->pass->hide();
    this->finish_account_creation->hide();
    this->name->hide();
    this->currency->hide();
    this->login->show();
    this->return_button->hide();
    this->error->hide();
    this->check->hide();
    this->get_id->hide();
    this->get_pass->hide();
}

//------------------------------------------------------------------------------------------------

void BankingWindow::handle_login_button()
{
    this->login->hide();
    this->create_account->hide();
    this->return_button->show();
    this->check->show();
    this->get_id->show();
    this->get_pass->show();
}

//------------------------------------------------------------------------------------------------

void BankingWindow::return_button_cb(Fl_Widget* button, void* data)
{
    BankingWindow* self = static_cast<BankingWindow*>(data);
    self->handle_return_button();
}

//------------------------------------------------------------------------------------------------

void BankingWindow::create_account_cb(Fl_Widget* button, void* data)
{
	BankingWindow* self = static_cast<BankingWindow*>(data);
	self->handle_create_account();
}

//------------------------------------------------------------------------------------------------

void BankingWindow::check_cb(Fl_Widget* button, void* data)
{
    BankingWindow* self = static_cast<BankingWindow*>(data);
    self->handle_check_button();
}

//------------------------------------------------------------------------------------------------

void BankingWindow::login_cb(Fl_Widget* button, void* data)
{
    BankingWindow* self = static_cast<BankingWindow*>(data);
    self->handle_login_button();
}

//------------------------------------------------------------------------------------------------


/// <summary>
/// This function must be rewritten. We must find the user_id then get the line that needs decryption.
/// Also, query() must be rewritten.
/// </summary>

void separate_data(std::string& line)
{
    size_t pos = line.find(':');
    if (pos != std::string::npos) {
        line = line.substr(pos + 2);
    }
    else
    {
        std::cout << line << '\n';
        std::cerr << "Corrupted data!\n";
    }
}

//------------------------------------------------------------------------------------------------

void BankingWindow::handle_check_button()
{
    // Get the result from the query and store it for check
    QueryResult check_it;
    std::ifstream in("data.csv", std::ios::binary);
    std::string decrypted;
    bool found = false;

    while (!found && !in.eof())
    {
        std::getline(in, decrypted);
        
        separate_data(decrypted);

        try {
            decrypted = decryptFromString(decrypted);
        }
        catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << "\n";
        }

        // Query the decrypted data
        std::stringstream os;
        os << decrypted;

        try {
            check_it = query(os);
        }
        catch (std::runtime_error& err) {
            std::cerr << err.what() << '\n';
        }

        // Check if the user entered the right data
        std::cout << "Actual ID: " << check_it.ID << '\n';
        if (get_id->value() == check_it.ID && get_pass->value() == check_it.password)
        {
            std::cout << "Success!\n";
            Account a(check_it.name, check_it.currency, check_it.balance);
            userWindow = new UserWindow(1200, 800, "MyBank", a);
            userWindow->show();
            this->hide();
            found = true;
        }
    }
    if (!found)
    {
        throw std::runtime_error("No account found with this password!");
    }
}

//------------------------------------------------------------------------------------------------

PasswordError BankingWindow::handle_passcheck(std::string pass)
{
    if (pass.empty()) return PasswordError::TooShort;

    bool upper, lower, special, digit;

    int count = 0;

    for (auto c : pass)
    {
        if (isupper(c)) upper = true;
        else if (islower(c)) lower = true;
        else if (isdigit(c)) digit = true;
        else special = true;
        count++;
    }

    if (count < 12) return PasswordError::TooShort;
    if (!upper) return PasswordError::NoUppercase;
    if (!lower) return PasswordError::NoLowercase;
    if (!digit) return PasswordError::NoDigit;
    if (!special) return PasswordError::NoSpecialChar;

    return PasswordError::None;
}

//------------------------------------------------------------------------------------------------

IDError BankingWindow::handle_idcheck(std::string id)
{
    int count = 0;

    for (auto c : id)
    {
        if (!isdigit(c)) return IDError::Invalid;
        count++;
    }

    if (count != 13) return IDError::InvalidLenght;

    return IDError::None;
}

//------------------------------------------------------------------------------------------------

bool BankingWindow::handle_namecheck(std::string name)
{
    for (auto c : name)
    {
        if (!isalpha(c) || isdigit(c)) return false;
    }
    return true;
}

//------------------------------------------------------------------------------------------------

void save()
{
    // Step 1: Write the data
    {
        std::ofstream out("data.csv", std::ios::app);
        out << '\n';
        out << banking_manager;
        std::cout << banking_manager.get_whole_data() << '\n';
    }
    // Step 2: Encrypt the data and write it out to the file
    
    encryptToFile(banking_manager.get_whole_data(), "data.csv");
    encryptToFile(banking_manager.get_history_data(), "data_" + banking_manager.get_current_id() + ".csv");
}

//------------------------------------------------------------------------------------------------

void BankingWindow::finish_account_creation_cb(Fl_Widget* button, void* data)
{
    // Check if the ID and the Password is valid if not then an error occured
    BankingWindow* self = static_cast<BankingWindow*>(data);
    PasswordError err = self->handle_passcheck(self->pass->value());
    IDError id_err = self->handle_idcheck(self->id->value());

    bool err_occured = false;

    self->buffer->text("\0");

    // Give the precise problem to the user
    switch (err)
    {
    case PasswordError::None:
        break;
    case PasswordError::TooShort:
        self->buffer->text("The password entered is too short!\n It should be at least 12 characters long.");
        err_occured = true;
        break;
    case PasswordError::NoUppercase:
        self->buffer->text("There must be at least one uppercase character!");
        err_occured = true;
        break;
    case PasswordError::NoLowercase:
        self->buffer->text("There must be at least one lowercase character!");
        err_occured = true;
        break;
    case PasswordError::NoDigit:
        self->buffer->text("There must be at least one digit!");
        err_occured = true;
        break;
    case PasswordError::NoSpecialChar:
        self->buffer->text("There must be at least one special character!");
        err_occured = true;
        break;
    default:
        break;
    }

    switch (id_err)
    {
    case IDError::None:
        break;
    case IDError::InvalidLenght:
        self->buffer->text("The ID must contain 13 digits!");
        err_occured = true;
        break;
    case IDError::Invalid:
        self->buffer->text("The ID must contain only digits!");
        err_occured = true;
        break;
    default:
        break;
    }

    if (!self->handle_namecheck(self->name->value()))
    {
        self->buffer->text("Invalid Name!");
        err_occured = true;
    }

    // If the account is created then add it to the user manager, which prints it to a file where it is saved
    if (!err_occured)
    {
        self->buffer->text("Account created successfully!");

        std::string currency;
        Currency type = static_cast<Currency>(self->currency->value());
        constexpr std::size_t CurrencyCount = static_cast<std::size_t>(Currency::COUNT);
        
        constexpr std::array<std::string_view, CurrencyCount> currencyNames = std::to_array<std::string_view>({ "USD", "EUR", "CHF" });
        currency = std::string(currencyNames.at(static_cast<size_t>(type)));;
        
        banking_manager.add_user(self->name->value(), self->id->value(), self->pass->value(), currency, 0.0);

        try {
            save();
        }
        catch (std::runtime_error err)
        {
            std::cerr << err.what();
        }
    }

    self->error->show();
}

//------------------------------------------------------------------------------------------------

void BankingWindow::close_cb(Fl_Widget* button, void* data)
{
    BankingWindow* win = static_cast<BankingWindow*>(data);

    win->hide();
}

//------------------------------------------------------------------------------------------------