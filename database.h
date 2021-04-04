#include "cmpt_error.h"
#include "record.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
using namespace std;

class database {
    public:
        // Default constructor
        database(){}

        // Reads in each entry in database.txt
        vector<single_record> readFile (string input);

        // Searching by name
        single_record searchByName(string userInput);
        // Deconstructor
        ~database();

    private:
        vector<single_record> mangaList = {};
};
