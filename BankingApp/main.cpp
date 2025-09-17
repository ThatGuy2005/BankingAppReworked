#include <unordered_map>
#include "window.h"

//------------------------------------------------------------------------------------------------

// Decide when to decrypte the file.
// Check so that no account is created twice with the sam ID and same currency
// When querry only get the needed account
// Add an account page. --> Show balance 
//                      --> Transaction history
//                      --> A pie graph for spendings and income 
//                      --> A subscription manager
//                      --> Add and windraw
//                      --> Exchange
// ERRORS: Check everything that can go wrong like files can't be open and so on.

//------------------------------------------------------------------------------------------------

void TODO()
{
    const std::string cyan = "\033[36m";
    const std::string red_bold = "\033[1;31m";
    const std::string yellow = "\033[33m";
    const std::string reset = "\033[0m";

    std::cout << cyan << "Decide when to decrypt the file." << reset << std::endl;
    std::cout << cyan << "Check so that no account is created twice with the same ID and same currency." << reset << std::endl;
    std::cout << cyan << "When query only get the needed account." << reset << std::endl;
    std::cout << cyan << "Add an account page." << reset << std::endl;

    std::cout << yellow << "  --> Show balance" << reset << std::endl;
    std::cout << yellow << "  --> Transaction history" << reset << std::endl;
    std::cout << yellow << "  --> A pie graph for spendings and income" << reset << std::endl;
    std::cout << yellow << "  --> A subscription manager" << reset << std::endl;
    std::cout << yellow << "  --> Add and withdraw" << reset << std::endl;
    std::cout << yellow << "  --> Exchange" << reset << std::endl;
    std::cout << red_bold << "ERRORS: " << reset << cyan << "Check everything that can go wrong like files can't be open and so on." << reset << std::endl;
    std::cout << red_bold << "TEST CHECK_BUTTON!!!" << reset << std::endl;
}

//------------------------------------------------------------------------------------------------

// IMPORTANT: WE WON'T WRITE OUT TO A FILE. FIRST MAKE A RANDOM USER_IDENTIFIER CAN'T HAVE THE SAME ONES. IT IS NOT ENCRYPTED.
// AFTER THE IDENTIFIER THERE WILL BE THE ENCRYPTED DATA, EVERYTHING EXCEPT THE HISTORY WHICH WILL BE IN A DIFFERENT FILE.
// TEST CHECK_BUTTON

//------------------------------------------------------------------------------------------------

int main() 
{
    TODO();
    BankingWindow win(1200, 800, "MyBank");
    Fl::background(128, 128, 128);
    win.show();
    return Fl::run();
}

//------------------------------------------------------------------------------------------------