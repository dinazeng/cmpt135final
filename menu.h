//menu class
#include "database.h"
#include <iostream>
#include <ncurses.h>
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

        //prints all elements in a vector
        void printDatabase(vector <single_record> mangaList);

        //adds an entry
        void addEntry();
        
        ~menu();
        
    private:
        int response;
        int xMax, yMax;
        string print;
        WINDOW *win;
        database *info;
};