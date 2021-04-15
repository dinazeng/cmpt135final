//database class

#ifndef DATABASE_H
#define DATABASE_H

#include "cmpt_error.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
using namespace std;

class database {
    public:
        // constructor
        database(string input){}

        // Reads in each entry in database.txt
        void readFile (string input);

/* -------------------------- Searching for records ------------------------- */
        // Searching by name
        manga_record searchByName (string name);
        // Searching by exact year
        vector<manga_record> searchByYear (int year);
        // Searching by year range
        vector<manga_record> searchByYear (int yearStart, int yearEnd);

/* ------------------- Searching for and deleting records ------------------- */
        // Searching by name
        void deleteByName (string name);
        // Searching by exact year
        void deleteByYear (int year);
        // Searching by year range
        void deleteByYear (int yearStart, int yearEnd);
        
        // Ask for confirmation on deleting record
        bool deleteConfirmation(manga_record manga);
        void deleteConfirmationYear (vector<manga_record> searchResults);

        bool realNum (string userInput, int end);

        vector<manga_record> listAlphabetical();       
        vector<manga_record> listAlphabeticalReverse();

        vector<manga_record> listNumerical();
        vector<manga_record> listNumericalReverse();


        // Getters
        vector<manga_record> getMangaList() const;

        //Modify the vector
        void add_entry (manga_record newEntry);

        // Displaying a manga's information
        void displayInformation(int index, manga_record manga);

        void notFound();

        // Deconstructor
        ~database();



    private:
        vector<manga_record> mangaList = {};
};

#endif