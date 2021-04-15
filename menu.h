//menu class
#ifndef MENU_H
#define MENU_H

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

        //prints all elements in a vector
        void printDatabase(vector <manga_record> mangaList);

        //print a single entry
        char printEntry(int index, vector <manga_record> mangaList);

        //adds an entry
        void addEntry();
        
        ~menu();
        
    private:
        string response;
        database *info;
};

#endif