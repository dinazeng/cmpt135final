//menu class
#ifndef MENU_H
#define MENU_H

#include "manga_record.h"
#include "database.h"
#include "menu.h"
#include <string>
#include <vector>
#include <ncurses.h>
using namespace std;

class menu{
    public:
        //default and only constructor
        menu();

        //ensures that user input is actually a number
        bool realNum (string userInput);

        //prints the available choices in menu
        void printMenu();
        
        //changes all characters in a string to lower case
        string toLowerStr (string str);

         //prints all elements in a vector
        void printDatabase(vector <manga_record> mangaList);

        //prints a singular entry
        char printEntry(int index, vector <manga_record> mangaList);

        //adds an entry to the database
        void addEntry();

        // Checks if string is blank
        bool isBlankString(string input);

        ~menu();
    
    private:
        char response;
        database *info;
        WINDOW*win;
        int yMax, xMax;
};

#endif