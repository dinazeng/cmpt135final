//menu class
#include <iostream>
using namespace std;

class menu{
    public:
        //default and only constructor
        menu(){}

        //prints the available choices in menu
        void printMenu();

        //changes all characters in a string to lower case
        string toLowerStr (string str);

    private:
        string response = "";
        database *info;
};