//manga_record.h class

#ifndef MANGA_RECORD_H
#define MANGA_RECORD_H

#include <vector>
#include <string>
#include <ncurses.h>
using namespace std;

class manga_record{
    public:
        manga_record(string mangaName, vector<string> mangaAuthor, vector <string> mangaGenres, 
                       bool mangaStatus, int releaseYear);

        manga_record(string mangaName, vector<string> mangaAuthor);

        //default constructor
        manga_record();

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
        int getYear() const ;

        //print everything
        void printEntry();

        //add to vector functions
        void add_genre(string newGenre);
        void add_author(string newAuthor);

        ~manga_record();

    private:
        string name;
        vector<string> authors;
        vector <string> genres;
        bool isReleasing;
        int year;
        WINDOW* win;
};

#endif