//record.h class

#include "cmpt_error.h"
#include <iostream>
#include <vector>
using namespace std;

class single_record{
    public:
        single_record(string mangaName, vector<string> mangaAuthor, vector <string> mangaGenres, 
                      bool mangaStatus, int releaseYear);

        //default constructor
        single_record(){}

        // Setters
        void set_name(string newName);
        void set_authors(vector<string> newAuthor);
        void set_genres(vector <string> newGenres);
        void set_status (bool newStat);
        void set_year(int newYear);
    
        // Getters
        string getName() const;
        vector<string> getAuthors() const;
        vector<string> getGenres() const;
        bool getStatus() const;
        int getYear() const;

        //add to vector functions
        void add_genre(string newGenre);
        void add_author(string newAuthor);

        ~single_record(){}

    private:
        string name = "";
        vector<string> authors = {};
        vector <string> genres = {};
        bool isReleasing = false;
        int year = 0;
};