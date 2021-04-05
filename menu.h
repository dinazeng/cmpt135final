#include "cmpt_error.h"
#include <iostream>
#include <string>
using namespace std;

class menu{
    public:
        menu(){}

        void printMenu();

        void getResponse(string res);

    private:
        string response = "";
};