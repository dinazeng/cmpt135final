//record class
#include "cmpt_error.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class single_record{
    public:
        single_record(string mangaName, vector<string> mangaAuthor, vector <string> mangaGenres, 
                      bool mangaStatus, int releaseYear): name(mangaName), authors(mangaAuthor),
                      genres(mangaGenres), isReleasing(mangaStatus), year(releaseYear){}

        single_record(string mangaName, vector<string> mangaAuthor):
            name(mangaName), authors(mangaAuthor){}

        //default constructor
        single_record(){}

        // Setters
        void set_name(string newName){name = newName;}
        void set_author(vector<string> newAuthor){authors = newAuthor;}
        void set_genres(vector <string> newGenres) {genres = newGenres;}
        void set_status (bool newStat){isReleasing = newStat;}
        void set_year(int newYear){year = newYear;}
    
        // Getters
        string getName() const { return name; }
        vector<string> getAuthor() const { return authors; }
        vector<string> getGenres() const { return genres; }
        bool getStatus() const { return isReleasing; }
        int getYear() const { return year; }

        //Other functions
        void add_genre(string newGenre){genres.push_back(newGenre);}
        void add_author(string newAuthor){authors.push_back(newAuthor);}

        ~single_record(){}

    private:
        string name = "";
        vector<string> authors = {};
        vector <string> genres = {};
        bool isReleasing = false;
        int year = 0;
};
