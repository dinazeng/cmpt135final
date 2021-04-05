//menu class
#include "cmpt_error.h"
#include "database.h"
#include "menu.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
using namespace std;

class menu{
    public:
        menu(){
            printMenu();
        }

        void printMenu(){
            cout << "Welcome to the Manga Database!\n";
            cout << "-----------------------------\n";
            while (response != "q"){
                
            }
            delete info;
            cout << "Have a great day!!";
        }

        void getResponse(string res){response = res;}
        
    private:
        string response = "";
        database *info = new database();
};