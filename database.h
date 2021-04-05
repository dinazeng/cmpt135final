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
        void readFile (string input);

/* -------------------------- Searching for records ------------------------- */
        // Searching by name
        single_record searchByName (string name);
        // Searching by exact year
        vector<single_record> searchByYear (int year);
        // Searching by year range
        vector<single_record> searchByYear (int yearStart, int yearEnd);

/* ------------------- Searching for and deleting records ------------------- */
        // Searching by name
        void deleteByName (string name);
        // Searching by exact year
        void deleteByYear (int year);
        // Searching by year range
        void deleteByYear (int yearStart, int yearEnd);

        // Ask for confirmation on deleting record
        bool deleteConfirmation(single_record manga);
        void deleteConfirmationYear (vector<single_record> searchResults);

        // Getters
        vector<single_record> getMangaList() const {return mangaList;}

        // Displaying a manga's information
        void displayInformation(int index, single_record manga);

        // Deconstructor
        ~database();



    private:
        vector<single_record> mangaList = {};
};
