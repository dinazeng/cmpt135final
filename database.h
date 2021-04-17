//database class

#ifndef DATABASE_H
#define DATABASE_H

#include "manga_record.h"
#include <vector>
#include <ncurses.h>
#include <string>
using namespace std;

class database {
    public:
        // Default constructor
        database();

        // Reads in each entry in database.txt
        void readFile (string input);

/* -------------------------- Searching for records ------------------------- */
        // Searching by exact name
        vector<manga_record> searchByExactName (string name);
        // Searching by substring name
        vector<manga_record> searchBySubName (string name);
        // Searching by exact year
        vector<manga_record> searchByYear (int year);
        // Searching by year range
        vector<manga_record> searchByYear (int yearStart, int yearEnd);
        // Serching by manga author
        vector<manga_record> searchByAuthor(string name);
        // Searching by status
        vector<manga_record> searchByStatus(bool status);


/* ------------------- Searching for and deleting records ------------------- */
        // Searching by exact name
        void deleteByExactName (string name);
        // Searching by sub string name
        void deleteBySubName (string name);
        // Searching by exact year
        void deleteByYear (int year);
        // Searching by year range
        void deleteByYear (int yearStart, int yearEnd);
        // Ask for confirmation on deleting record
        bool deleteConfirmation (int index, manga_record manga);

        void deleteConfirmationYear (vector<manga_record> searchResults);
        
        bool realNum (string userInput, int end);
/* -------------- Listing records in multiple different orders -------------- */

        //changes all characters in a string to lower case
        string toLowStr (string str);

        vector<manga_record> listAlphabetical();

        vector<manga_record> listAlphabeticalReverse();

        vector<manga_record> listNumerical();

        vector<manga_record> listNumericalReverse();

        vector<manga_record> listAuthor();

        vector <manga_record> listAuthorReverse();

        // Getters
        vector<manga_record> getMangaList() const; // here

        //Modify the vector
        void add_entry (manga_record newEntry);

        void printDatabase(vector<manga_record> mangaList);
        
        // Displaying a manga's information
        char displayMultiple(int index, manga_record manga);

        char displaySingular(int index, manga_record manga);

        void notFound();

        // Deconstructor
        ~database();

    private:
        vector <manga_record> mangaList;
        int yMax, xMax;
        WINDOW*win;
};

#endif