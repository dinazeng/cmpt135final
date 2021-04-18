//Menu class
#ifndef Menu_H
#define Menu_H

#include "Manga_Record.h"
#include "Database.h"
#include "Menu.h"
#include <string>
#include <vector>
#include <ncurses.h>
using namespace std;

class Menu{
    public:
        //default and only constructor
        Menu();

        //ensures that user input is actually a number
        bool realNum (string userInput);

        //prints the available choices in Menu
        void printMenu();
        
        //changes all characters in a string to lower case
        string toLowerStr (string str);

         //prints all elements in a vector
        void printDatabase(vector <Manga_Record> mangaList);

        //prints a singular entry
        char printEntry(int index, vector <Manga_Record> mangaList);

        //adds an entry to the Database
        void addEntry();

        // Checks if string is blank
        bool isBlankString(string input);

        // Deletes leading and trailing whitespace
        string deleteWhitespace(string name);

        ~Menu();
    
    private:
        char response;
        Database *info;
        WINDOW*win;
        int yMax, xMax;
};

#endif