//menu class
#include "cmpt_error.h"
#include "database.h"
#include "record.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class menu{
    public:
        menu(){}
        void printMenu();
        string toLowerStr (string str);

    private:
        string response = "";
        database *info;
};