//menu class
#include <iostream>
using namespace std;

class menu{
    public:
        //default and only constructor
        menu(){}

        //ensures that user input is actually a number
        bool realNum (string userInput);

        //prints the available choices in menu
        void printMenu();

        //changes all characters in a string to lower case
        string toLowerStr (string str);

        ~menu();
        
    private:
        string response;
        database *info;
};