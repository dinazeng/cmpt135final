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
        
        // Searching by exact year
        vector<single_record> searchByYear (int year);
        // Searching by year range
        vector<single_record> searchByYear (int yearStart, int yearEnd);

        // Getters
        vector<single_record> getMangaList() const {return mangaList;}
        
        // Deconstructor
        ~database();



    private:
        vector<single_record> mangaList = {};
};
