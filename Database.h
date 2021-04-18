//Database class

#ifndef Database_H
#define Database_H

#include "Manga_Record.h"
#include <vector>
#include <ncurses.h>
#include <string>
using namespace std;

class Database {
    public:
        // Default constructor
        Database();

        // Reads in each entry in Database.txt
        vector<Manga_Record> readFile (string input);

/* -------------------------- Searching for records ------------------------- */
        // Searching by exact name
        vector<Manga_Record> searchByExactName (string name);
        // Searching by substring name
        vector<Manga_Record> searchBySubName (string name);
        // Searching by exact year
        vector<Manga_Record> searchByYear (int year);
        // Searching by year range
        vector<Manga_Record> searchByYear (int yearStart, int yearEnd);
        // Searching by manga author
        vector<Manga_Record> searchByAuthor(string name);
        // Searching by genres
        vector<Manga_Record> searchByGenre(string name);
        // Searching by status
        vector<Manga_Record> searchByStatus(bool status);


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
        bool deleteConfirmation (int index, Manga_Record manga);

        void deleteConfirmationYear (vector<Manga_Record> searchResults);
        
        bool realNum (string userInput, int end);

/* -------------- Listing records in multiple different orders -------------- */
        //changes all characters in a string to lower case
        string toLowStr (string str);

        vector<Manga_Record> listAlphabetical();

        vector<Manga_Record> listAlphabeticalReverse();

        vector<Manga_Record> listNumerical();

        vector<Manga_Record> listNumericalReverse();

        vector<Manga_Record> listAuthor();

        vector <Manga_Record> listAuthorReverse();

        // Getters
        vector<Manga_Record> getMangaList() const; // here

        //Modify the vector
        void add_entry (Manga_Record newEntry);

        void printDatabase(vector<Manga_Record> mangaList);
        
        // Displaying a manga's information
        char displayMultiple(int index, vector<Manga_Record> mangaVec);

        char displaySingular(int index, Manga_Record manga);

        void notFound();

        // Deconstructor
        ~Database();

    private:
        vector <Manga_Record> mangaList;
        int yMax, xMax;
};

#endif